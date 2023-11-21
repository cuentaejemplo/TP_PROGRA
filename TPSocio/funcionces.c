#include "funcionces.h"

int compararSocio(const void *d1, const void *d2)
{
    int *dato1 = (int *)d1, *dato2 = (int *)d2;
    return *dato1 - *dato2;
}

long compararDNI(long d1, long d2)
{
    return d1-d2;
}

int compararFecha(const void *d1,const void *d2)
{
    const t_Socio *socio1 = (t_Socio *)d1,
                   *socio2 = (t_Socio *)d2;

    if( (socio1->FCuotaPaga.Anio - socio2->FCuotaPaga.Anio) == 0)
    {
        if((socio1->FCuotaPaga.Mes - socio2->FCuotaPaga.Mes) == 0)
        {
            return socio1->FCuotaPaga.Dia - socio2->FCuotaPaga.Dia;
        }
        else
        {
            return socio1->FCuotaPaga.Mes - socio2->FCuotaPaga.Mes;
        }
    }

    return socio1->FCuotaPaga.Anio - socio2->FCuotaPaga.Anio;
}
void mostrarNumeroSocio(void *d1)
{
    long *nroSocio = (long *)d1;
    printf("%ld \n", *nroSocio);
}

void crearArchivoBinario(const char *path, const char *pathTexto)
{
    FILE *pfT,*pfB;
    t_Socio socio;
    pfT = fopen(pathTexto,"rt");

    if(!pfT)
    {
        printf("No pudo abrir el archivo texto\n");
        return;
    }

    pfB = fopen(path,"wb");

    if(!pfB)
    {
        printf("No pudo abrir el archivo binario\n");
        fclose(pfT);
        return;
    }

    while(!feof(pfT))
    {
        fscanf(pfT,"%ld|%49[^|]|%ld|%d/%d/%d|%c|%d/%d/%d|%9[^|]|%d/%d/%d|%c|%d/%d/%d\n",
               &socio.NroSocio,
               socio.ApyNom,
               &socio.DNI,
               &socio.FNacimiento.Dia,
               &socio.FNacimiento.Mes,
               &socio.FNacimiento.Anio,
               &socio.Sexo,
               &socio.FAfiliacion.Dia,
               &socio.FAfiliacion.Mes,
               &socio.FAfiliacion.Anio,
               socio.Categoria,
               &socio.FCuotaPaga.Dia,
               &socio.FCuotaPaga.Mes,
               &socio.FCuotaPaga.Anio,
               &socio.Estado,
               &socio.FBaja.Dia,
               &socio.FBaja.Mes,
               &socio.FBaja.Anio
              );
        fwrite(&socio,sizeof(socio),1,pfB);
    }

    fclose(pfT);
    fclose(pfB);

}

void mostrarArchivoBinario(const char *path)
{
    FILE *pf;
    t_Socio socio;
    pf = fopen(path,"rb");

    if(!pf)
    {
        printf("No se pudo abrir el archivo\n");
        return;
    }
    fread(&socio,sizeof(t_Socio),1,pf);

    while(!feof(pf))
    {
        printf("%ld %s %ld %d/%d/%d %s %c %d/%d/%d %d/%d/%d %c\n",
               socio.NroSocio,
               socio.ApyNom,
               socio.DNI,
               socio.FNacimiento.Dia,
               socio.FNacimiento.Mes,
               socio.FNacimiento.Anio,
               socio.Categoria,
               socio.Sexo,
               socio.FAfiliacion.Dia,
               socio.FAfiliacion.Mes,
               socio.FAfiliacion.Anio,
               socio.FBaja.Dia,
               socio.FBaja.Mes,
               socio.FBaja.Anio,
               socio.Estado
              );
        fread(&socio,sizeof(t_Socio),1,pf);
    }

    fclose(pf);
}

void ordenarArchivoBinario(const char *path)
{
    FILE *pf;
    int cant=0;
    t_Socio *socio = NULL;
    pf = fopen(path,"r+b");

    if(!pf)
    {
        printf("No se pudo abrir el archivo\n");
        return;
    }

    fseek(pf, 0, SEEK_END);
    cant = ftell(pf) / sizeof(t_Socio);
    socio= malloc(ftell(pf));

    if(!socio)
    {
        printf("No se pudo reservar memoria\n");
        return;
    }

    rewind(pf);

    fread(socio,sizeof(t_Socio),cant,pf);

    qsort(socio,cant,sizeof(t_Socio),compararSocio);
    rewind(pf);
    fwrite(socio, sizeof(t_Socio), cant, pf);

    free(socio);
    fclose(pf);
}

void mostrarSociosOrdenados(const char *path)
{
    FILE *pf;
    t_Socio socio;
    pf = fopen(path,"rb");

    if(!pf)
    {
        printf("No se pudo abrir el archivo\n");
        return;
    }
    fread(&socio,sizeof(t_Socio),1,pf);

    while(!feof(pf))
    {
        if(socio.Estado != 'B')
            printf("%ld %s %ld %d/%d/%d %s %c %d/%d/%d %d/%d/%d %d/%d/%d %c\n",
                   socio.NroSocio,
                   socio.ApyNom,
                   socio.DNI,
                   socio.FNacimiento.Dia,
                   socio.FNacimiento.Mes,
                   socio.FNacimiento.Anio,
                   socio.Categoria,
                   socio.Sexo,
                   socio.FCuotaPaga.Dia,
                   socio.FCuotaPaga.Mes,
                   socio.FCuotaPaga.Anio,
                   socio.FAfiliacion.Dia,
                   socio.FAfiliacion.Mes,
                   socio.FAfiliacion.Anio,
                   socio.FBaja.Dia,
                   socio.FBaja.Mes,
                   socio.FBaja.Anio,
                   socio.Estado
                  );

        fread(&socio,sizeof(t_Socio),1,pf);
    }

    fclose(pf);
}

void mostrarArchivoIndice(const char *path)
{
    FILE *pf;
    long nroSocio;
    pf = fopen(path,"rb");

    if(!pf)
    {
        printf("No se pudo abrir el archivo\n");
        return;
    }
    fread(&nroSocio,sizeof(long),1,pf);

    while(!feof(pf))
    {
        printf("%ld\n",nroSocio);
        fread(&nroSocio,sizeof(long),1,pf);
    }

    fclose(pf);
}
