#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"LibreriasTFI.h"
#include <locale.h>

struct Fecha
{
	int dia,mes,anio;
};

struct Mascotas
{
	char Nombre[60],Dom[60],Loc[60],Tel[25];
	int DNID;
    Fecha fecNac;
    float Peso;
};

struct Turnos
{
	int MatV,DNI;
	Fecha fecTurn;
	char Det[380];
};
void RegistrarMas(FILE *Us);

main()
{
	setlocale(LC_ALL,"spanish");
	FILE *Us;
	int menu=0,b=0,Is,Vi=0;
	
	while(menu!=5)
	{
		printf("-------------------------------------------------");
		printf("\nSe encuentra en el menú de asistentes, ingrese:");
		printf("\n\n1-Iniciar sesión");
		printf("\n2-Registrar mascota");
		printf("\n3-Regisrar turno");
		printf("\n4-Listado de atenciones por veterinario y fecha");
		printf("\n5-Cerrar Menú");
		printf("\n-----------------------------------------------");
		printf("\n\nIngrese la opcion: ");
		scanf("%d",&menu);
		system("CLS");
		
		switch(menu)
		{
			case 1: Is = IniciarSesion(Us,b);
			        if(Is == 1)
			        {
			            printf("\nSesión iniciada\n");
			        }
			 break;
			
			 case 2:  if(Is==1)
			          {
			          	RegistrarMas(Us);
			          }
			          else
			          {
			          	printf("Error: Debe iniciar sesión\n");
			          }
			 break;
			 		        
			        
		}
		if(menu!=5)
		{
			printf("\n\n\n");
			system("pause");
		}
		
		system("CLS");
	}
	
}

void RegistrarMas(FILE *Us)
{
	Mascotas DatM;
	
	Us = fopen("Mascotas.dat","ab");
	if(Us == NULL)
	{
		printf("Error: No se pudo abrir el archivo\n");
	}
	else
	{
		printf("Ingrese los siguientes datos de la mascota:\n\n");
		
		printf("\tNombre y apellido de la mascota: ");
		_flushall();
		gets(DatM.Nombre);
		
		printf("\tDomicilio: ");
		_flushall();
		gets(DatM.Dom);
		
		printf("\tDNI del dueño: ");
		scanf("%d",&DatM.DNID);
		
		printf("\tLocalidad: ");
		_flushall();
		gets(DatM.Loc);
		
		printf("\tFecha de nacimiento (DD/MM/AAAA): ");
		scanf("%d/%d/%d",&DatM.fecNac.dia,&DatM.fecNac.mes,&DatM.fecNac.anio);
		
		printf("\tPeso de la mascota: ");
		scanf("%f",&DatM.Peso);
		
		printf("\tTelefono: ");
		_flushall();
		gets(DatM.Tel);
		
		fwrite(&DatM,sizeof(Mascotas),1,Us);
		
	}
	fclose(Us);
}



