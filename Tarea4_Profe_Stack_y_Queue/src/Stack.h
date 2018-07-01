/*
 * Stack.h
 *
 *  Created on: 18/06/2018
 *      Author: administrador
 */

#ifndef STACK_H_
#define STACK_H_

typedef enum {false, true, error} bool;
typedef void *Type;
typedef struct strStack *Stack;

Stack createStack();			//Crear pila
void destroyStack(Stack);		//Destruir pila

bool push(Stack, Type);			//Insertar un dato al final
Type pop(Stack);				//Sacar el Top
Type top(Stack);				//Consultar el quien es el Top

bool isEmpty(Stack);			//Preguntar si esta vacio
int size_Stack(Stack);			//Retorna el tamaño actual de la pila

#endif /* STACK_H_ */



