/*
 * Stack.h
 *
 *  Created on: 18/06/2018
 *      Author: administrador
 */

#ifndef STACK_H_
#define STACK_H_

typedef enum {false, true} bool;

typedef void * Type;

typedef struct strStack *Stack;

Stack createStack();

void destroyStack(Stack);

bool push(Stack, Type);

Type pop(Stack);

Type top(Stack);

bool isEmpty(Stack);

#endif /* STACK_H_ */



