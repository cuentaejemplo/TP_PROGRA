#include "fecha.h"

int esBisiesto(int anio)
{
    if ((anio % 4 == 0 && anio % 100 != 0) || (anio % 400 == 0))
    {
        return 1; // Es bisiesto
    }
    else
    {
        return 0; // No es bisiesto
    }
}

int validarFecha(int dia,int mes, int anio)
{
    if(validarAnio(anio))
    {
        if(mes == 1 || mes == 3 || mes == 5 || mes == 7 || mes == 8 || mes == 10 || mes == 12)
        {
            if(dia >= 1 && dia <=31)
                return 1;
        }
        else
        {
            if(mes == 4 || mes == 6 || mes == 9 || mes == 11)
            {
                if(dia >= 1 && dia <=30)
                    return 1;
            }
            else
            {
                if(mes ==2)
                {
                    if(esBisiesto(anio))
                    {
                        if(dia >= 1 && dia <= 29)
                            return 1;
                    }
                    else
                    {
                        if(dia >= 1 && dia <= 28)
                            return 1;
                    }
                }
            }
        }
    }

    printf("\nFecha ingresada invalida\n");
    return 0;
}

int validarAnio(int anio)
{
    if(anio > 0)
        return 1;

    return 0;
}
