#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"LibreriasTFI.h"
#include <locale.h>



void RegistrarMas(FILE *Us);
void RegistarTur(FILE *Us);

main()
{
	setlocale(LC_ALL,"spanish");
	FILE *Us;
	int menu=0,b=0,Is,Vi=0;
	
	while(menu!=5)
	{
		printf("-------------------------------------------------");
		printf("\nSe encuentra en el men� de asistentes, ingrese:");
		printf("\n\n1-Iniciar sesi�n");
		printf("\n2-Registrar mascota");
		printf("\n3-Registrar turno");
		printf("\n4-Listado de atenciones por veterinario y fecha");
		printf("\n5-Cerrar Men�");
		printf("\n-----------------------------------------------");
		printf("\n\nIngrese la opcion: ");
		scanf("%d",&menu);
		system("CLS");
		
		switch(menu)
		{
			case 1: Is = IniciarSesion(Us,b);
			        if(Is == 1)
			        {
			            printf("\nSesi�n iniciada\n");
			        }
			 break;
			
			 case 2:  if(Is==1)
			          {
			          	RegistrarMas(Us);
			          }
			          else
			          {
			          	printf("Error: Debe iniciar sesi�n\n");
			          }
			 break;
			 		
			 case 3:  if(Is==1)
			          {
			          	RegistarTur(Us);
			          }
			          else
			          {
			          	printf("Error: Debe iniciar sesi�n\n");
			          }    
		    break;
			case 4: menu=5;
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
		
		printf("\tDNI del due�o: ");
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
			    	
				printf("Ingrese el DNI del due�o: ");
				scanf("%d",&DatP.DNIT);	
				
				Masc = fopen("Mascotas.dat","rb");
				if(Masc==NULL)
				{
					printf("\nError: no se registro ninguna mascota\n");
				}
				else
				{
					    printf("Ingrese el nombre de la mascota: ");
					    _flushall();
					    gets(DatP.NomMas);
					    strupr(DatP.NomMas);
					    
						fread(&AuxM,sizeof(Mascotas),1,Masc);
						while(!feof(Masc))
						{
							
							if(AuxM.DNID == DatP.DNIT && strcmp(AuxM.Nombre,DatP.NomMas)==0)
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
										if(strcmp(AuxP.NomMas,DatP.NomMas)==0 && AuxP.DNIT == DatP.DNIT)
										{
											printf("Ingrese la fecha de turno(DD/MM/AAAA): ");
											scanf("%d/%d/%d",&DatP.FecT.dia,&DatP.FecT.mes,&DatP.FecT.anio);
											
											strcpy(DatP.evoMasc,AuxP.evoMasc);
											DatP.borrado=false;
											fseek(Tur,-sizeof(Turnos),1);
											fwrite(&DatP,sizeof(Turnos),1,Us);
											
											printf("Turno registrado");
							                band=3;
											fseek(Tur,0,2);
											fseek(Masc,0,2);
											fseek(Us,0,2);
										
										}
										else
										{
											band=1;
										}
										
										fread(&AuxP,sizeof(Turnos),1,Tur);
									}
									fclose(Tur);
									if(band==0)
									{
										band=1;
									}
									
									
								}
								
							}
							else
							{
								band=2;
							}
							
						
							fread(&AuxM,sizeof(Mascotas),1,Masc);
						}
						fclose(Masc);
				}
                
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
	
	
	
	
	Tur=fopen("Turnos.dat","rb");
	fread(&AuxP,sizeof(Turnos),1,Tur);
	while(!feof(Tur))
	{
		
		printf("%d/%d/%d",AuxP.FecT.dia,AuxP.FecT.mes,AuxP.FecT.anio);
		if(AuxP.borrado==false)
		{
			printf("--CUalquier cosa---");
		}
		fread(&AuxP,sizeof(Turnos),1,Tur);
		
	}
	fclose(Tur);
	
}
