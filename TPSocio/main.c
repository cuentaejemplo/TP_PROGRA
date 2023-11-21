#include "main.h"

int main()
{
    char menu, ubicacion[20];
    t_indice indice;

    printf("Donde su ubica el archivo: ");
    gets(ubicacion);

    crearArchivoBinario(ARCH_BINARIO,ubicacion);

    ind_crear(&indice,sizeof(indice),compararSocio);
    ind_cargar(&indice,ARCH_BINARIO);

    do
    {
        printf("==================================\n");
        printf("Alta nuevo socio - A\n");
        printf("Modificar socio - M\n");
        printf("Baja de socio- B\n");
        printf("Listar todos los socios dados baja- L\n");
        printf("Listar todos los socios- V\n");
        printf("Listar socios con mayor retraso- P\n");
        printf("Salir - S\n\n");
        printf("==================================\n");

        printf("Ingrese un caracter: ");
        scanf("%c",&menu);
        fflush(stdin);

        switch(ES_MINISCULA(menu))
        {
        case'A':
                printf("Dar de alta socio\n");
            darAltaSocio(&indice,ARCH_BINARIO);
            system ("pause");
            break;
        case'M':
            printf("Modificar socio\n");
            modificarSocio(&indice,ARCH_BINARIO);
            system ("pause");
            break;
        case'B':
                printf("Baja de socio\n");
            darBajaSocio(&indice,ARCH_BINARIO);
            system ("pause");
            break;
        case'L':
            printf("Listar todo los socios fueron dados de baja\n");
            ind_recorrer(&indice,mostrarSocioDadoBaja,&indice);
            system ("pause");
            break;
        case'V':
            printf("Listar los socios ordenados\n");
            ind_recorrer(&indice,mostrarSocio,&indice);
            system ("pause");
            break;
        case'P':
            printf("Listar socios con mayor retraso\n");
            mostrarSocioMayorRetraso(ARCH_BINARIO);
            system ("pause");
            break;
        }
        system("cls");
    }
    while(ES_MINISCULA(menu) != 'S');

    ind_grabar(&indice,"socios.idx");
    ind_vaciar(&indice);
}
