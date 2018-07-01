/*
 * Queue.h
 *
 *  Created on: 23/06/2018
 *      Author: administrador
 */

#ifndef QUEUE_H_
#define QUEUE_H_

typedef enum {falsee, truee} booleano;
typedef void *Type;
typedef struct strQueue *Queue;

Queue create_queue();			//Crear una Cola
void destroy_queue(Queue);		//Destruir pila

void offer_queue(Queue, Type);	//Insertar un dato al FINAL
Type poll_queue(Queue);			//Saca al dato que esta enfrente
Type peek_queue(Queue);			//Consulta quien está al frente (no elimina)

booleano isEmptyQueue(Queue);	//Preguntar si esta vacio
int size_queue(Queue);			//Retorna el tamaño actual de la cola

#endif /* QUEUE_H_ */
