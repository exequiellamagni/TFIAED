#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <locale.h>

struct DatosVet
{
	char ApeyNom[60];
	int Mat,DNI;
	char Tel[25];
};
struct Usuario
{
	char Usuar[10];
	char Contra[32];
	char Nombre[60];
};

void RegistrarVet(FILE *Vet);
int UsuarioRepetido(char NomU[10],FILE *&Vet);
void ComprobarUsuario(char NomU[10],int &b,FILE *&Vet);
void ComprobarContra(char ConU[32],int &b);
void RegistrarUs(FILE *Vet);

main()
{
	int menu=0;
	setlocale(LC_ALL,"spanish");
	FILE *Vet;
	
	
	
	while(menu!=5)
	{
		printf("-----------------------------------------------------");
		printf("\nSe encuentra en el menú de administración, ingrese:");
		printf("\n\n1-Registrar un nuevo veterinario");
		printf("\n2-Registrar un nuevo asistente");
		printf("\n5-Cerrar Menú");
		printf("\n---------------------------------------------------");
		printf("\n\nIngrese la opcion: ");
		scanf("%d",&menu);
		system("CLS");
		
		switch(menu)
		{
			case 1: RegistrarVet(Vet);
			break;
			case 2: RegistrarUs(Vet);
			break;
			case 5: 
			break;
			default: printf("Error: opcion invalida");
		}
		if(menu!=5)
		{
			printf("\n\n\n");
			system("pause");
		}
		system("CLS");
	}
	
	
	
}

void RegistrarVet(FILE *Vet)
{
	DatosVet DatV;
	Usuario DatU;
	int b;
	
	Vet = fopen("Veterinario.dat","ab");
	
	if(Vet == NULL)
	{
		printf("Error al abrir el archivo\n");
	}
	else
	{
		printf("Ingrese los siguientes datos del veterinario: \n");
		
		printf("\tApellido y Nombre: ");
		_flushall();
		gets(DatV.ApeyNom);
		printf("\tMatricula: ");
		scanf("%d",&DatV.Mat);
		printf("\tDNI: ");
		scanf("%d",&DatV.DNI);
		printf("\tTelefono: ");
		_flushall();
		gets(DatV.Tel);
		fwrite(&DatV,sizeof(DatosVet),1,Vet);
		fclose(Vet);
		
	    //Registro de usuario  del veterinario.
	    system("CLS");
	    Vet = fopen("Usuario.dat","a+b");
	    if(Vet==NULL)
	    {
	    	printf("Error al abrir el archivo\n");
	    }
	    else
	    {
	    	strcpy(DatU.Nombre,DatV.ApeyNom);
		
		    printf("Registrar nombre de usuario\n");
		    printf("1-Debe ser unico\n2-Debe comenzar con una letra minuscula\n3-Debe tener como minimo dos letras mayusculas\n");
		    printf("4-Tener como maximo 3 digitos\n5-Debe tener de 6-10 caracteres\n");
		    b=0;
		    while(b==0)
		    {
		        printf("\nIngrese el nombre de usuario: ");
		        _flushall();
	    	    gets(DatU.Usuar);
			    ComprobarUsuario(DatU.Usuar,b,Vet);
		    }
		  
	       //registro de contraseñia del veterinario
	  
	  	    printf("\nRegistrar contraseña:\n");
		    printf("1- Debe contener como minimo: una letra mayuscula,una minuscula y un numero\n");
		    printf("2- Solo puede contener caracteres alfanumericos\n");
		    printf("3- Debe tener entre 6-32 caracteres\n");
		    printf("4- No debe tener mas de 3 caracteres numericos consecutivos\n");
		    printf("5- No debe tener 2 letras consecutivas ascendentes\n");
		    b=0;
	  	    while(b==0)
	  	    {
	  		    printf("\nIngrese la contraseña: ");
			    _flushall();
			    gets(DatU.Contra);
			    ComprobarContra(DatU.Contra,b);
	  	    }
	  	    
	  	    fwrite(&DatU,sizeof(Usuario),1,Vet);
	  	    fclose(Vet);
		
	    }

	}
}



int UsuarioRepetido(char NomU[10],FILE *&Vet)
{
	Usuario Us;
	int b=1;

    rewind(Vet);
	fread(&Us,sizeof(Usuario),1,Vet);
	while(!feof(Vet))
	{
    	if(strcmp(Us.Usuar,NomU)==0)
    	{
    		return b=0;
    	}
    	
    	fread(&Us,sizeof(Usuario),1,Vet);
    	
    }
    return b;
    fclose(Vet);
}

void ComprobarUsuario(char NomU[10], int &b,FILE *&Vet)
{
	    
	    int Long,r,cm=0;
	    
		Long = strlen(NomU);
		r = UsuarioRepetido(NomU,Vet);
		if(r==1)
		{
		    if(Long>=6 && Long<=10)
	        {
		        if(islower(NomU[0]) != 0)
		        {
		        	for(int i=0;i<Long;i++)
		        	{
		        		if(isupper(NomU[i]) != 0)
		        		{
		        			cm++;
		        		}
		        	}
		        	if(cm>=2)
		        	{
		        		cm=0;
		        		for(int i=0;i<Long;i++)
		        		{
		        			if(isdigit(NomU[i])!=0)
		        			{
		        				cm++;
		        			}
		        		}
		        		if(cm<=3)
		       			{
		       				b=1;
		       			}
		       			else
		       			{
		       				printf("\nError: No puede contener mas de 3 digitos.\n");
		       			}
		       		}
	        		else
	        		{
						 printf("\nError: Debe tener como minimo 2 letras mayusculas.\n");
		        	}
		        		
		        }
		       	else
		        {
		        	printf("\nError: La primera letra debe ser minuscula.\n");
		        }
	        }
	        else
	        {
		       	printf("\nError: Debe ingresar un usuario de 6-10 caracteres.\n");
	        }
		}
		else
		{
		    printf("\nError: El usuario ya existe.\n");
		}
}
	        
	
void ComprobarContra(char ConU[32],int &b)
{	
        char aux,aux1;
        int Long,May=0,Min=0,Num=0;
			
		Long = strlen(ConU);
		if(Long >= 6 && Long <= 32)
		{
			for(int i=0;i<Long;i++)
			{		
				if(isalnum(ConU[i])==0)
				{
					Num=1;
				}
			}
			if(Num==0)	
			{
				for(int i=0;i<Long;i++)
				{
					if(isupper(ConU[i])!=0)
					{
						May=1;
					}
					else if(islower(ConU[i])!=0)
					{
						Min=1;
					}
					else if(isdigit(ConU[i])!=0)
					{
						Num=1;
					}
				}
				if(Num==1 && May==1 && Min==1)
				{
					Num=0;
					May=0;
					for(int i=0;i<Long;i++)
					{
						if(isdigit(ConU[i])!=0)
						{
							Num++;
							if(Num==4)
							{
								May=1;
								i=Long;
							}
						}
						else if(isalpha(ConU[i])!=0)
						{
							Num=0;
						}
					}
					if(May==0)
					{
						Num=0;
						for(int i=0;i<Long;i++)
						{
							if(isalpha(ConU[i])!=0)
							{
								Num++;
								if(Num==2)
								{
									
									aux = toupper(ConU[i]);
									aux1 = toupper(ConU[i-1]);
									
									if(aux1 == aux-1)
									{
									   May=1;
									   i=Long;	
									}
									
								}
							}
							else
						    {
						    	Num=0;
						    }
					    }
					    if(May==0)
					    {
					    	b=1;
					    }
					    else
					    {
					    	printf("\nError: No debe ingresar dos letras consecutivas y ascendentes.\n");
					    }
					}	
					else
					{
						printf("\nError: No debe ingresar mas de 3 digitos seguidos.\n");
					}
				}
				else
				{
					printf("\nError: Debe ingresar al menos una mayúscula, una minúscula y un número.\n");
				}
				
			}
			else
			{
				printf("\nError: Debe ingresar caractéres alfanumericos.\n");
			}
		}
		else
		{
			printf("\nError: Debe ingresar una contrasenia de 6-32 caractéres.\n");
		}
					
}


void RegistrarUs(FILE *Vet)
{
        Usuario DatU;
        int b=0;
	
	    printf("Ingrese apellido y nombre del asistente: ");
	    _flushall();
    	gets(DatU.Nombre);
	
	    //Registro de usuario  del asistente.
	    system("CLS");
	    Vet = fopen("Usuario.dat","a+b");
	    if(Vet==NULL)
	    {
	    	printf("Error al abrir el archivo\n");
	    }
	    else
	    {
		    printf("Registrar nombre de usuario:\n");
		    printf("1-Debe ser unico\n2-Debe comenzar con una letra minuscula\n3-Debe tener como minimo dos letras mayusculas\n");
		    printf("4-Tener como maximo 3 digitos\n5-Debe tener de 6-10 caracteres\n");
		    b=0;
		    while(b==0)
		    {
		        printf("\nIngrese el nombre de usuario: ");
		        _flushall();
	    	    gets(DatU.Usuar);
			    ComprobarUsuario(DatU.Usuar,b,Vet);
		    }
		  
	       //registro de contraseñia del asistente.
	  
	  	    printf("\nRegistrar contraseña:\n");
		    printf("1- Debe contener como minimo: una letra mayuscula,una minuscula y un numero\n");
		    printf("2- Solo puede contener caracteres alfanumericos\n");
		    printf("3- Debe tener entre 6-32 caracteres\n");
		    printf("4- No debe tener mas de 3 caracteres numericos consecutivos\n");
		    printf("5- No debe tener 2 letras consecutivas ascendentes\n");
		    b=0;
	  	    while(b==0)
	  	    {
	  		    printf("\nIngrese la contraseña: ");
			    _flushall();
			    gets(DatU.Contra);
			    ComprobarContra(DatU.Contra,b);
	  	    }
	  	    
	  	    fwrite(&DatU,sizeof(Usuario),1,Vet);
	  	    fclose(Vet);
		
	    }
	
	
}











