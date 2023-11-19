#ifndef FUNCIONCES_H_INCLUDED
#define FUNCIONCES_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>
#include "primitivas.h"
typedef struct
{
    int Dia,
        Mes,
        Anio;
} t_Fecha;

typedef struct
{
    long NroSocio;
    char ApyNom[60];
    long DNI;
    t_Fecha FNacimiento;
    char Sexo;
    t_Fecha FAfiliacion;
    char Categoria[10];
    t_Fecha FCuotaPaga;
    char Estado;
    t_Fecha FBaja;
}t_Socio;

int compararSocio(const void *d1, const void *d2);
void mostrarNodo(const void *dato, unsigned tam, void *nose);
void crearArchivoBinario(const char *path);
void mostrarArchivoBinario(const char *path);
void ordenarArchivoBinario(const char *path);
#endif // FUNCIONCES_H_INCLUDED
