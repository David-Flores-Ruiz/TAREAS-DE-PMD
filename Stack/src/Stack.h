/*
 * Stack.h
 *
 *  Created on: 18/06/2018
 *      Author: ie717807
 */

#ifndef STACK_H_
#define STACK_H_



typedef enum {false, true} bool;	//Definir un tipo Booleano

typedef void * Type;

typedef struct strStack *Stack;

Stack createStack();

void destroyStack(Stack);

bool push(Stack, Type);	//Insertar en el tope

Type pop(Stack);		//Extrae el tope

Type top(Stack);		//Solo es consultar el tope

bool isEmpty(Stack);



#endif /* STACK_H_ */
