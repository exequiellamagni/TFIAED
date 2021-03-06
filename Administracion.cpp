#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <locale.h>
#include"LibreriasTFI.h"

typedef char NomV[60];

void RegistrarVet(FILE *Vet);
int UsuarioRepetido(char NomU[10],FILE *&Vet);
void ComprobarUsuario(char NomU[10],int &b,FILE *&Vet);
void ComprobarContra(char ConU[32],int &b);
void RegistrarUs(FILE *Vet);
void MostrarAtenciones(FILE *Vet);
void Ranking(FILE *Vet);

main()
{
	int menu=0,l=100;
	setlocale(LC_ALL,"spanish");
	FILE *Vet,*clave;
	int pin,cont,acc=0,k;
	
	clave = fopen("claves.dat","rb");
	if(clave==NULL)
	{
		fclose(clave);
		clave = fopen("claves.dat","wb");

         while(pin > 5);
         {
         	printf("Crear pin(Maximo 5 digitos):\n\tIngrese el nuevo pin: ");
			scanf("%d",&pin);
         }

		fwrite(&pin,sizeof(int),1,clave);
		fclose(clave);
		acc=1;
	}
	else
	{
		clave = fopen("claves.dat","rb");
		fread(&pin,sizeof(int),1,clave);
		do
		{
			printf("Ingrese el pin de acceso: ");
			scanf("%d",&cont);
			if(cont == pin)
			{
				acc = 1;
			}
			else
			{
				printf("\nContrase�a incorrecta: \n");
				printf("1.Volver a intentar\n2.Volver al Men�\n\nOpcion: ");
				scanf("%d",&k);
				if(k==1)
				{
					acc=0;
					system("cls");
				}
				else
				{
					acc=2;
				}

			}
			
			
		}while(acc==0);
		

	}
    system("CLS");
	if(acc==1)
	{
		while(menu!=5)
		{
			printf("-----------------------------------------------------");
			printf("\nSe encuentra en el men� de administraci�n, ingrese:");
			printf("\n\n1-Registrar un nuevo veterinario");
			printf("\n2-Registrar un nuevo asistente");
			printf("\n3-Atenciones por veterinarios");
			printf("\n4-Ranking de atenciones por veterinarios");
			printf("\n5-Cerrar Men�");
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
				case 3: MostrarAtenciones(Vet);
				break;
				case 4: Ranking(Vet);
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
		  	system("CLS");
	       //registro de contrase�a del veterinario
	  
	  	    printf("Registrar contrase�a:\n");
		    printf("1- Debe contener como minimo: una letra mayuscula,una minuscula y un numero\n");
		    printf("2- Solo puede contener caracteres alfanumericos\n");
		    printf("3- Debe tener entre 6-32 caracteres\n");
		    printf("4- No debe tener mas de 3 caracteres numericos consecutivos\n");
		    printf("5- No debe tener 2 letras consecutivas ascendentes\n");
		    b=0;
	  	    while(b==0)
	  	    {
	  		    printf("\nIngrese la contrase�a: ");
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
					printf("\nError: Debe ingresar al menos una may�scula, una min�scula y un n�mero.\n");
				}
				
			}
			else
			{
				printf("\nError: Debe ingresar caract�res alfanumericos.\n");
			}
		}
		else
		{
			printf("\nError: Debe ingresar una contrasenia de 6-32 caract�res.\n");
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
		  	system("CLS"); 
	       //registro de contrase�a del asistente.
	  
	  	    printf("Registrar contrase�a:\n");
		    printf("1- Debe contener como minimo: una letra mayuscula,una minuscula y un numero\n");
		    printf("2- Solo puede contener caracteres alfanumericos\n");
		    printf("3- Debe tener entre 6-32 caracteres\n");
		    printf("4- No debe tener mas de 3 caracteres numericos consecutivos\n");
		    printf("5- No debe tener 2 letras consecutivas ascendentes\n");
		    b=0;
	  	    while(b==0)
	  	    {
	  		    printf("\nIngrese la contrase�a: ");
			    _flushall();
			    gets(DatU.Contra);
			    ComprobarContra(DatU.Contra,b);
	  	    }
	  	    
	  	    fwrite(&DatU,sizeof(Usuario),1,Vet);
	  	    fclose(Vet);
		
	    }
	
	
}

void MostrarAtenciones(FILE *Vet)
{
	Turnos AuxT;
	DatosVet AuxV;
	FILE *Tur;
	int band;
	
	Vet=fopen("Veterinario.dat","rb");
	if(Vet==NULL)
	{
		printf("Error: No hay veterinarios registrados.");
	}
	else
	{
		printf("===========================\n");
		printf("== Listado de Atenciones ==\n");
		printf("===========================");
		fread(&AuxV,sizeof(DatosVet),1,Vet);
		while(!feof(Vet))
		{
			Tur = fopen("Turnos.dat","rb");
			if(Tur==NULL)
			{
				printf("Error: No hay turnos");
		    }
		    else
			{
			    fread(&AuxT,sizeof(Turnos),1,Tur);
			    
			    band=0;
			    while(!feof(Tur))
			    {			    	
			    	if(AuxV.Mat == AuxT.MatV && AuxT.borrado == true)
			    	{
			    		if(band==0)
			    		{
			    			printf("\n\n\n============================================\n");
			    			printf("Mascotas atendidas por %s:\n",AuxV.ApeyNom);
			    			printf("============================================\n\n");
			    			printf("Datos de la mascota: \n");
			    		    band=1;
			    		}
			    		printf("--------------------------------------------\n");
			    		printf("\tNombre: %s\n",AuxT.NomMas);
			    		printf("\tDNI del due�o: %d\n",AuxT.DNIT);
			    		printf("\tFecha del turno: %d/%d/%d\n",AuxT.FecT.dia,AuxT.FecT.mes,AuxT.FecT.anio);
			    		printf("\tEvolucion de la mascota: %s\n",AuxT.evoMasc);
			    		printf("--------------------------------------------\n");
			    		
			    	}
			    	fread(&AuxT,sizeof(Turnos),1,Tur);
			    }
			    fclose(Tur);
			}
			fread(&AuxV,sizeof(DatosVet),1,Vet);
		}
		fclose(Vet);
	}
}


void Ranking(FILE *Vet)
{
	NomV Vets[100];
	Turnos AuxT;
	DatosVet AuxV;
	FILE *Tur;
	int vec[100],i=0,c,aux;
	char auxC[60];
	int auxa,auxm;
	int band=0;
	
	Vet=fopen("Veterinario.dat","rb");
	if(Vet==NULL)
	{
		printf("Error: No hay veterinarios registrados.");
	}
	else
	{
		printf("Ingrese el a�o(AAAA) del cual desea conocer el ranking: ");
		scanf("%d",&auxa);
		printf("\nIngrese el mes(MM) del cual desea conocer el ranking: ");
		scanf("%d",&auxm);
		fread(&AuxV,sizeof(DatosVet),1,Vet);
		while(!feof(Vet))
		{
			Tur = fopen("Turnos.dat","rb");
			if(Tur==NULL)
			{
				band=0;
		    }
		    else
			{
				c=0;
			    fread(&AuxT,sizeof(Turnos),1,Tur);
			    while(!feof(Tur))
			    {	
				    		    	
			    	if(AuxV.Mat == AuxT.MatV && AuxT.borrado == true)
			    	{
			    		if(AuxT.FecT.mes == auxm && AuxT.FecT.anio == auxa)
			    		{
			    			c++;
			    			band=1;
			    		}
			    	
			    		
			    	}
			    	
			    	fread(&AuxT,sizeof(Turnos),1,Tur);
			    	
			    }
			    vec[i]=c;
			    strcpy(Vets[i],AuxV.ApeyNom);
			    i++;
			    fclose(Tur);
			}
			fread(&AuxV,sizeof(DatosVet),1,Vet);
		}
		fclose(Vet);
	}
	
	for(int j=0;j<i;j++)
	{
		for(int k=j;k<i;k++)
		{
			if(vec[j]<vec[k])
			{
				aux = vec[j];
				vec[j] = vec[k];
				vec[k] = aux;
				strcpy(auxC,Vets[j]);
				strcpy(Vets[j],Vets[k]);
				strcpy(Vets[k],auxC);
			
			}
		
		}	
	}
	
	if(band==0)
	{
		printf("\n\nNo hubo atenciones ese mes.");
	}
	else
	{
		printf("\nRanking de atenciones: \n\n");
	    for(int j=0;j<i;j++)
		{
			printf("%d-%s: %d\n",j+1,Vets[j],vec[j]);	
		}	
	}

	
}








