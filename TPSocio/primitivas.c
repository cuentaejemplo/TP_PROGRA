#include "primitivas.h"

void ind_crear (t_indice* ind, size_t tam_clave, int (*cmp)(const void*, const void*))
{
    ind->tam_clave= tam_clave;
    ind->cmp = cmp;
    ind->arbol = NULL;
}

int ind_insertar(t_indice *ind, void *clave, unsigned nro_reg)
{
    void *aux_reg_ind = malloc(ind->tam_clave + sizeof(unsigned));
    if (!aux_reg_ind)
    {
        return -1;
    }

    memcpy(aux_reg_ind, clave, ind->tam_clave);

    memcpy(aux_reg_ind + ind->tam_clave, &nro_reg, sizeof(unsigned));

    if(!insertarEnOrderRecursiva(&ind->arbol,aux_reg_ind,ind->tam_clave+sizeof(unsigned),
                                 ind->cmp))
    {
        free(aux_reg_ind);
        return 0;
    }

    free(aux_reg_ind);

    return 1;
}

int ind_cargar (t_indice* ind, const char* path)
{
    t_Socio socio;
    FILE *pf;

    pf = fopen(path,"rb");

    if(!pf)
    {
        printf("No pudo abrir el archivo\n");
        return 0;
    }

    fseek(pf,0,SEEK_SET);

    fread(&socio,sizeof(t_Socio),1,pf);
    int i = 0;

    while(!feof(pf))
    {
        ind_insertar(ind,&socio.NroSocio,i);
        i++;
        fread(&socio,sizeof(t_Socio),1,pf);
    }

    fclose(pf);
    return 1;
}

int ind_recorrer (const t_indice* ind, void (*accion)(const void *, unsigned, void *),void* param)
{
    recorrerArbolOrden(&ind->arbol,accion,param);
    return 1;
}

int ind_buscar(const t_indice* ind, void *clave, unsigned *nro_reg)
{
    t_nodo **nodo = buscarNodo(&ind->arbol, clave, ind->cmp);
    if (!nodo)
    {
        return 0;
    }

    memcpy(nro_reg, (*nodo)->info + ind->tam_clave, sizeof(unsigned));

    return 1;
}

void ind_vaciar (t_indice* ind)
{
    vaciar_arbol(&ind->arbol);
}

void darAltaSocio(t_indice *ind,const char *path)
{
    FILE *pf;
    long nroSocio;
    unsigned pos=0;
    t_Socio socio;

    pf = fopen(path,"r+b");
    if(!pf)
    {
        printf("No se pudo abrir el archivo.\n");
        return;
    }

    printf("Ingrese el numero de socio: ");
    scanf("%ld",&nroSocio);

    if(nroSocio > 1 && nroSocio < 10000000)
    {
        if(ind_buscar(ind,&nroSocio,&pos))
        {
            printf("Numero socio existente\n");
            fseek(pf,pos*sizeof(t_Socio),SEEK_SET);
            fread(&socio,sizeof(t_Socio),1,pf);
            printf("%ld %s\n", socio.NroSocio,socio.ApyNom);
            fclose(pf);
            return;
        }
        else
        {
            printf("Nro socio no existe.\n");
            fclose(pf);
            return;
        }
    }
    else
    {
        printf("Nro socio invalido.\n");
        return;
    }

    fclose(pf);
}

void darBajaSocio(t_indice *ind,const char *path)
{
    FILE *pf;
    long nroSocio;
    unsigned pos=0;
    int dia=0,mes=0,anio=0;
    t_Socio socio;

    pf = fopen(path,"r+b");
    if(!pf)
    {
        printf("No se pudo abrir el archivo.\n");
        return;
    }

    printf("Ingrese el numero de socio: ");
    scanf("%ld",&nroSocio);

    if(nroSocio > 1 && nroSocio < 10000000)
    {
        if(ind_buscar(ind,&nroSocio,&pos))
        {
            printf("Se encontro el numero socio\n");
            fseek(pf,pos*sizeof(t_Socio),SEEK_SET);
            fread(&socio,sizeof(t_Socio),1,pf);
            printf("%ld %s\n", socio.NroSocio,socio.ApyNom);

            if(socio.Estado == 'B')
            {
                printf("El numero socio ya se encuentra dado de baja.\n");
                fclose(pf);
                return;
            }

            printf("Ingrese el dia: ");
            scanf("%d",&dia);

            printf("Ingrese el mes: ");
            scanf("%d",&mes);

            printf("Ingrese el anio: ");
            scanf("%d",&anio);

            socio.Estado = 'B';
            socio.FBaja.Dia = dia;
            socio.FBaja.Mes = mes;
            socio.FBaja.Anio = anio;

            fseek(pf,pos*sizeof(t_Socio),SEEK_SET);
            fwrite(&socio,sizeof(t_Socio),1,pf);

            printf("Se dio de baja existosamente.\n");

            fclose(pf);
            return;
        }
        else
        {
            printf("Nro socio no existe.\n");
            fclose(pf);
            return;
        }
    }
    else
    {
        printf("Nro socio invalido.\n");
        return;
    }

    fclose(pf);
}

void modificarSocio(t_indice *ind,const char *path)
{
    FILE *pf;
    long nroSocio;
    unsigned pos=0;
    char nuevoNombre[60];
    t_Socio socio;

    pf = fopen(path,"r+b");
    if(!pf)
    {
        printf("No se pudo abrir el archivo.\n");
        return;
    }

    printf("Ingrese el numero de socio: ");
    scanf("%ld",&nroSocio);
    fflush(stdin);
    if(nroSocio > 1 && nroSocio < 10000000)
    {
        if(ind_buscar(ind,&nroSocio,&pos))
        {
            printf("nroSocio existente\n");
            fseek(pf,pos*sizeof(t_Socio),SEEK_SET);
            fread(&socio,sizeof(t_Socio),1,pf);
            printf("%ld %s\n", socio.NroSocio,socio.ApyNom);

            printf("Ingrese el nuevo nombre del socio: ");
            gets(nuevoNombre);
            fflush(stdin);

            fseek(pf,pos*sizeof(t_Socio),SEEK_SET);
            strcpy(socio.ApyNom,nuevoNombre);
            fwrite(&socio,sizeof(t_Socio),1,pf);

            fseek(pf,pos*sizeof(t_Socio),SEEK_SET);
            fread(&socio,sizeof(t_Socio),1,pf);
            printf("%ld %s\n", socio.NroSocio,socio.ApyNom);

            fclose(pf);
            return;
        }
        else
        {
            printf("Nro socio no existe.\n");
            fclose(pf);
            return;
        }
    }
    else
    {
        printf("Nro socio invalido.\n");
        return;
    }
    fclose(pf);
}
