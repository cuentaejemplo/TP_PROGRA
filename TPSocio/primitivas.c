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

//buscar v2
int ind_buscar(const t_indice* ind, void *clave, unsigned nro_reg)
{
    t_nodoa *p = ind->arbol;
    while (*p != NULL)
    {
        int cmp_res = ind->cmp(clave, (*p)->pd); 
        if (cmp_res == 0)  
        {
            memcpy(clave, (*p)->pd, MIN(ind->tam_clave, (*p)->tam));
            return 1;
        }
        else if (cmp_res < 0) 
            p = &(*p)->izq;
        else 
            p = &(*p)->der;
    }
    return 0;
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
    if (eliminar_elem_arbol_bin_busq(&(ind->arbol), clave, ind->tam_clave, ind->cmp)) 
    {
        memcpy(clave, aux->info, MIN(ind->tam_clave, aux->tam));
        free(aux);
        return 1;
    }
    return 0;
}

int ind_grabar(const t_indice* ind, const char* path)
{
    FILE* pf = fopen(path, "wb");
    if (archivo == NULL)
        return 0;
    fwrite(&(ind->tam_clave), sizeof(size_t), 1, pf);
    fwrite(&(ind->cmp), sizeof(int (*)(const void*, const void*)), 1, pf);
    fwrite(ind->arbol, sizeof(t_nodo), 1, pf);
    fclose(pf);
    return 1;
}

void ind_vaciar (t_indice* ind){
    vaciar_arbol(&ind->arbol);
}
