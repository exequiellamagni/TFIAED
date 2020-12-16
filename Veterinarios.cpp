#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"LibreriasTFI.h"
#include <locale.h>


void listaEspera(FILE *Us);
void evolucionMascota(FILE *Us);

main()
{
	setlocale(LC_ALL,"spanish");
	FILE *Us;
	int menu=0, Is=1;
	int b=1;
	
	while(menu!=4)
	{
		printf("-------------------------------------------------");
		printf("\nSe encuentra en el menú de veterinarios, ingrese:");
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
			case 3: 
					if(Is == 1)
					{
						evolucionMascota(Us);
					}
					else
					{
						printf("Para acceder, inicie sesion.\n");
					}
			break;
			case 4:break;
			default: printf("Error: número no valido");
     
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
	Turnos turnAux,AuxT;	
	DatosVet matriAux;	
	int matri,k=1;
	Mascotas mascAux;	
	FILE *aux,*Us2;
			
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
							if(fecAux.dia == turnAux.FecT.dia && fecAux.mes == turnAux.FecT.mes && fecAux.anio == turnAux.FecT.anio && turnAux.borrado==false)
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
								if(mascAux.DNID == turnAux.DNIT && turnAux.borrado == false && strcmp(mascAux.Nombre,turnAux.NomMas)==0)
								{
									printf("DATOS DEL TURNO:\n");
									printf("--------------------------------------------------\n");
									printf("Nombre de la mascota: ");
									puts(turnAux.NomMas);
									if((mascAux.fecNac.anio - fecAux.anio)>0)
									{
										printf("Edad: %d años\n",fecAux.anio - mascAux.fecNac.anio);
									}
									else if((mascAux.fecNac.mes - fecAux.mes) > 0)
									{
										printf("Edad: %d meses\n",fecAux.mes - mascAux.fecNac.mes);
									}
									else
									{
										printf("Edad: %d dias\n",fecAux.dia - mascAux.fecNac.dia);
									}									
									printf("Peso: %2.f\n",mascAux.Peso);
									printf("Localidad: %s\n",mascAux.Loc);
									printf("DNI del dueño: %d\n",mascAux.DNID);
									printf("\n\nEVOLUCION REGISTRADA DE LA MASCOTA:\n");
									
									Us2 = fopen("Turnos.dat","rb");
									fread(&AuxT,sizeof(Turnos),1,Us2);
									while(!feof(Us2))
									{
										if(strcmp(AuxT.NomMas,turnAux.NomMas)==0 && AuxT.borrado==true)
										{
											printf("%s - ",AuxT.evoMasc);
											k=0;
										}
										fread(&AuxT,sizeof(Turnos),1,Us2);	
									}
									fclose(Us2);
									if(k==1)
									{
										printf("No hay evalucion registrado\n");
									}
									printf("\n--------------------------------------------------\n");
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


void evolucionMascota(FILE *Us)
{
	char auxNom[60];
	Turnos AuxT;
	int band=0,i=0;
	
	Us = fopen("Turnos.dat","r+b");
	if(Us==NULL)
	{
		printf("Error: Todavia no se registron turnos");
	}
	else
	{
		printf("Ingrese: \n\n");
		printf("Nombre de la mascota: ");
		_flushall();
		gets(auxNom);
		strupr(auxNom);
		fread(&AuxT,sizeof(Turnos),1,Us);
		while(feof(Us)==0 && band==0)
		{
			if(strcmp(auxNom,AuxT.NomMas)==0 && AuxT.borrado == false)
			{
				printf("\nEvolucion de la mascota: ");
				_flushall();
		        gets(AuxT.evoMasc);
		        AuxT.borrado=true;
		        fseek(Us,i*sizeof(Turnos),0);
		        fwrite(&AuxT,sizeof(Turnos),1,Us);
		        band=1;
		        
			}
			else
			{
				
				fread(&AuxT,sizeof(Turnos),1,Us);	
			}
			i++;
		}
		fclose(Us);
	}
	
	if(band!=1)
	{
		printf("\n\nError: Esta mascota no tiene turno\n\n");
	}
	else
	{
		printf("\n\nEvolucion guardada con exito\n\n");
	}
}














