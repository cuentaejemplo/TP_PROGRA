#include "funcionces.h"

int compararSocio(const void *d1, const void *d2)
{
    int *dato1 = (int *)d1, *dato2 = (int *)d2;
    return *dato1 - *dato2;
}

void crearArchivoBinario(const char *path)
{
    FILE *pfT,*pfB;
    t_Socio socio;
    pfT = fopen("socios.txt","rt");

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

void mostrarSocioDadoBaja(const char *path)
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
        if(socio.Estado == 'B')
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

