// Project 3 Part 2 Test File for Webb Telescope Video and the Bounded Buffer that is the Producer-Consumer Problem Using Semaphores
// in Kernel Space
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/syscall.h>
#include <pthread.h>
#include "buffer_sem.h"

#ifndef NR_init_buffer_sem_421
#define NR_init_buffer_sem_421 446
#define NR_enqueue_buffer_sem_421 447
#define NR_dequeue_buffer_sem_421 448
#define NR_delete_buffer_sem_421 449
#endif

sem_t semaphore_print;

// *********************************************************************************************************************************************
// The Definition of Function "void makeBlock(char *buffer, int vForValue)" is that the Function "void makeBlock(char *buffer, int vForValue)" *
// makes a 1024 character block of data to append to the Ring Buffer that is the Circular Buffer.                                              *
// *********************************************************************************************************************************************
void makeBlock(char *buffer, int vForValue)
{
	// Create a for() loop for the whole buffer by setting the character to the alphabetical number of the value passed in.
	for(int i = 0; i < DATA_LENGTH-1; ++i)
	{
		buffer[i] = vForValue + '0';
	}

	buffer[DATA_LENGTH - 1] = '\0';
}

// ********************************************************************************************************************************
// The Definition of Function "void *producer(void *pForPointer)" is that the Function "void *producer(void *pForPointer)" is the *
// Producer Thread for testing the Semaphore Version of the Circular Buffer.                                                      *
// ********************************************************************************************************************************
void *producer(void *pForPointer)
{
	// Initialize the random generator with a different seed to the Consumer Thread.
	srand(65161);

	// Initialize a data block to hold the information produced.
	char block[DATA_LENGTH];

	// Create a for() loop to loop 1000 times for the purpose of adding to the Ring Buffer.
	for(int i = 0; i < 1000; ++i)
	{
		// Build the block of characters to fill the buffer with.
		makeBlock(block, i % 10);

		// Use "semaphore_print" to Print Out the Result. In addition, the "semaphore_print" has to be blocked by a Semaphore
		// in order to prevent issues with printing to the Output from Multiple Threads.
		sem_wait(&semaphore_print);
		fprintf(stdout, "Produced: %d\n", i % 10);
		sem_post(&semaphore_print);

		// Call the kernel function for enqueing the "block" data into the buffer.
		syscall(NR_enqueue_buffer_sem_421, block);

		// Sleep for a random time in milliseconds from 0 milliseconds to 10 milliseconds.
		usleep((rand() % 10) * 1000);
	}

	return NULL;
}

// ********************************************************************************************************************************
// The Definition of Function "void *consumer(void *pForPointer)" is that the Function "void *consumer(void *pForPointer)" is the *
// Consumer Thread for testing the Semaphore Version of the Circular Buffer.                                                      *
// ********************************************************************************************************************************
void *consumer(void *pForPointer)
{
	// Initialize the random number generator to a different seed than the Producer Thread.
	srand(651616);

	// Initialize a data block to hold the information consumed.
	char block[DATA_LENGTH];

	// Create a for() loop to loop 1000 times for the purpose of reading from the Ring Buffer.
	for(int i = 0; i < 1000; ++i)
	{
		// Call the kernel function for dequeueing in order to consume a place in the buffer and return it to "block".
		syscall(NR_dequeue_buffer_sem_421, block);

		// Use "semaphore_print" to Print Out the Result. In addition, the "semaphore_print" has to be blocked by a Semaphore
		// in order to prevent issues with printing to the Output from Multiple Threads.
		sem_wait(&semaphore_print);
		fprintf(stdout, "Consumed: %c\n", block[0]);
		sem_post(&semaphore_print);

		// Sleep for a random time in milliseconds from 0 milliseconds to 10 milliseconds.
		usleep((rand() % 10) * 1000);
	}

	return NULL;
}

int main()
{
	// Call the kernel function for initializing the buffer in order to test the error condition if the initialized buffer
	// returns a nonzero, then print out the statement that tells the user that he or she cannot initialize the buffer and semaphores.
	if(syscall(NR_init_buffer_sem_421) != 0)
	{
		fprintf(stderr, "Cannot initialize the buffer and semaphores.\n");
		return -1;
	}

	// Initialize the "semaphore_print".
	sem_init(&semaphore_print, 0, 1);

	// Define the Thread Structure for the Producer Thread and define the Thread Structure for the Consumer Thread.
	pthread_t producer_t;
	pthread_t consumer_t;

	// Use the pthread_create() Function to create the Producer Thread. In addition, use the pthread_create() Function to create the
	// Consumer Thread.
	pthread_create(&producer_t, NULL, producer, NULL);
	pthread_create(&consumer_t, NULL, consumer, NULL);

	// Use the pthread_join() Function to wait for the Producer Thread to complete. In addition, use the pthread_join() Function to wait
	// for the Consumer Thread to complete.
	pthread_join(producer_t, NULL);
	pthread_join(consumer_t, NULL);

	// Call the kernel function for deleting the buffer in order to delete the buffer.
	syscall(NR_delete_buffer_sem_421);

	// Destroy the Semaphore.
	sem_destroy(&semaphore_print);
	return 0;
}
