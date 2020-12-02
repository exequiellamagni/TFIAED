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
int UsuarioRepetido(FILE *Vet,Usuario DatU);
void Cargarusuario(Usuario &DatU);

main()
{
	setlocale(LC_ALL,"spanish");
	FILE *Vet;
	
}

void RegistrarVet(FILE *Vet)
{
	DatosVet DatV;
	Usuario DatU;
	
	
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
		printf("\tDNI");
		scanf("%d",&DatV.DNI);
		printf("\tTelefono");
		_flushall();
		gets(DatV.Tel);
		fwrite(&DatV,sizeof(DatosVet),1,Vet);
		fclose(Vet);
		
	
		strcpy(DatU.Nombre,DatV.ApeyNom);
	    Cargarusuario(DatU);
	}
}


int UsuarioRepetido(Usuario DatU)
{
	Usuario Us;
	int b=1;
	FILE *Vet;
	
	Vet = fopen("Usuario.dat","a+b");
	if(Vet == NULL)
	{
		printf("Error al abrir el archivo\n");
	}
	else
	{
		rewind(Vet);
		fread(&Us,sizeof(Usuario),1,Vet);
	    while(!feof(Vet))
	    {
	    	if(strcmp(Us.Usuar,DatU.Usuar)==0)
	    	{
	    		b=0;
	    		return b;
	    	}
	    	
	    	fread(&Us,sizeof(Usuario),1,Vet);
	    	
	    }
	    return b;
	    fclose(Vet);
	}

	
	
}


void Cargarusuario(Usuario &DatU)
{
	    char aux,aux1;
	    int Long,b=0,r,cm=0,May=0,Min=0,Num=0;
	
		printf("Registrar nombre de usuario\n");
		printf("1-Debe ser unico\n2-Debe comenzar con una letra minuscula\n3-Debe tener como minimo dos letras mayusculas\n");
		printf("4-Tener como maximo 3 digitos\n5-Debe tener de 6-10 caracteres");			
	    while(b==0)
		{
			cm=0;
			printf("Ingrese el nombre de usuario: ");
		    _flushall();
		    gets(DatU.Usuar);
		    Long = strlen(DatU.Usuar);
		    
		    r = UsuarioRepetido(DatU);
		    if(r==1)
		    {
		    	if(Long>=6 && Long<=10)
	            {
		        	if(islower(DatU.Usuar[0]) != 0)
		        	{
		        		for(int i=0;i<Long;i++)
		        		{
		        			if(isupper(DatU.Usuar[i]) != 0)
		        			{
		        				cm++;
		        			}
		        		}
		        		if(cm>=2)
		        		{
		        			cm=0;
		        			for(int i=0;i<Long;i++)
		        			{
		        				if(isdigit(DatU.Usuar[i])!=0)
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
		        				printf("Error: No puede contener mas de 3 digitos.");
		        			}
		        		}
		        		else
		        		{
		        			printf("\nError: Debe tener como minimo 2 letras mayusculas.");
		        		}
		        		
		        	}
		        	else
		        	{
		        		printf("\nError: La primera letra no es minuscula.");
		        	}
	            }
	            else
	            {
		       	    printf("\nError: Debe ingresar un usuario de 6-10 caracteres.");
	            }
		    }
		    else
		    {
		    	printf("\nError: El usuario ya existe.");
		    }
	        
		}
		
		b=0;
		
		printf("Registrar contraseña:\n");
		printf("1- Debe contener como minimo: una letra mayuscula,una minuscula y un numero\n");
		printf("2- Solo puede contener caracteres alfanumericos\n");
		printf("3- Debe tener entre 6-32 caracteres\n");
		printf("4- No debe tener mas de 3 caracteres numericos consecutivos\n");
		printf("5- No debe tener 2 letras consecutivas ascendentes\n");
		
		while(b==0)
		{
			Num=0;
			printf("Ingrese la contraseña: ");
			_flushall();
			gets(DatU.Contra);
			Long = strlen(DatU.Contra);
			if(Long >= 6 && Long <= 32)
			{
				for(int i=0;i<Long;i++)
				{
					
					if(isalnum(DatU.Contra[i])==0)
					{
						Num=1;
					}
				}
				if(Num==0)
				{
					for(int i=0;i<Long;i++)
					{
						if(isupper(DatU.Contra[i])!=0)
						{
							May=1;
						}
						else if(islower(DatU.Contra[i])!=0)
						{
							Min=1;
						}
						else if(isdigit(DatU.Contra[i])!=0)
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
							if(isdigit(DatU.Contra[i])!=0)
							{
								Num++;
								if(Num==4)
								{
									May=1;
									i=Long;
								}
							}
							else if(isalpha(DatU.Contra[i])!=0)
							{
								Num=0;
							}
						}
						if(May==0)
						{
							Num=0;
							May=0;
							for(int i=0;i<Long;i++)
							{
								if(isalpha(DatU.Contra[i])!=0)
								{
									Num++;
									if(Num==2)
									{
										aux = toupper(DatU.Contra[i]);
										aux1 = toupper(DatU.Contra[i-1]);
										if(aux>aux1)
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
						    	printf("Error: No debe ingresar dos letras consecutivas y ascendentes.");
						    }
						}	
						else
						{
							printf("Error: No debe ingresar mas de 3 digitos seguidos.");
						}
					}
					else
					{
						printf("Error: Debe ingresar al menos una mayúscula, una minúscula y un número.");
					}
					
				}
				else
				{
					printf("Error: Debe ingresar caractéres alfanumericos.");
				}
			}
			else
			{
				printf("Error: Debe ingresar una contrasenia de 6-32 caractéres.");
			}
			
			
			
			
		}
		
		
}




















