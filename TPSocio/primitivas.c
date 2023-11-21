#include "primitivas.h"

void ind_crear (t_indice* ind, size_t tam_clave, int (*cmp)(const void*, const void*))
{
    ind->tam_clave= tam_clave;
    ind->cmp = cmp;
//    ind->arbol = NULL;
    crearArbol(&ind->arbol);
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
    int i = 0;
    pf = fopen(path,"rb");

    if(!pf)
    {
        printf("No pudo abrir el archivo\n");
        return 0;
    }

    fread(&socio,sizeof(t_Socio),1,pf);


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

void recorrerYGrabar(const t_arbol *arbol, FILE *pf)
{
    if (*arbol)
    {
        void * nue = malloc((*arbol)->tam);
        memcpy(nue, (*arbol)->info, (*arbol)->tam);
        fwrite(nue, (*arbol)->tam, 1, pf);
        free(nue);
    }
}

void grabarArchivoIndice(const void *dato, unsigned tam, void *param)
{

    FILE *pf = (FILE *)param;

    long *d1 = (long *)dato;

    fwrite(d1,sizeof(long),1,pf);

//dato = nrosocio
//tam = toda la informacion del ARBOL
//param = pf
}

int ind_grabar(const t_indice *ind, const char *path)
{
    FILE *pf;

    pf = fopen(path, "wb");

    if(!pf)
    {
        printf("No pudo abrir el archivo para grabar el índice");
        return 0;
    }

    recorrerArbolOrden(&ind->arbol,grabarArchivoIndice,pf);

    fclose(pf);

    return 1;
}

int ind_eliminar(t_indice* ind, void *clave, unsigned nro_reg)
{
    t_nodo **p = &(ind->arbol);
    int cmp_res;
    while (*p != NULL && (cmp_res = ind->cmp(clave, (*p)->info)) != 0)
    {
        if (cmp_res < 0)
            p = &(*p)->izq;
        else
            p = &(*p)->der;
    }
    if (*p == NULL)
        return 0;
    t_nodo *aux = *p;
    if (eliminar_de_arbol(&(ind->arbol), clave, ind->cmp))
    {
        memcpy(clave, aux->info, MIN(ind->tam_clave, aux->tam));
        free(aux);
        return 1;
    }
    return 0;
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
    size_t sumSocios;
    t_Socio socio,nuevoSocio;
    int i=0,encontrado=0;
    char *opciones[] = {"MENOR", "CADETE", "ADULTO", "VITALICIO", "HONORARIO", "JUBILADO"};

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
            printf("\nNumero socio existente\n");
            fseek(pf,pos*sizeof(t_Socio),SEEK_SET);
            fread(&socio,sizeof(t_Socio),1,pf);

            if(socio.Estado == 'B')
            {
                socio.FBaja.Dia =0;
                socio.FBaja.Mes =0;
                socio.FBaja.Anio =0;
                socio.Estado = 'A';
                fseek(pf,pos*sizeof(t_Socio),SEEK_SET);
                fwrite(&socio,sizeof(t_Socio),1,pf);
                printf("Se dio de alta existosamente\n");
            }

            fclose(pf);
            return;
        }
        else
        {
            printf("\nIngrese DNI: ");
            scanf("%ld", &nuevoSocio.DNI);
            fflush(stdin);
            if(nuevoSocio.DNI > 10000 && nuevoSocio.DNI < 100000000)
            {
                fread(&socio,sizeof(t_Socio),1,pf);
                while(!feof(pf))
                {
                    if(compararDNI(nuevoSocio.DNI,socio.DNI)== 0)
                    {
                        printf("Numero de DNI existente\n");
                        fclose(pf);
                        return;
                    }
                    fread(&socio,sizeof(t_Socio),1,pf);
                }

                printf("\nIngrese Apellido y Nombre: ");
                gets(nuevoSocio.ApyNom);
                fflush(stdin);

                printf("Ingrese Fecha de nacimiento(dd/mm/aaaa): ");
                scanf("%d/%d/%d",
                      &nuevoSocio.FNacimiento.Dia,
                      &nuevoSocio.FNacimiento.Mes,
                      &nuevoSocio.FNacimiento.Anio);
                fflush(stdin);

                printf("Ingrese Sexo(F,O,M): ");
                scanf(" %c", &nuevoSocio.Sexo);
                fflush(stdin);

                printf("Ingrese fecha de ultima paga(dd/mm/aaaa): ");
                scanf("%d/%d/%d",
                      &nuevoSocio.FCuotaPaga.Dia,
                      &nuevoSocio.FCuotaPaga.Mes,
                      &nuevoSocio.FCuotaPaga.Anio);
                fflush(stdin);

                printf("Ingrese fecha afiliacion(dd/mm/aaaa): ");
                scanf("%d/%d/%d",
                      &nuevoSocio.FAfiliacion.Dia,
                      &nuevoSocio.FAfiliacion.Mes,
                      &nuevoSocio.FAfiliacion.Anio);
                fflush(stdin);

                printf("Ingrese categoria: [MENOR, CADETE, ADULTO, VITALICO, HONORARIO, JUBILADO] ");
                gets(nuevoSocio.Categoria);
                fflush(stdin);
                for (i = 0; i < 6; i++)
                {
                    if (strcmp(nuevoSocio.Categoria , opciones[i]) == 0)
                    {
                        encontrado = 1;
                        break;
                    }
                }
                if(encontrado)
                {
                    nuevoSocio.FBaja.Dia = nuevoSocio.FBaja.Mes = nuevoSocio.FBaja.Anio =0;

                    fseek(pf, 0, SEEK_END);
                    sumSocios = ftell(pf) / sizeof(t_Socio);

                    ind_insertar(ind, &nroSocio, sumSocios);

                    nuevoSocio.NroSocio = nroSocio;
                    nuevoSocio.Estado = 'A';

                    fwrite(&nuevoSocio, sizeof(t_Socio), 1, pf);
                    printf("\nAgregado con Exito!\n");
                    fclose(pf);
                    return;
                }else{
                    printf("Categoria incorrecta\n");
                    fclose(pf);
                    return;
                }
            }
            else
            {
                printf("Numero de DNI Invalido\n");
                fclose(pf);
                return;
            }
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

    printf("\nIngrese el numero de socio: ");
    scanf("%ld",&nroSocio);

    if(nroSocio > 1 && nroSocio < 10000000)
    {
        if(ind_buscar(ind,&nroSocio,&pos))
        {
            printf("\nSe encontro el numero socio\n");
            fseek(pf,pos*sizeof(t_Socio),SEEK_SET);
            fread(&socio,sizeof(t_Socio),1,pf);
            printf("%ld %s\n", socio.NroSocio,socio.ApyNom);

            if(socio.Estado == 'B')
            {
                printf("\nEl numero socio ya se encuentra dado de baja.\n");
                fclose(pf);
                return;
            }

            printf("\nIngrese el dia: ");
            scanf("%d",&dia);

            printf("\nIngrese el mes: ");
            scanf("%d",&mes);

            printf("\nIngrese el anio: ");
            scanf("%d",&anio);

            if(validarFecha(dia,mes,anio))
            {
                socio.Estado = 'B';
                socio.FBaja.Dia = dia;
                socio.FBaja.Mes = mes;
                socio.FBaja.Anio = anio;

                fseek(pf,pos*sizeof(t_Socio),SEEK_SET);
                fwrite(&socio,sizeof(t_Socio),1,pf);

                ind_eliminar(ind, &nroSocio, pos);

                printf("Se dio de baja existosamente.\n");
            }
            else
            {
                printf("\nFecha invalida\n");
            }

            fclose(pf);
            return;
        }
        else
        {
            printf("\nNro socio no existe.\n");
            fclose(pf);
            return;
        }
    }
    else
    {
        printf("\nNro socio invalido.\n");
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

void mostrarSocioDadoBaja(const void *dato, unsigned tam, void *param)
{
    FILE *pf;
    t_Socio socio;
    t_indice *indice = (t_indice *)param;
    int *nroSocio = (int *)dato;
    unsigned pos=0;
    ind_buscar(indice,nroSocio,&pos);

    pf= fopen("./socio.dat","rb");

    if(!pf)
    {
        printf("No se pudo abrir el archivo\n");
        return;
    }

    fseek(pf, pos * sizeof(t_Socio),SEEK_SET);
    fread(&socio,sizeof(t_Socio),1,pf);

    if(socio.Estado == 'B')
    {
        printf("%ld %s %ld\n", socio.NroSocio, socio.ApyNom, socio.DNI);
    }

    fclose(pf);
}

void mostrarSocio(const void *dato, unsigned tam, void *param)
{
    FILE *pf;
    t_Socio socio;
    t_indice *indice = (t_indice *)param;
    int *nroSocio = (int *)dato;
    unsigned pos=0;
    ind_buscar(indice,nroSocio,&pos);

    pf= fopen("./socio.dat","rb");

    if(!pf)
    {
        printf("No se pudo abrir el archivo\n");
        return;
    }

    fseek(pf, pos * sizeof(t_Socio),SEEK_SET);
    fread(&socio,sizeof(t_Socio),1,pf);

    if(socio.Estado != 'B')
    {
        printf("%ld %s %ld\n", socio.NroSocio, socio.ApyNom, socio.DNI);
    }

    fclose(pf);
}

void mostrarSocioMayorRetraso(const char *path)
{
    FILE *pf;
    t_Socio socio;
    pf= fopen(path,"rb");
    tLista lista;

    if(!pf)
    {
        printf("No se pudo abrir el archivo\n");
        return;
    }
    crearLista(&lista);

    fread(&socio,sizeof(t_Socio),1,pf);

    while(!feof(pf))
    {
        ponerEnOrden(&lista,&socio,sizeof(t_Socio),compararFecha);
        fread(&socio,sizeof(t_Socio),1,pf);
    }

    mostrar_lista(&lista,mostrarNumeroSocio);

    vaciarLista(&lista);
    fclose(pf);
}
