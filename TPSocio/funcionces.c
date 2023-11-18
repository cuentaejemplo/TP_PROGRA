#include "funcionces.h"

int compararSocio(const void *d1, const void *d2){
    int *dato1 = (int *)d1, *dato2 = (int *)d2;
    return *dato1 - *dato2;
}

void mostrarNodo(const void *dato, unsigned tam, void *nose){
    t_indice *ind = (t_indice *)dato;
    long puntero_long = *(long *)ind->clave;

    printf("%ld\n", puntero_long);
}
