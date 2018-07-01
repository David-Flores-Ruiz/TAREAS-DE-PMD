/*
 * Stack.c
 *
 *  Created on: 19/06/2018
 *      Author: administrador
 */

#include <stdio.h>
#include <stdlib.h>
#include "Stack.h"


struct strNode{
	Type data;
	struct strNode *prior;
};

typedef struct strNode Node;

struct strStack{
	Node *top;
	int size;
};

Stack createStack(){
	Stack new=(Stack)malloc(sizeof(struct strStack));
	if(new==NULL)
		return NULL;
	new->top=NULL;
	new->size=0;
	return new;
}

void destroyStack(Stack who){
	while(isEmpty(who)!=true)
		pop(who);
	free(who);
}

bool push(Stack who, Type data){
	Node *newNode=(Node *)malloc(sizeof(Node));
	if(newNode==NULL)
		return false;
	newNode->prior=who->top;
	newNode->data=data;  //Cuidado aquí
	who->size+=1;
	who->top=newNode;
	return true;
}

Type pop(Stack who){
	if (who->top==NULL)
		return NULL;
	Type temp;
	Node *tempNode;
	temp=who->top->data;
	who->size--;
	tempNode=who->top;
	who->top=who->top->prior;
	free(tempNode);
	return temp;
}

Type top(Stack who){
	if (who->top==NULL)
		return NULL;
	return who->top->data;
}

bool isEmpty(Stack who){
	if (who->size==0)
		return true;
	else
		return false;
}

int size_Stack(Stack who){
	return who->size;
}
