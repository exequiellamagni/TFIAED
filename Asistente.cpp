#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"LibreriasTFI.h"
#include <locale.h>

void RegistrarMas(FILE *Us);
void RegistarTur(FILE *Us);
void ListAt(FILE*Us);

main()
{
	setlocale(LC_ALL,"spanish");
	FILE *Us;
	int menu=0,b=0,Is,Vi=0;
	Mascotas Aux;
	while(menu!=5)
	{
		printf("-------------------------------------------------");
		printf("\nSe encuentra en el menú de asistentes, ingrese:");
		printf("\n\n1-Iniciar sesión");
		printf("\n2-Registrar mascota");
		printf("\n3-Registrar turno");
		printf("\n4-Listado de atenciones por veterinario y fecha");
		printf("\n5-Cerrar Menú");
		printf("\n-----------------------------------------------");
		printf("\n\nIngrese la opcion: ");
		scanf("%d",&menu);
		system("CLS");
		
		switch(menu)
		{
			case 1:  Is = IniciarSesion(Us,b);
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
			 		
			 case 3:  if(Is==1)
			          {
			          	RegistarTur(Us);
			          }
			          else
			          {
			          	printf("Error: Debe iniciar sesión\n");
			          }    
		    break;
			case 4: // if(Is==1)
			         //{
			         	ListAt(Us);
			         //}
			         //else
			         //{
			         //	printf("\nError: Debe iniciar sesion\n");
			         //}
			break;  
			case 5:
			break;
			default: printf("\nEl valor ingresado no es valida."); 
			        
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
	Mascotas DatM,Aux;
	int DNIRep,band=0;
	char NomRep[60];
	
	Us = fopen("Mascotas.dat","a+b");
	if(Us == NULL)
	{
		printf("Error: No se pudo abrir el archivo\n");
	}
	else
	{	
		printf("Ingrese los siguientes datos de la mascota:\n\n");
		
		printf("\tNombre y apellido de la mascota: ");
		_flushall();
		gets(NomRep);
		strupr(NomRep);
		
		printf("\tDNI del dueño: ");
		scanf("%d",&DNIRep);
		
		rewind(Us);
		fread(&Aux,sizeof(Mascotas),1,Us);
		while(!feof(Us))
		{
			strupr(Aux.Nombre);
			
			if(Aux.DNID==DNIRep)
			{
			   	if(strcmp(Aux.Nombre,NomRep)==0)
			   	{
			   		printf("La mascota ya esta registrada.\n1-Actualizar datos\n2-No Actualizar\n\nIngrese una opcion: ");
			   		scanf("%d",&band);
			   		if(band==1)
			   		{
			   				printf("\tDomicilio: ");
							_flushall();
							gets(DatM.Dom);
		
							printf("\tLocalidad: ");
							_flushall();
							gets(DatM.Loc);
			   			
			   				printf("\tPeso de la mascota: ");
							scanf("%f",&DatM.Peso);
		
							printf("\tTelefono: ");
							_flushall();
							gets(DatM.Tel);
							
							fseek(Us,-sizeof(Mascotas),1);
							fwrite(&DatM,sizeof(Mascotas),1,Us);
							
							printf("\nDatos actualizados con exito.\n");
							fseek(Us,0,2);
			   		}
			   		
			   	}
			   	
			}
			
		    fread(&Aux,sizeof(Mascotas),1,Us);	
		}
		
		if(band==0)
		{
			strcpy(DatM.Nombre,NomRep);
			DatM.DNID=DNIRep;
			
			printf("\tDomicilio: ");
			_flushall();
			gets(DatM.Dom);
		
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
	}
	fclose(Us);
	
	
}



void RegistarTur(FILE *Us)
{
	Turnos DatP,AuxP;
	DatosVet Matri;
	Mascotas AuxM;
	FILE *Masc, *Tur;
	int band=0;
	
	printf("Ingrese el numero de matricula de el veterinario: ");
	scanf("%d",&DatP.MatV);
	
	Us = fopen("Veterinario.dat","rb");
	if(Us==NULL)
	{
		printf("\nError: No se registro ningun veterinario\n");
	}
	else
	{
       
		fread(&Matri,sizeof(DatosVet),1,Us);
		while(!feof(Us))
		{
			
			if(Matri.Mat == DatP.MatV)
			{
				
			
				Masc = fopen("Mascotas.dat","rb");
				if(Masc==NULL)
				{
					printf("\nError: no se registro ninguna mascota\n");
				}
				else
				{
					   
				        printf("Ingrese el DNI del dueño: ");
						scanf("%d",&DatP.DNIT);	
						
						printf("Ingrese el nombre de la mascota: ");
					  	_flushall();
						gets(DatP.NomMas);
					 	strupr(DatP.NomMas);
				         
					    fread(&AuxM,sizeof(Mascotas),1,Masc);
						while(!feof(Masc))
						{
					            if(strcmp(AuxM.Nombre,DatP.NomMas )==0 && AuxM.DNID == DatP.DNIT)
								{
									
									Tur = fopen("Turnos.dat","a+b");
									if(Tur==NULL)
									{
										band=1;
									}
									else
									{
										rewind(Tur);
										fread(&AuxP,sizeof(Turnos),1,Tur);
										while(!feof(Tur))
										{
											if(strcmp(AuxP.NomMas,DatP.NomMas) == 0 && AuxP.DNIT == DatP.DNIT)
											{
												printf("Ingrese la fecha de turno(DD/MM/AAAA): ");
												scanf("%d/%d/%d",&DatP.FecT.dia,&DatP.FecT.mes,&DatP.FecT.anio);
											
												strcpy(DatP.evoMasc,AuxP.evoMasc);
												DatP.borrado=false;
												fseek(Tur,-sizeof(Turnos),1);
												fwrite(&DatP,sizeof(Turnos),1,Tur);
												
												printf("Turno registrado");
							                	band=3;
												fseek(Tur,0,2);
											}
											else
											{
												band=1;
											}
										
											fread(&AuxP,sizeof(Turnos),1,Tur);
										}
										fclose(Tur);
										if(band==0 || band==2)
										{
											band=1;
										}
									}
									fseek(Masc,0,2);
							    }
								else
								{
									band=2;
								}
							
							fread(&AuxM,sizeof(Mascotas),1,Masc);
						}
						fclose(Masc);
						
				}
               fseek(Us,0,2); 
			}
			
			fread(&Matri,sizeof(DatosVet),1,Us);
		}
		
		fclose(Us);
	}
	
	if(band==1)
	{
	    Tur = fopen("Turnos.dat","ab");
		printf("Ingrese la fecha de turno(DD/MM/AAAA): ");
		scanf("%d/%d/%d",&DatP.FecT.dia,&DatP.FecT.mes,&DatP.FecT.anio);
		fwrite(&DatP,sizeof(Turnos),1,Tur);
		printf("Turno registrado");
		fclose(Tur);
	}
	else if(band==2)
	{
		printf("\nError: Mascota no registrada\n");
	}
	else if (band==0)
	{
		printf("\nError: Matricula incorrecta\n");
	}
	

}


void ListAt(FILE*Us)
{
	FILE *Aux;
    Fecha fecAux;
    int matricula;
    Mascotas AuxM;
    int band=0;
    Turnos AuxT;
    
	printf("Ingrese la matricula del veterinario: ");
	scanf("%d",&matricula);

	printf("Ingrese la fecha a buscar(DD/MM/AAAA): ");
	scanf("%d/%d/%d",&fecAux.dia,&fecAux.mes,&fecAux.anio);
	
	if(fecAux.dia > 0 && fecAux.dia < 32)
	{
		
		if(fecAux.mes > 0 && fecAux.mes < 13)
		{
			if(fecAux.anio > 2019 && fecAux.anio < 2300)
			{
				band=1;
			}
			else
			{
				printf("\nError: Año erroneo\n");
				band=2;
			}
      	}
        else
        {
        	band=2;
        	printf("\nError: Mes erroneo\n");
        }
	}
	else
	{
		band=2;
		printf("\nError: Dia erroneo\n");
	}

	
	if(band==1)
	{
		
		Us=fopen("Turnos.dat","rb");
		if(Us==NULL)
		{
			printf("\nError: No se hicieron atenciones\n");
		}
		else
		{
			fread(&AuxT,sizeof(Turnos),1,Us);
		
			while(!feof(Us))
			{
	
				if(AuxT.MatV == matricula)
				{
					if(fecAux.dia == AuxT.FecT.dia)
					{
						if(fecAux.mes == AuxT.FecT.mes)
						{
							if(fecAux.anio == AuxT.FecT.anio && AuxT.borrado==true)
							{
								
								printf("Datos de la mascota: \n");
								printf("-----------------------------------\n");
								printf("\tNombre: %s\n",AuxT.NomMas);
								printf("\tDNI del dueño: %d\n",AuxT.DNIT);
								printf("\tHistoria clinica: %s\n",AuxT.evoMasc);
								printf("-----------------------------------\n");
								    
							}
								
						}
					}
				}
				fread(&AuxT,sizeof(Turnos),1,Us);
			}
			fclose(Us);
		}
	}
	else if(band==2)
	{
		printf("El veterinario no realizo ninguna atencion en esa fecha.");
	}
}
