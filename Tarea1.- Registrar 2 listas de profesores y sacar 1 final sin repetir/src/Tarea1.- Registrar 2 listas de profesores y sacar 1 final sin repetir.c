/*
 ============================================================================
 Name        : -.c
 Author      : 
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct{
	char nombre[15];
	float calificacion;
} Profesor;

//float averageArray(Profesor ______  , int _____);
void readArray(Profesor arr[20], int n);
void mergeArrays(Profesor arr1[] , int n1, Profesor arr2[] , int n2, Profesor arrF[]);
void sortArray(Profesor arrF[], int n3);
int comparaCadenas (char cadena1[], char cadena2[]);
void printArray(Profesor arrF[], int n3);

int main(void) {
	setvbuf(stdout, NULL, _IONBF, 0);
	Profesor arr1[20];  //Primer arreglo
	Profesor arr2[20];  //Segundo arreglo
	Profesor arrF[40];  //Arreglo final, con elementos fusionados y ordenados
	int n1, n2, n3; //Longitud de los arreglos
	int valor;
	Profesor *apuntador;

	printf("\nDe que tamaño es la *lista #1* de profesores a ingresar: ");
	scanf("%d", &n1);
	readArray(arr1, n1); //leer el primer arreglo

	setbuf(stdin, 0);
	printf("\nDe que tamaño es la *lista #2* de profesores a ingresar: ");
	scanf("%d", &n2);
	readArray(arr2, n2); //leer el segundo arreglo

	n3 = n1 + n2;

	mergeArrays(arr1, n1, arr2, n2, arrF);  //Fusionar los dos arreglos en un tercer arreglo

	sortArray(arrF, n3);  //Ordenar los elementos del tercer arreglo, recuerde que pueden existir profesores repetidos
	printf("\n\nLa lista ordenada de profesores, sin repetir ninguno es:\n");
	printArray(arrF, n3);   //Imprimir el resultado final
	
	apuntador = arrF;
	int i=0;
	for(i; i<n3-1; i++ ){
		valor = comparaCadenas( (apuntador + i)->nombre , (apuntador + i+1)->nombre );
		printf("Valor Comparacion: %d ", valor);
		if(valor == 0) //Si la comparacion son iguales
		{
			(apuntador + i+1)->calificacion = (	(apuntador + i)->calificacion + (apuntador + i+1)->calificacion) /2;	//Le asignamos el promedio al nombre repetido en la posición de adelante
			(apuntador + i)->calificacion = -5;	//Borrado lógico
		}
	}

	//printArray(arrF, n3);   //Imprimir el resultado final


	return EXIT_SUCCESS;
}

//float averageArray(Profesor ______  , int _____){
//
//
//	return	3.5;
//}

void readArray(Profesor arr[20], int N){
	Profesor *apuntador = arr;
	char auxNombre[15];
	float auxCalif;

	printf("Introduce los profesores y su calificacion:");

	int i = 0;
	for (i; i < N; i++){
		setbuf(stdin, 0);
		gets(auxNombre);
		strcpy((apuntador + i)->nombre , "");
		strcpy((apuntador + i)->nombre , auxNombre);
		scanf("%f", &auxCalif);
		(apuntador + i)->calificacion = auxCalif;
	}
}


void mergeArrays(Profesor arr1[] , int n1, Profesor arr2[] , int n2, Profesor arrF[]){	//n3 = n1 + n2
	Profesor *apuntador = arrF;
	int i, j, limit;

	for(i=0; i < n1; i++){
		strcpy((apuntador + i)->nombre , "");
		strcpy((apuntador + i)->nombre , (arr1 + i)->nombre);
		(apuntador + i)->calificacion = (arr1 + i)->calificacion;
	}

	limit = i;

	for(j=0; j < n2; j++){
		strcpy((apuntador + j + limit)->nombre , "");
		strcpy((apuntador + j + limit)->nombre , (arr2 + j)->nombre);
		(apuntador + j + limit)->calificacion = (arr2 + j)->calificacion;
	}
}

void sortArray(Profesor arrF[], int n3){	//Aqui deben llegar el arreglo
	Profesor *apunta = arrF;			//combinado de las 2 listas y su tamaño
	Profesor structSwap;	//CREO Q PODRIA SER SOLO 1 VARIABLE
	Profesor *auxSwap = &structSwap;
	int i;
	int j;

	for(i = 0; i < n3; i++){
		for(j = 0; j < n3-1; j++){
			if(	(apunta + j)->calificacion > (apunta + j + 1)->calificacion	)
				{
					strcpy(	(auxSwap + j)->nombre, "");
					strcpy(	(auxSwap + j)->nombre, (apunta + j)->nombre );	//Pasar al AUX
					(auxSwap + j)->calificacion = (apunta + j)->calificacion;	//Pasar al AUX

					strcpy(	(apunta + j)->nombre, (apunta + j + 1)->nombre );// Inicia el SWAP
					(apunta + j)->calificacion = (apunta + j + 1)->calificacion;//Inicia el SWAP

					strcpy(	(apunta + j + 1)->nombre, (auxSwap + j)->nombre	);//FIN de SWAP
					(apunta + j + 1)->calificacion = (auxSwap + j)->calificacion;//FIN de SWAP
				}
		}
	}
}

int comparaCadenas (char cadena1[], char cadena2[]){	//Deben ser de MAX. 15 caracteres
	char *apCad1 = cadena1;
	char *apCad2 = cadena2;
	int i=0;
	int bandera1 = 1,  bandera2 = 1;	// Se inicializan banderas en 1
	int mayor = 1;
	int iguales = 0;
	int menor = -1;

	while (i<15)
	{
		if(	*(apCad1 + i) == '\0' )
			bandera1 = 0;	//Se apaga bandera1


		if( *(apCad2 + i) == '\0' )
			bandera2 = 0; 	//Se apaga bandera2

		if ( *(apCad1 + i) > *(apCad2 + i) )	// s1>s2
					return mayor;

		if ( *(apCad1 + i) < *(apCad2 + i) )	// s1<s2
					return menor;

		if( bandera1 == 0 && bandera2 == 1)
			return menor;

		if( bandera1 == 1 && bandera2 == 0)
			return mayor;

		if( bandera1 == 0 && bandera2 == 0)
			return iguales;

		i++;
	}
	return 8;	// SI regresa 8 es error
}


void printArray(Profesor arrF[], int n3){
	Profesor *dezplazaArr = arrF;

	int i = 0;
	for (i; i<n3; i++){
		if(	(dezplazaArr + i)->calificacion != -5)//Si hubo borrado lógico no lo imprime
		{
			printf("%s ->\t\t", (dezplazaArr + i)->nombre );
			printf("%f\n", (dezplazaArr + i)->calificacion);
		}
		
	}

}

