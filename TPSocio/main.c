#include "main.h"

int main()
{
    char menu;
    t_indice indice;
    //principio del programa debo preguntar donde se encuentra el archivo txt, para poder generar archivo binario
    crearArchivoBinario(ARCH_BINARIO);
    ordenarArchivoBinario(ARCH_BINARIO);

    ind_crear(&indice,sizeof(indice),compararSocio);
    ind_cargar(&indice,ARCH_BINARIO);

    do
    {
        printf("==================================\n");
        printf("Alta nuevo socio - A\n");
        printf("Modificar socio - M\n");
        printf("Baja de socio- B\n");
        printf("Listar todo los socios- L\n");
        printf("Listar en orden- V\n");
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
            mostrarSocioDadoBaja(ARCH_BINARIO);
            system ("pause");
            break;
        case'V':
            printf("Listar los socios ordenados\n");
            mostrarSociosOrdenados(ARCH_BINARIO);
            system ("pause");
            break;
        case'P':
            printf("Listar socios con mayor retraso\n");
            system ("pause");
            break;
        }
        system("cls");
    }
    while(ES_MINISCULA(menu) != 'S');
}
