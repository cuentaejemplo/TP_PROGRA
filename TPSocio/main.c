#include "main.h"

int main()
{
    t_indice indice;
    FILE *pf;
    t_Socio socio;
//    t_Socio socio[] = {
//    {1003,"Aguante Yo",12345687,{15,3,1990},'O',{1,1,2020},"ADULTO",{1,1,2023},'A',{0,0,0}},
//    {1001,"Juan Perez",12345678,{15,3,1990},'M',{1,1,2020},"MENOR",{1,1,2023},'A',{0,0,0}},
//    {1002,"Juan Redes",12345679,{15,3,1990},'F',{1,1,2020},"CADETE",{1,1,2023},'A',{0,0,0}}
//    };
//
    pf = fopen("socio.dat","rb");
//
//    for(int i=0; i <3 ; i++)
//        fwrite(&socio[i],sizeof(t_Socio),1,pf);

    long nro = 1001;
    unsigned tam=0;
    ind_crear(&indice,sizeof(indice),compararSocio);
    ind_cargar(&indice,"socio.dat");
    ind_recorrer(&indice,mostrarNodo,NULL);
    ind_buscar(&indice,&nro,&tam);

    fseek(pf,tam,SEEK_CUR);
    fread(&socio,sizeof(t_Socio),1,pf);
    printf("\n\n%ld %s\n", socio.NroSocio, socio.ApyNom);


    ind_vaciar(&indice);
    //ind_insertar(&indice,&nroSocio,sizeof(nroSocio));

    fclose(pf);

}
