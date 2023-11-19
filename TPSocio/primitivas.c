#include "primitivas.h"

void ind_crear (t_indice* ind, size_t tam_clave, int (*cmp)(const void*, const void*))
{
    ind->nro_reg= tam_clave;
    ind->cmp = cmp;
    ind->arbol = NULL;
}

int ind_insertar(t_indice *ind, void *clave, unsigned nro_reg)
{
    void *aux_reg_ind = malloc(ind->nro_reg + sizeof(unsigned));
    if (!aux_reg_ind)
    {
        return -1;
    }

    memcpy(aux_reg_ind, clave, ind->nro_reg);

    memcpy(aux_reg_ind + ind->nro_reg, &nro_reg, sizeof(unsigned));

    if(!insertarEnOrderRecursiva(&ind->arbol,aux_reg_ind,ind->nro_reg+sizeof(unsigned),
                        ind->cmp))
    {
        free(aux_reg_ind);
        return 0;
    }

    free(aux_reg_ind);

    return 1;
}

int ind_cargar (t_indice* ind, const char* path){
    t_Socio socio;
    FILE *pf;

    pf = fopen(path,"rb");

    if(!pf){
        printf("No pudo abrir el archivo\n");
        return 0;
    }

    fread(&socio,sizeof(t_Socio),1,pf);

    while(!feof(pf)){
        ind_insertar(ind,&socio.NroSocio,sizeof(t_Socio));
        fread(&socio,sizeof(t_Socio),1,pf);
    }

    fclose(pf);
    return 1;
}

int ind_recorrer (const t_indice* ind, void (*accion)(const void *, unsigned, void *),void* param){
    recorrerArbolOrden(&ind->arbol,accion,param);
    return 1;
}

int ind_buscar(const t_indice* ind, void *clave, unsigned *nro_reg)
{
    t_nodo **nodo = buscarNodo(&ind->arbol, clave, ind->cmp);
    if (!nodo)
    {
        printf("No se encontro el Nro socio\n");
        return 0;
    }

    memcpy(nro_reg,(*nodo)->info + ind->nro_reg, sizeof(unsigned));

    return 1;
}

void ind_vaciar (t_indice* ind){
    vaciar_arbol(&ind->arbol);
}
