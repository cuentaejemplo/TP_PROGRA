#ifndef ARBOL_H_INCLUDED
#define ARBOL_H_INCLUDED

#include <stdlib.h>
#include <string.h>
#define MAX(x,y) ((x) > (y) ? (x) : (y))
#define MIN(x,y) ((x) > (y) ? (x) : (y))

typedef struct s_nodo{
    void *info;
    size_t tam;
    struct s_nodo *izq, *der;
}t_nodo;

typedef t_nodo * t_arbol;

void crearArbol(t_arbol *arbol);
int insertarEnOrderRecursiva(t_arbol *pa,void * info, size_t tam, int(*cmp)(const void*,const void*));
void recorrerArbolOrden(const t_arbol *pa,void (*accion)(const void *, unsigned, void *),void *param);
t_nodo ** buscarNodo(const t_arbol *pa,const void *info, int(*cmp)(const void*,const void*));
void vaciar_arbol(t_arbol *pa);
#endif // ARBOL_H_INCLUDED
