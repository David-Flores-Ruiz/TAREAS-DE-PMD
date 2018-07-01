/*
 ============================================================================
 Name        : MiMain.c
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

bool balanced(char *c);

int main(){
	setvbuf(stdout, NULL, _IONBF, 0);
	char cadena[30];
	int valor;
	printf("Introduce la expresion algebraica:\n");
	gets(cadena);
	valor = balanced(cadena);

	if(valor == 1)
		printf("-------------------Los parentesis y corchetes est�n balanceados------------------\n");
	else
		printf("La expresion NO esta balanceada en los parentesis y corchetes\n");

	return EXIT_SUCCESS;
}


bool balanced(char* exp){
	Stack s1;
	char* letraPop;
	s1=createStack();
	if(s1 != NULL)
		printf("Se cre� correctamente el stack\n");

	int i;
	for (i=0; exp[i] != '\0'; i++){
		if (exp[i]=='(')	//Mete al stack parentesis abiertos
			push(s1, (void *)&exp[i]);
		else if (exp[i]=='[')	//Mete al stack corchetes abiertos
			push(s1, (void *)&exp[i]);

		else if ( exp[i] == ')' ){	//Si encuentra cierre de parentesis
			if(isEmpty(s1)==false){	//�LTIMO IF ANIDADO PARA EVITAR QUE EL PROGRAMA TRUENE POR HACER POP CON PILA VAC�A
				letraPop = (char *)pop(s1); //saca del stack (el ultimo que se abri�)
				if (*letraPop != '('){	//sino es el que corresponde ya VALI� la expresi�n
					printf("Falla linea 51\n");
					return false;
				}
			}
		}
		else if(exp[i]==']'){
			if(isEmpty(s1)==false){	//�LTIMO IF ANIDADO PARA EVITAR QUE EL PROGRAMA TRUENE POR HACER POP CON PILA VAC�A
				letraPop = (char *)pop(s1);
				if (*letraPop != '['){
					printf("Falla linea 58\n");
					return false;
				}
			}
		}
	}//Termina el for

	if (isEmpty(s1)==true)
		return true;
	else{
		return false;
		printf("Sobraron parentesis Falla linea 68\n");
	}
}




//Del pasado: jajajajajajaja ERROR con...	(2+3)+(3+2)+[2--1]

//Con esto truena...   2-3)+(1-2)[2+4]+1(
//preciso 	2-3)+(1-2)
//Cuando quiere hacer pop y no hay NADA

