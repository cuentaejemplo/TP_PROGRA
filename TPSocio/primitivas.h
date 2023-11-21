#ifndef PRIMITIVAS_H_INCLUDED
#define PRIMITIVAS_H_INCLUDED
#include <stdio.h>
#include "arbol.h"
#include "funcionces.h"
#include "fecha.h"
#include "lista.h"

typedef struct{
    unsigned tam_clave;
    int (*cmp)(const void *,const void *);
    t_arbol arbol;
}t_indice;

void ind_crear (t_indice* ind, size_t tam_clave, int (*cmp)(const void*, const void*));
int ind_insertar(t_indice *ind, void *clave, unsigned nro_reg);
int ind_cargar (t_indice* ind, const char* path);
int ind_recorrer (const t_indice* ind, void (*accion)(const void *, unsigned, void *),void* param);
int ind_buscar(const t_indice* ind, void *clave, unsigned *nro_reg);
int ind_eliminar (t_indice* ind, void *clave, unsigned nro_reg);
void recorrerYGrabar(const t_arbol *arbol, FILE *pf);
int ind_grabar(const t_indice *ind, const char *path);
void ind_vaciar (t_indice* ind);



void darAltaSocio(t_indice *ind,const char *path);
void darBajaSocio(t_indice *ind,const char *path);
void modificarSocio(t_indice *ind,const char *path);
void mostrarSocio(const void *dato, unsigned tam, void *param);
void mostrarSocioDadoBaja(const void *dato, unsigned tam, void *param);
void mostrarSocioMayorRetraso(const char *path);
void grabarArchivoIndice(const void *dato, unsigned tam, void *param);
#endif // PRIMITIVAS_H_INCLUDED
