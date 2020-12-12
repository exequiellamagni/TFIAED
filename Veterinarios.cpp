#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"LibreriasTFI.h"
#include <locale.h>


void listaEspera(FILE *Us);


main()
{
	setlocale(LC_ALL,"spanish");
	FILE *Us;
	int menu=0, Is;
	int b=1;
	
	while(menu!=4)
	{
		printf("-------------------------------------------------");
		printf("\nSe encuentra en el menú de asistentes, ingrese:");
		printf("\n\n1-Iniciar sesión");
		printf("\n2-Visualizar lista de espera de turnos.");
		printf("\n3-Registrar evolucion de mascota.");
		printf("\n4-Cerrar Menú");
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
			 case 2:
			        if(Is == 1)
			        {
			            listaEspera(Us);
			        }
			        else
			        {
			        	printf("Para acceder, inicie sesión.\n");
					}
			break;
			
			
			
			
			       
		}
		if(menu!=4)
		{
			printf("\n\n\n");
			system("pause");
		}
		
		system("CLS");
	}
	
}

void listaEspera(FILE *Us)
{
	Fecha fecAux;
	int band=1;  //bandera
	Turnos turnAux;	
	DatosVet matriAux;	
	int matri;
	Mascotas mascAux;	
	FILE *aux;
			
	while(band==1)
	{
		printf("Ingrese la fecha de hoy. Ej(DD/MM/AAAA): ");
		scanf("%d/%d/%d",&fecAux.dia,&fecAux.mes,&fecAux.anio);
		
		if(fecAux.dia > 0 && fecAux.dia < 32)
		{
			if(fecAux.mes > 0 && fecAux.mes < 13)
			{
				if(fecAux.anio > 2019 && fecAux.anio < 2300)
				{
					Us = fopen("Turnos.dat","rb");
					if(Us == NULL)
					{
						printf("\nNo se han encontrado turnos.\n");
					}
					else
					{
						fread(&turnAux,sizeof(Turnos),1,Us);
						while(!feof(Us))
						{
							if(fecAux.dia == turnAux.FecT.dia && fecAux.mes == turnAux.FecT.mes && fecAux.anio == turnAux.FecT.anio)
							{
								printf("Ingrese la matricula: ");
								scanf("%d",&matri);
						
					
								aux=fopen("Veterinario.dat","rb");
								if(aux==NULL)
								{
									printf("Error: No se pudo abrir el archivo.\n");
								}
								else
								{
									fread(&matriAux,sizeof(DatosVet),1,aux);
									while(!feof(aux))
									{
										if(matriAux.Mat == matri)
										{
											band=0;
											fseek(aux,0,2);
											fseek(Us,0,2);
										}
										fread(&matriAux,sizeof(DatosVet),1,aux);
									}
									if(band==1)
									{
										printf("Error: Matricula incorrecta.\n");
									}
								}
							}
							fread(&turnAux,sizeof(Turnos),1,Us);
						}
						if(band==1)
						{
							printf("No hay turnos disponibles hoy.\n");
						}
						fclose(Us);	
					}
				}
				else
				{
					printf("Error: Año de turno erróneo.\n");
				}
			}
			else
			{
				printf("Error: Mes de turno erróneo.\n");
			}
		}
		else
		{
			printf("Error: Dia de turno erróneo.\n");
		}
		if(band==1)
		{
			printf("1-Volver a ingresar una fecha, 2-Volver al menu.\n");
			scanf("%d",&band);
		}
	}
	
	
	if(band==0)
	{
		Us = fopen("Turnos.dat","rb");
		
		if(Us == NULL)
		{
			printf("Error: No se pudo leer el archivo.\n");
		}
		else
		{
			fread(&turnAux,sizeof(Turnos),1,Us);
			while(!feof(Us))
			{
				if(fecAux.dia == turnAux.FecT.dia && fecAux.mes == turnAux.FecT.mes && fecAux.anio == turnAux.FecT.anio)
				{
					if(matri == turnAux.MatV)
					{
						aux = fopen("Mascotas.dat","rb");
						if(aux==NULL)
						{
							printf("Error: No hay ninguna mascota registrada.\n");
						}
						else
						{
							fread(&mascAux,sizeof(Mascotas),1,aux);
							while(!feof(aux))
							{
								if(mascAux.DNID == turnAux.DNIT)
								{
									printf("DATOS DEL TURNO:\n");
									printf("--------------------------------------------------\n");
									printf("Nombre de la mascota: ");
									puts(mascAux.Nombre);
									printf("Fecha de nacimiento: %d/%d/%d\n",mascAux.fecNac.dia,mascAux.fecNac.mes,mascAux.fecNac.anio);
									printf("Peso: %2.f\n",mascAux.Peso);
									printf("--------------------------------------------------\n");
								}
								else
								{
									
								}
								fread(&mascAux,sizeof(Mascotas),1,aux);
							}
						}
					}
				}
			    fread(&turnAux,sizeof(Turnos),1,Us);
			}
		    fclose(Us);
			
		}
	}
	
	
	
	
	
	
}














