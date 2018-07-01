/*
 * Stack.c
 *
 *  Created on: 18/06/2018
 *      Author: ie717807
 */

#include <stdio.h>
#include <stdlib.h>
#include "Stack.h"

struct strNode{	//Declarando un Tipo de Dato (Para Node)
	Type data;
	struct strNode *prior;
};

typedef struct strNode Node;	//Renombrando el Tipo de Dato

struct strStack{ //Declarando un Tipo de Dato (Para Stack)
	Node *top;
	int size;
};


Stack createStack(){
	Stack new = (Stack) malloc(sizeof(struct strStack));
	if(new == NULL)
		return NULL;

	new->top = NULL;
	new->size = 0;
	return new;
}

void destroyStack(Stack who){
	while(isEmpty(who) != true)
		pop(who);
	free(who);
}

bool push(Stack who, Type data){
	Node *newNode = (Node *) malloc (sizeof(Node));
	if(newNode == NULL)
		return false;
	newNode->prior = who->top;

	newNode->data = data;	//Linea de referencia
	//newNode->data = (Type) malloc (sizeof(Type));
	who->size += 1;
	who->top = newNode;
	return true;
}

Type pop (Stack who){
	if(who->top == NULL)
		return NULL;
	Type temp;
	Node *tempNode;
	temp = who->top->data;
	who->size --;
	tempNode = who->top;
	who->top = who->top->prior;
	free(tempNode);
	return temp;
}

Type top(Stack who){
	if(who->top == NULL)
		return NULL;
	return who->top->data;
}

bool isEmpty(Stack who){
	if (who->size == 0)
		return true;
	else
		return false;
}


