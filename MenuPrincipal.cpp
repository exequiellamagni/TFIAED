#include <stdlib.h>
#include <stdio.h>


main()
{
	int menu;
	while(menu!=4)
	{
		printf("-------------------------------------------------\n");
		printf("Se encuentra en el menu principal: \n\n");
		printf("1-Ingresar al modulo de Administracion\n");
		printf("2-Ingrear al modulo de asistente\n");
		printf("3-Ingresar al modulo de veterinarios\n");
		printf("4-Cerrar programa\n");
		printf("-------------------------------------------------");
		printf("\nIngrese la opcion: ");
		scanf("%d",&menu);
		system("CLS");
		
		switch(menu)
		{
			case 1: system("Administracion");
			break;
			case 2: system("Asistente");
			break;
			case 3: system("Veterinarios");
			break;
			case 4: printf("Hasta pronto, que tenga un buen dia");
			break;
			default: printf("Error el numero ingresado no es valido");
		}
		if(menu!=4)
		{
			printf("\n\n\n");
		    system("pause");
		}
		
		system("CLS");
	}
}
