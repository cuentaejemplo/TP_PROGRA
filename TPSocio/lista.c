#include "lista.h"

void crearLista(tLista *pl){
    *pl = NULL;
}

int ponerEnOrden(tLista *p, const void *d, unsigned cantBytes,int (*comparar)(const void *, const void *))
{
    tNodo *nue;

    while(*p && comparar((*p)->info, d) < 0)
        p = &(*p)->sig;

    if((nue = (tNodo *)malloc(sizeof(tNodo))) == NULL ||
            (nue->info = malloc(cantBytes)) == NULL)
    {
        free(nue);
        return 0;
    }
    memcpy(nue->info, d, cantBytes);
    nue->tam = cantBytes;
    nue->sig = *p;
    *p = nue;
    return 1;
}

void mostrar_lista(tLista *lista, void(mostrar)(void *))
{
    int i =0;
    while(*lista && i< 10)
    {
        mostrar((*lista)->info);
        lista = &(*lista)->sig;
        i++;
    }
}

void vaciarLista(tLista *p)
{
    while(*p)
    {
        tNodo *aux = *p;
        *p = aux->sig;
        free(aux->info);
        free(aux);
    }
}
