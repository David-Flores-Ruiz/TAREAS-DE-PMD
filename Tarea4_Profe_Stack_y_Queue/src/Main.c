/*
 ============================================================================
 Name        : Tarea4_Profe_Stack_y_Queue.c
 Author      : 
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Stack.h"
#include "Queue.h"

char * InfixToPosfix(char * exp);
bool hasHigherPrecedence(char * top, char * operator);//¿El top tiene mayor precedencia que operador o igual?
void concatenar ( char c1[20], char c2[20], char cF[40] );

int main(void) {
	setvbuf(stdout, NULL, _IONBF, 0);
	char cadInfijo[20];
	char cadPostfijo[40];//Va a llevar espacios
	printf("Introduce la expresion aritmética (Válida) en formato INFIJO:\n");
	gets(cadInfijo);
	puts(cadInfijo);

	strcpy(cadPostfijo, InfixToPosfix(cadInfijo));//LLamada a la función para convertir a POSTFIJO
	printf("\n------> La cadena en formato POSTFIJO es:\n");
	puts(cadPostfijo);

	return EXIT_SUCCESS;
}



char * InfixToPosfix(char * exp){
	Stack pila = NULL; //Vacía
	Queue colaRes = NULL, auxCola = NULL; //Vacia
	char *topData;

	auxCola = create_queue();
	//if(auxCola != NULL)
		//printf("EL auxCola se creo correctamente ");

	colaRes = create_queue();
	//if(colaRes != NULL)
		//printf("	y el colaRes ");

	pila = createStack();
	//if(pila != NULL)
		//printf("	y el pila !!! ");


	int longitud = strlen(exp);
	//printf("longitud: %d", longitud);
	int *temp;
	int i;

	for(i=0; i<longitud; i++){
		offer_queue(auxCola, &exp[i] );//Insertar toda la exp en Orden FIFO, osea en la Cola
		temp = peek_queue(auxCola);
		//printf("\nConsulta %d del auxCola enfrente %c tamaño de la auxCola: %d", i , *temp, size_queue(auxCola));
	}

	char *caracter;
	for(i=0; i<longitud; i++){
		caracter = poll_queue(auxCola);
		//printf("\nLinea 70: %c", *caracter);
		if ( 48 <= *caracter && *caracter <= 57 ){ // NÚMEROS! según el ASCII
			offer_queue(colaRes, caracter );
			//printf("\nNumero insertado en la colaRES! tamaño: %d",size_queue(colaRes) );
		}//Si encuentras numeros insertalos en la Queue Resultante
		if(*caracter == '(')
			push(pila, caracter);
		if(*caracter == '+' || *caracter == '-' || *caracter == '*' || *caracter == '/'){
			topData = top(pila);
			while(  (isEmpty(pila) == false) && ( *topData != '(')  ){
				//printf("\nLinea 81del while... Actual TOP de la PILA: %c", *topData);
				if(hasHigherPrecedence(topData , caracter ) == true){
					temp = pop(pila);
					offer_queue(colaRes, temp );
					//printf("\nLinea85...Se insertó operador en colaRES! tamaño: %d", size_queue(colaRes) );
					topData = top(pila);
				}else {
					break;
				}
			}//Termina ciclo Mientras
			push(pila, caracter); //inserta el operador
			//printf("\nLinea 90... Tamaño actual de la pila: %d",size_Stack(pila));
			topData = top(pila);
			//printf("\nLinea 92 Primero... ó  Actual TOP de la PILA: %c", *topData);
		}
		if( *caracter == ')'){
			topData = top(pila);
			while(	( isEmpty(pila) == 0) && ( *topData != '(')  ){
				//printf("\nEL elemeto a remover de la pila es: %c", *topData);
				temp = pop(pila);
				//printf("\nLinea 97... Tamaño actual de la pila: %d",size_Stack(pila));
				offer_queue(colaRes, temp );
				topData = top(pila);
			}
			if(isEmpty(pila) == 0)
				temp = pop(pila);//Remueve el '('
		}
	}
// e) si al llegar a este punto la pila no está vacía, remover uno por uno e insertarlos en colaRes
	while(isEmpty(pila) == false){
		temp = pop(pila);
		offer_queue(colaRes, temp );
	}

	char cad1[25];//Postfijo
	char cad2[25];//Espacios
	char cadFinal[50];

	i=0;
	while (isEmptyQueue(colaRes) == 0){
		temp = poll_queue(colaRes);
		//printf("\ntemp %c", *temp);
		cad1[i] = *temp;		//EN cad1 está el resultado en formato Postfijo
		i++;
	}

	cad1[i] = '\0';

	for(i=0; i<longitud; i++){
		cad2[i] = ' ';
	}

	cad2[i] = '\0';

	//printf("\nAntes de concatenar: %s", cad1);
	concatenar (cad1, cad2, cadFinal);
	exp = cadFinal;
	//printf("\nEL resultado Concatenado es:\n");
	//puts(cadFinal);

	return exp;
}

bool hasHigherPrecedence(char * top, char * operator){//¿El top tiene mayor precedencia que operador o igual?
	if(	*top == '*' || *top == '/' )
		return true;

	else if(  (*top == '+' || *top == '-') && (*operator == '-' || *operator == '+')	)
		return true;

	else if(	(*top == '+' || *top == '-') && (*operator == '*' || *operator == '/')	)
		return false;//Único caso en que el Top no es mayor al operator

	else
		return error;//Posible simbolo raro
}

void concatenar ( char c1[], char c2[], char cF[] ){
	int i=0, j=0;
	char *apunCF = cF;
	//printf("c1: %s\nc2: %s", c1, c2);
	while(c1[j]!='\0'){
		*(apunCF + i) = c1[j];
		*(apunCF + i+1) = c2[j];
		i+=2;
		j++;
	}

	*(apunCF + i) = '\0';
}



//fallas de ejecucion con:
//1+2*5
//( 1 + 2 ) * ( 3 + 4 ) //sin espacios si funciona no tiene npor que asi
//1 + 2 * 3 se cicla infinitamente

//Exito con:
//(1+2)*(3+4)
//( 1 + 2 ) * 5
//1 * 2 + 3
//1 + 3 + 4
//1 - 3 + 4
//1 * 4 * 6
//1 / 4 * 6
