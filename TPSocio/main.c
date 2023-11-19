#include "main.h"

int main()
{
    char menu;
    t_indice indice;

    //principio del programa debo preguntar donde se encuentra el archivo txt, para poder generar archivo binario
    crearArchivoBinario("socio.dat");
    ordenarArchivoBinario("socio.dat");

    ind_crear(&indice,sizeof(indice),compararSocio);

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
            system ("pause");
            break;
        case'M':
            printf("Modificar socio\n");
            system ("pause");
            break;
        case'B':
            printf("Baja de socio\n");
            system ("pause");
            break;
        case'L':
            printf("Listar todo los socios fueron dados de baja\n");
            system ("pause");
            break;
        case'V':
            printf("Listar los socios ordenados\n");
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
