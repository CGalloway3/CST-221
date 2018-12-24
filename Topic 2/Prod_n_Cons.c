/*
** Producer and comsumer implementation using pthread mutex and condition
** main creates the threads and starts them running. They will continue
** lopping until the program is terminated with ctrl-c
** Chad galloway
*/

#include <stdio.h>
#include <pthread.h>

#define TRUE 1

int theProduct;					
_Bool bufferSize = 0;   // Size of buffer 0 or 1
unsigned short WORD;  // Buffer used between producer and consumer 

pthread_mutex_t the_mutex;
pthread_cond_t consumer_waiting, producer_waiting; // used for signaling

void put (unsigned short value) { // Puts the value passed, into the word and increases the buffer Size variable.
	WORD = value;
	bufferSize++;
}

int get() {  // decreases the buffer size variable and returns the word
	bufferSize--;
	return WORD;
}

int produce(){ // Produces the Product.
	printf("Producing item %i \n", (unsigned short)++theProduct);
	return theProduct;
}

void consume(unsigned short w){ // Comsumes the Product.
	printf("Consuming item %i \n", w);
}

void *producer(void *ptr) // Entry point for the producer thread.
{	
	int w;
	
	while (TRUE) {
		pthread_mutex_lock(&the_mutex);  // get exclusive access to buffer
		while (bufferSize == 1) pthread_cond_wait(&producer_waiting, &the_mutex); // Buffer full wait
		w = produce();
		put(w);
		pthread_cond_signal(&consumer_waiting); 	//wake up consumer
		pthread_mutex_unlock(&the_mutex);  //release access to buffer
	}
	pthread_exit(0);
}

void *consumer(void *ptr) // Entry point for the comsumer thread.
{	
	int w;
	
	while (TRUE) {
		pthread_mutex_lock(&the_mutex); //get exclusive access to buffer
		while (bufferSize == 0 ) pthread_cond_wait(&consumer_waiting, &the_mutex);  // Buffer empty wait
		w = get();  //take_item out of buffer
		consume(w);				
		pthread_cond_signal(&producer_waiting); 	//wake upproducer
		pthread_mutex_unlock(&the_mutex);  //release access to buffer
	}
	pthread_exit(0);
} 

int main(int argc, char *argv[])
{
	pthread_t prod, cons;
	pthread_mutex_init(&the_mutex, 0);
	pthread_cond_init(&consumer_waiting, 0);
	pthread_cond_init(&producer_waiting, 0);
	pthread_create(&cons, 0, &consumer, 0);
	pthread_create(&prod, 0, &producer, 0);
	pthread_join(prod, 0);
	pthread_join(cons, 0);
	pthread_cond_destroy(&consumer_waiting);
	pthread_cond_destroy(&producer_waiting);
	pthread_mutex_destroy(&the_mutex);
} 
