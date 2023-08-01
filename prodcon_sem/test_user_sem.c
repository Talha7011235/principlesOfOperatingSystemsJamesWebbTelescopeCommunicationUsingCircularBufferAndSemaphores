// Project 3 Part 2 Test File for Webb Telescope Video and the Bounded Buffer that is the Producer-Consumer Problem Using Semaphores
// in User Space
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include "buffer_sem.h"

sem_t semaphore_print;

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
	// Initialize the random generator with a different value to the Consumer Thread.
	srand(65161);

	// In order for the Producer to add to the queue, initialize a basic block of chars.
	char block[DATA_LENGTH];

	// Create a for() loop to loop 1000 times for the purpose of adding to the Ring Buffer.
	for(int i = 0; i < 1000; ++i)
	{
		// Generate the block to be added to the queue.
		makeBlock(block, i % 10);

		// Capture the Print Semaphore in order to make sure that only one print action occurs at a time.
		sem_wait(&semaphore_print);
		fprintf(stdout, "Produced: %d\n", i % 10);
		sem_post(&semaphore_print);

		// Add the block to the queue.
		enqueue_buffer_421(block);

		// Sleep for a  random number of milliseconds from 0 milliseconds to 10 milliseconds.
		usleep((rand() % 10) * 1000);
	}

	return NULL;
}

// ********************************************************************************************************************************************
// The Definition of Function "void *consumer(void *pForPointer)" is that the Function "void *consumer(void *pForPointer)" is the Thread that *
// will empty the Circular Buffer using the dequeue_buffer_421() Function.                                                                    *
// ********************************************************************************************************************************************
void *consumer(void *pForPointer)
{
	// Initialize the random generator with a different value to the Producer Thread.
	srand(651616);

	// In order for the Producer to add to the queue, initialize a basic block of chars.
	char block[DATA_LENGTH];

	// Create a for() loop to loop 1000 times for the purpose of removing from the Ring Buffer.
	for(int i = 0; i < 1000; ++i)
	{
		// Pull a block from the queue.
		dequeue_buffer_421(block);

		// Capture the Print Semaphore. Then, Print Out the received block ID.
		sem_wait(&semaphore_print);
		fprintf(stdout, "Consumed: %c\n", block[0]);
		sem_post(&semaphore_print);

		// Sleep for a random amount of milliseconds between 0 milliseconds and 10 milliseconds.
		usleep((rand() % 10) * 1000);
	}

	return NULL;
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

	// Initialize the "semaphore_print". In addition, initialize the Producer Thread and initialize the Consumer Thread.
	sem_init(&semaphore_print, 0, 1);
	pthread_t producer_t;
	pthread_t consumer_t;

	// Use the pthread_create() Function to create the Producer Thread. In addition, use the pthread_create() Function to create the
	// Consumer Thread.
	pthread_create(&producer_t, NULL, producer, NULL);
	pthread_create(&consumer_t, NULL, consumer, NULL);

	// The pthread_join() Function causes the system to wait until the thread that is specified is complete.
	pthread_join(producer_t, NULL);
	pthread_join(consumer_t, NULL);

	// Call for the delete_buffer_421() Function in order to delete the buffer and memory inside it.
	delete_buffer_421();

	// Delete the buffer and delete the memory inside it.
	sem_destroy(&semaphore_print);
	return 0;
}
