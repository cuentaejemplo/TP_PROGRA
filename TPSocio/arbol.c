#include "arbol.h"

void crearArbol(t_arbol *pa)
{
    *pa = NULL;
}

int insertarEnOrderRecursiva(t_arbol *pa,void * info, size_t tam, int(*cmp)(const void*,const void*))
{
    int comp;
    t_nodo *nue;
    if(*pa)
    {
        if((comp = cmp(info, (*pa)->info))<0)
            return insertarEnOrderRecursiva(&(*pa)->izq,info,tam,cmp);
        else if(comp > 0)
            return insertarEnOrderRecursiva(&(*pa)->der,info,tam,cmp);
        else
            return -1; //duplicado
    }
    nue = (t_nodo*)malloc(sizeof(t_nodo));
    if(!nue)
        return -1;

    nue->info = malloc(tam);

    if(!nue->info)
    {
        free(nue);
        return -1;
    }
    memcpy(nue->info,info,tam);
    nue -> tam = tam;
    nue->izq = nue->der = NULL;

    *pa = nue;
    return 1;
}

void recorrerArbolOrden(const t_arbol *pa,void (*accion)(const void *, unsigned, void *),void *param)
{
    if(!*pa)
        return;

    recorrerArbolOrden(&(*pa)->izq,accion,param); //I
    accion((*pa)->info,(*pa)->tam,param); //R
    recorrerArbolOrden(&(*pa)->der,accion,param); //D
}

t_nodo ** buscarNodo(const t_arbol *pa,const void *info, int(*cmp)(const void*,const void*))
{
    int rc=0;
    while(*pa && (rc = cmp(info,(*pa)->info)))
    {
        if(rc < 0)
            pa=&(*pa)->izq;
        else
            pa=&(*pa)->der;
    }

    if(!*pa)
        return NULL;

    return (t_nodo **)pa;
}

int altura_arbol(t_arbol *pa)
{
    int hizq, hder;
    if(!*pa)
    {
        return 0;
    }
    hizq = altura_arbol(&(*pa)->izq);
    hder = altura_arbol(&(*pa)->der);
    return (hizq>hder?hizq:hder)+1;
}


t_nodo **mayor_nodo(t_arbol *pa)
{
    if(!*pa)
    {
        return NULL;
    }
    while((*pa)->der)
        pa = &(*pa)->der;
    return pa;
}

t_nodo **menor_nodo(t_arbol *pa)
{
    if(!*pa)
    {
        return NULL;
    }
    while((*pa)->izq)
        pa = &(*pa)->izq;
    return pa;
}

int eliminar_raiz_arbol_bin_busq(t_arbol *pa)
{
    t_nodo **remp, *elim;
    if(!*pa)
        return 0;//arbol vacio
    free((*pa)->info);
    if(!(*pa)->izq && !(*pa)->der)
    {
        free(*pa);
        *pa = NULL;
        return 1; // OK
    }
    remp = altura_arbol(&(*pa)->izq)>altura_arbol(&(*pa)->der)?mayor_nodo(&(*pa)->izq):menor_nodo(&(*pa)->der);
    elim = *remp;
    (*pa)->info = elim->info;
    (*pa)->tam = elim->tam;
    *remp = elim->izq?elim->izq:elim->der;
    free(elim);
    return 1; //OK
}

int eliminar_de_arbol(t_arbol *pa, void *d, int (*cmp)(const void *,const void*))
{
    int resultado;

    while (*pa)
    {
        resultado = cmp(&(*pa)->info, d);

        if (resultado< 0)
            pa = &(*pa)->der;
        else if (resultado > 0)
            pa = &(*pa)->izq;
        else
            eliminar_raiz_arbol_bin_busq(pa);
    }

    if(!*pa)
        return 0;

    return 1;
}

void vaciar_arbol(t_arbol *pa)
{
    if(!*pa)
        return;

    vaciar_arbol(&(*pa)->izq);
    vaciar_arbol(&(*pa)->der);
    free((*pa)->info);
    free(*pa);
    *pa = NULL;
}
