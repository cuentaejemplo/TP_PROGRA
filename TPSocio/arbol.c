#include "arbol.h"

void crearArbol(t_arbol *pa) {
    *pa = NULL;
}

int insertarEnOrderRecursiva(t_arbol *pa,void * info, size_t tam, int(*cmp)(const void*,const void*)) {
    int comp;
    t_nodo *nue;
    if(*pa) {
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

    if(!nue->info) {
        free(nue);
        return -1;
    }
    memcpy(nue->info,info,tam);
    nue -> tam = tam;
    nue->izq = nue->der = NULL;

    *pa = nue;
    return 1;
}

void recorrerArbolOrden(const t_arbol *pa,void (*accion)(const void *, unsigned, void *),void *param) {
    if(!*pa)
        return;

    recorrerArbolOrden(&(*pa)->izq,accion,param); //I
    accion(&(*pa)->info,(*pa)->tam,param); //R
    recorrerArbolOrden(&(*pa)->der,accion,param); //D
}

t_nodo ** buscarNodo(const t_arbol *pa,const void *info, int(*cmp)(const void*,const void*)){
    int rc=0;
    while(*pa && (rc = cmp(info,(*pa)->info))){
        if(rc < 0)
            pa=&(*pa)->izq;
        else
            pa=&(*pa)->der;
    }

    if(!*pa)
        return 0;

    return (t_nodo **)pa;
}

void vaciar_arbol(t_arbol *pa) {
    if(!*pa)
        return;

    vaciar_arbol(&(*pa)->izq);
    vaciar_arbol(&(*pa)->der);
    free((*pa)->info);
    free(*pa);
    *pa = NULL;
}
