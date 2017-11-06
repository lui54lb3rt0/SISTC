#ifndef INCLUDE_MYMQ_H
#define INCLUDE_MYMQ_H

#include <semaphore.h>
#include <pthread.h>

typedef struct
{
  int slot_size; //maximum slot size;
  int number_of_slots;
	void *slots; //malloc(slot_size*number_of_slots)
  int *data_size; //indicates the actual size of the data stored on each slot
	int oldest_slot; //index of the oldest element in the queue
	sem_t sem_msgs_in_queue; //send increments this, receive waits on this
	sem_t sem_free_slots; //receive increments this, send waits on this
	pthread_mutex_t* access;  //the accesses to the message queue 
                            //must be mutually exclusive
}
mymq_t;


//returns -1 on error
int mymq_init(mymq_t *mq, int slot_size, int number_of_slots);

void mymq_send(mymq_t *mq, void *data, int size);

//returns size of received message  (in bytes) 
int mymq_receive(mymq_t *mq, void *data, int size);


#endif
