#ifndef LISTA_H_INCLUDED
#define LISTA_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct sNodo
{
    void *info;
    unsigned tam;
    struct sNodo *sig;
} tNodo;

typedef tNodo *tLista;

void crearLista(tLista *pl);
int ponerEnOrden(tLista *p, const void *d, unsigned cantBytes,int (*comparar)(const void *, const void *));
void mostrar_lista(tLista *lista, void(mostrar)(void *));
void vaciarLista(tLista *p);

#endif // LISTA_H_INCLUDED
