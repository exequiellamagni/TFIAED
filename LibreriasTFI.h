#include<stdio.h>
#include<stdlib.h>
#include<string.h>

struct Usuario
{
	char Usuar[10];
	char Contra[32];
	char Nombre[60];
};

struct Fecha
{
	int dia,mes,anio;
};


struct DatosVet
{
	char ApeyNom[60];
	int Mat,DNI;
	char Tel[25];
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
	int MatV,DNIT;
	Fecha FecT;
	char Det[380];
	bool borrado;
};



int IniciarSesion(FILE *&Vet,int b)
{
	DatosVet DatV;
	Usuario DatI, DatC,AuxC;
	int k=0,In=0;
	FILE *aux;
	
	printf("Ingrese apellido y nombre: ");
	_flushall();
	gets(DatI.Nombre);
	strupr(DatI.Nombre);
	
	Vet = fopen("Usuario.dat","rb");
	if(Vet==NULL)
	{
		printf("\nError: No se registro ningun usuario\n");
		return 0;
	}
	else
	{
		fread(&DatC,sizeof(Usuario),1,Vet);
		
		while(!feof(Vet))
		{
			strupr(DatC.Nombre);
			if(strcmp(DatI.Nombre,DatC.Nombre)==0)
			{
				AuxC=DatC;
				k=1;
			}
			
			fread(&DatC,sizeof(Usuario),1,Vet);
		}
		
		fclose(Vet);
		
		if(k==1)
		{
		
			aux=fopen("Veterinario.dat","rb");
			if(aux==NULL)
			{
				if(b==1)
				{
					printf("\nError: No se registro ningun veterinario\n");
					return 0;
				}
				else
				{
					k=1;
				}
			}
			else
			{
				fread(&DatV,sizeof(DatosVet),1,aux);
		
	        	while(!feof(aux))
	    	    {
	        		if(strcmp(DatI.Nombre,DatV.ApeyNom)==0)
	        		{
	        			k=0;
	        		}
	    		
	        		fread(&DatV,sizeof(DatosVet),1,aux);
	        	}
	        	
	        	fclose(aux);
	   		}
	   		
	   		if(k==1)
	   		{
	   			if(b==0)
	   		    {
	   				while(In == 0)
	   				{
	   			    	printf("\nIngrese el usuario: ");
	   			    	_flushall();
	   			    	gets(DatI.Usuar);
	   			    		
	   			    	if(strcmp(DatI.Usuar,AuxC.Usuar)==0)
	   			    	{
	   			    		printf("\nIngrese la contraseņa: ");
	   			    		_flushall();
	   			    		gets(DatI.Contra);
	   			    		
	   			    		if(strcmp(DatI.Contra,AuxC.Contra)==0)
	   			    		{
	   			    			return 1;
	   			    		}
	   			    		else
	   			    		{
	   			    			printf("\nError: contraseņa incorrecta\n");
	   			    		}
	   			    		     
	   			    	}
	   			    	else
	   			    	{
	   			    		printf("\nError: usuario incorrecto\n");	
	   			    	}
	   					
						printf("\n<0- Volver a intentar> - <Otro numero-Volver al menu>\n\nIngrese una opcion: ");
						scanf("%d",&In);
						system("CLS");
	   				}
	   				return 0;
	   				
	   		    }
	   			else
	   			{
	   			  	printf("\nError: No posee acceso al modulo de veterinario\n");
	   			}
	   			
	   			
	   	   }
	   	   
	   	   else if(k==0)
	   	   {
	   			if(b==1)
	   			{
	   				while(In == 0)
	   				{
	   			    	printf("\nIngrese el usuario: ");
	   			    	_flushall();
	   			    	gets(DatI.Usuar);
	   			    		
	   			    	if(strcmp(DatI.Usuar,AuxC.Usuar)==0)
	   			    	{
	   			    		printf("\nIngrese la contraseņa: ");
	   			    		_flushall();
	   			    		gets(DatI.Contra);
	   			    		
	   			    		if(strcmp(DatI.Contra,AuxC.Contra)==0)
	   			    		{
	   			    			return 1;
	   			    		}
	   			    		else
	   			    		{
	   			    			printf("\nError: contraseņa incorrecta\n");
	   			    		}
	   			    		     
	   			    	}
	   			    	else
	   			    	{
	   			    		printf("\nError: usuario incorrecto\n");	
	   			    	}
	   					
						printf("\n<0- Volver a intentar> - <Otro numero-Volver al menu>\n\nIngrese una opcion: ");
						scanf("%d",&In);
						system("CLS");
	   				}
	   				return 0;
	   				
	   			}
	   			else
	   			{
	   				printf("\nError: No posee acceso al modulo de asistente\n");
	   			}
	   			
	   			
	   	   }
			
			
		}
		else
		{
			printf("\nEl nombre ingresado no esta registrado\n");
			return 0;
		}
	}
	
}

