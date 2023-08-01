// Project 3 Part 3 Test File for Web Telescope Video and the Bound Buffer Using Monitors: Use a Monitor Instead of a Semaphore for Locking in
// User Space
#include <stdio.h>
#include <stdlib.h>
#include <semaphore.h>
#include <pthread.h>
#include <unistd.h>
#include "buffer_mon.h"

sem_t print;

// *********************************************************************************************************************************************
// The Definition of Function "void makeBlock(char *buffer, int vForValue)" is that the Function "void makeBlock(char *buffer, int vForValue)" *
// takes a value that is represented by the variable "int vForValue" and builds a block of DATA_LENGTH characters of that value.               *
// *********************************************************************************************************************************************
void makeBlock(char *buffer, int vForValue)
{
	for(int i = 0; i < DATA_LENGTH-1; ++i)
	{
		buffer[i] = vForValue + '0';
	}
	buffer[DATA_LENGTH - 1] = '\0';
}

// ********************************************************************************************************************************************
// The Definition of Function "void *producer(void *pForPointer)" is that the Function "void *producer(void *pForPointer)" is the Thread that *
// will fill the Circular Buffer using the enqueue_buffer_421() Function.                                                                     *
// ********************************************************************************************************************************************
void *producer(void *pForPointer)
{
	// Initialize the random number generator to a different seed than the Consumer Thread.
	srand(65161);

	// Initialize a data block to hold the information produced.
	char block[DATA_LENGTH];

	// Create for() loop to loop 1000 times for the purpose of adding to the Ring Buffer.
	for(int i = 0; i < 1000; ++i)
	{
		// Build the block of characters to fill the buffer with.
		makeBlock(block, i % 10);

		// Print Out the Result. The "print" needs to be blocked by a semaphore to prevent issues with printing to the output from
		// Multiple Threads.
		sem_wait(&print);
		fprintf(stdout, "Produced: %d\n", i % 10);
		sem_post(&print);

		// Call the Enqueue Function, the "enqueue_buffer_421()" Function, to enqueue the "block" data into the buffer.
		enqueue_buffer_421(block);

		// Sleep for a Random Time.
		usleep((rand() % 10) * 1000);
	}
}

// ********************************************************************************************************************************************
// The Definition of Function "void *consumer(void *pForPointer)" is that the Function "void *consumer(void *pForPointer)" is the Thread that *
// will empty the Circular Buffer using the dequeue_buffer_421() Function.                                                                    *
// ********************************************************************************************************************************************
void *consumer(void *pForPointer)
{
	// Initialize the random number generator to a different seed than the Producer Thread.
	srand(651616);

	// Initialize a data block to hold the information consumed.
	char block[DATA_LENGTH];

	// Create for() loop to loop 1000 times for the purpose of reading from the Ring Buffer.
	for(int i = 0; i < 1000; ++i)
	{
		dequeue_buffer_421(block);

		// Print Out the Result. The "print" needs to be blocked by a semaphore to prevent issues with printing to the output from 
		// Multiple Threads.
		sem_wait(&print);
		fprintf(stdout, "Consumed: %c\n", block[0]);
		sem_post(&print);

		// Sleep for a Random Time.
		usleep((rand() % 10) * 1000);
	}
}

int main()
{
	// Test the error condition for if the initialized buffer returns a nonzero, then print out the statement that tells the user
	// that he or she cannot initialize the buffer and semaphores.
	if(init_buffer_421() != 0)
	{
		fprintf(stderr, "Cannot initialize the buffer and semaphores.\n");
		return -1;
	}

	// Initialize the print semaphore.
	sem_init(&print, 0 , 1);

	// Define the Thread Structures for the Producer Thread and Consumer Thread.
	pthread_t producer_t;
	pthread_t consumer_t;

	// Create the Producer Thread and create the Consumer Thread.
	pthread_create(&producer_t, NULL, producer, NULL);
	pthread_create(&consumer_t, NULL, consumer, NULL);

	// Wait for the Producer Thread and wait for the Consumer Thread to complete before moving on.
	pthread_join(producer_t, NULL);
	pthread_join(consumer_t, NULL);

	// Call for the "delete_buffer_421() Function in order to delete the buffer.
	delete_buffer_421();

	// Destroy the semaphore.
	sem_destroy(&print);
	return 0;
}
