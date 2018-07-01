/*
 * Queue.c
 *
 *  Created on: 24/06/2018
 *      Author: administrador
 */

#include <stdio.h>
#include <stdlib.h>
#include "Queue.h"

struct strNode{
	Type data;
	struct strNode *next;
};

typedef struct strNode Node;

struct strQueue{
	Node *first;
	Node *last;
	int size;
};

booleano isEmptyQueue(Queue who){
	if (who->size==0)
		return truee;
	return falsee;
}

int size_queue(Queue who){
	return who->size;
}

Queue create_queue(){
	Queue new=(Queue)malloc(sizeof(struct strQueue));
	new->first=NULL;
	new->last=NULL;
	new->size=0;
	return new;
}

void destroy_queue(Queue who){
	while(isEmptyQueue(who)==falsee)
		poll_queue(who);
}

void offer_queue(Queue who, Type data){
	//char* entro = data;
	//printf("offer: %c\n", *entro);
	Node *newNode=(Node *)malloc(sizeof(struct strNode));
	newNode->next=NULL;
	newNode->data=data;
	if(isEmptyQueue(who)==truee){
		who->first=newNode;
		who->last=newNode;
	}
	else{
		who->last->next=newNode;
		who->last=newNode;
	}
	who->size++;
}

Type poll_queue(Queue who){
	Node *tempNode;
	Type tempData;
	if(isEmptyQueue(who)==falsee){
		tempNode=who->first;
		tempData=who->first->data;
		who->first=who->first->next;
		free(tempNode);
		who->size--;
		if(isEmptyQueue(who)==truee)
			who->last=NULL;
		return tempData;
	}
	return NULL;
}

Type peek_queue(Queue who){
	if(isEmptyQueue(who)==falsee)
		return who->first->data;
	else
		return NULL;
}
