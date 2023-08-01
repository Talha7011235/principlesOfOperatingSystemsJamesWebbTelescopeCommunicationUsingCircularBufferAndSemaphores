// Webb Telescope Video and the Bounded Buffer Using Monitors: Use a Monitor Instead of a Semaphore for Locking in User Space
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>
#include "buffer_mon.h"

struct ring_buffer_421 *ringBuffer = NULL;

// Use a Mutex and a Conditional Variable to perform Synchronization.
pthread_mutex_t mutex;
pthread_cond_t condition;

// *********************************************************************************************************************************************
// The Definition of Function "long init_buffer_421(void)" is that the Function "long init_buffer_421(void)" initializes a new Circular        *
// Buffer, in other words it initializes a new Ring Buffer, in user memory for each Node. The Function "long init_buffer_421(void)" does not   *
// reinitialize the buffer if it already exists. In addition, the Function "long init_buffer_421(void)" returns 0 on success and returns -1 on *
// failure.                                                                                                                                    *
// *********************************************************************************************************************************************
long init_buffer_421(void)
{
	// Check to see if the Ring Buffer that is the Circular Buffer is already initialized.
	if (ringBuffer != NULL)
	{
		// Return -1 if it failed for any reason.
		return -1;
	}

	int i = 0;

	// Initialize the Ring Buffer, that is the Circular Buffer, to hold the Node List.
	ringBuffer = (struct ring_buffer_421 *)malloc(sizeof(struct ring_buffer_421));
	ringBuffer->length = 0;

	// Initialize the temp node that is the Temporary Variable "temp_node_421".
	struct node_421* temp_node_421 = NULL;

	// Create a for loop() in order to iterate the number of times of the SIZE_OF_BUFFER because according
        // to the "buffer_sem.h" Header File, the "SIZE_OF_BUFFER" is defined and the value for the SIZE_OF_BUFFER is 20.
	for(int i = 0; i < SIZE_OF_BUFFER; i++)
	{
		// Create a Node Object.
		struct node_421 *pointerOne = (struct node_421 *)malloc(sizeof(struct node_421));

		// Initialize the Node Object Data to a Null Terminator to indicate an empty string.
		pointerOne->data[0] = '\0';

		// Check if the temp node that is the Temporary Variable "temp_node_421" is empty. In addition, the temp node that is the
		// Temporary Variable "temp_node_421" will be empty in the initial case.
		if(temp_node_421 == NULL)
		{
			// Point the Head Node Pointer *write and Tail Node Pointer *read to the Node Object. Furthermore, point the
			// temp node pointer that is the Temporary Variable "temp_node_421" to the Node Object.
			ringBuffer->read = ringBuffer->write = pointerOne;
			temp_node_421 = pointerOne;
			continue;
		}

		// Assign the "next" node to the temp Pointer "temp_node_421" which includes the previously created object.
		pointerOne->next = temp_node_421;

		// Assign the temp Pointer "temp_node_421" to the recently created object.
		temp_node_421 = pointerOne;

	}

	// Assign the head's next node to the last object created. In this case, the temp node that is the Temporary
	// Variable "temp_node_421" includes the last object created. As a result, the Buffer becomes a Circular Linked List
	// from the line of C code shown below that is part of the linked list.
	ringBuffer->write->next = temp_node_421;

	// If Initialization is a success, then return 0. In the case of failure for any reason, return -1.
	// Initialize the pthread, that is the POSIX Thread, "mutex" and "condition".
	pthread_mutex_init(&mutex, NULL);
	pthread_cond_init(&condition, NULL);

	// Return 0 on success. In the case of failure, return -1.
	return 0;
}

// **********************************************************************************************************************************
// First, the De finition of Function "long enqueue_buffer_421(char *i)" is that the Function "long enqueue_buffer_421(char *i)"    *
// copies 1024 Bytes from the "data" into the "write" node's data variable. Second, the Function "long enqueue_buffer_421(char *i)" *
// correctly updates the buffer's "length" and Tail Node Pointer *write. The Function "long enqueue_buffer_421(char *i)" cannot     *
// insert data into a buffer that is not initialized. In addition, the Function "long enqueue_buffer_421(char *data)" cannot        *
// insert data into a full buffer and when this happens, a Monitor is used to ensure the buffer has room for inserting the          *
// buffer. Finally, the Function "long enqueue_buffer_421(char *i)" returns 0 on success and returns -1 on failure.                 *
// **********************************************************************************************************************************
long enqueue_buffer_421(char *i)
{
	// Check if the Ring Buffer that is the Circular Buffer is already initialized.
	if(ringBuffer == NULL)
	{
		return -1;
	}

	// Lock the Mutex in order to have exclusive access to the Critical Section.
	pthread_mutex_lock(&mutex);

	// Wait inside the Monitor loop until the Thread is allowed to enter the Critical Section. It will wait for a Signal to wake up and check
	// again.
	while(ringBuffer->length >= SIZE_OF_BUFFER)
	{
		pthread_cond_wait(&condition, &mutex);
	}

	printf("Enqueue: %s\n", i);

	// Copy the data that is enqueued into the Ring Buffer that is the Circular Buffer.
	strcpy(ringBuffer->write->data, i);
	ringBuffer->length++;

	// After finishing the enqueuing of the value, send a Signal to all of the waiting threads that they can wake up and check to see
	// if they are allowed into the Critical Section.
	pthread_cond_broadcast(&condition);

	// Move the Head Pointer *write to the "next" buffer position.
	ringBuffer->write = ringBuffer->write->next;

	// Release the Mutex so that other Threads can capture it.
	pthread_mutex_unlock(&mutex);

	// Return 0 on success. In the case of failure, return -1.
}

// ******************************************************************************************************************************************
// First, the Definition of Function "long dequeue_buffer_421(char *data)" is that the Function "long dequeue_buffer_421(char *data)"       *
// copies 1024 Bytes from the Head Node "read" into the provided buffer data. Second, the Function "long dequeue_buffer_421(char *data)"    *
// correctly updates the buffer's "length" and Head Node Pointer "*read". The Function "long dequeue_buffer_421(char *data)" cannot         *
// dequeue a buffer that is not initialized. In addition, the Function "long dequeue_buffer_421(char *data)" cannot dequeue and as a result *
// of this, the length has to equal to 0. Furthermore, in the Function "long dequeue_buffer_421(char *data)", in order to make sure the     *
// Function "long dequeue_buffer_421(char *data)" cannot dequeue an empty buffer, a Monitor is used to ensure that the buffer is not empty  *
// before the dequeue. Finally, the Function "long dequeue_buffer_421(char *data)" returns 0 on success and returns -1 on failure.          *
// ******************************************************************************************************************************************
long dequeue_buffer_421(char *data)
{
	// Check if the Ring Buffer that is the Circular Buffer is already initialized.
	if(ringBuffer == NULL)
	{
		return -1;
	}

	// Lock the Mutex in order to have exclusive access to the Critical Section.
	pthread_mutex_lock(&mutex);

	// Wait inside the Monitor loop until the Thread is allowed to enter the Critical Section. It will wait for a Signal to wake up and check
        // again.
	while(ringBuffer->length <= 0)
	{
		pthread_cond_wait(&condition, &mutex);
	}

	// Move the data from the Ring Buffer that is the Circular Buffer into the provided Pointer Variable *data.
	strcpy(data, ringBuffer->read->data);
	ringBuffer->read->data[0] = '\0';
	ringBuffer->length--;

	printf(":: Dequeueing element from buffer. ::\n");
	printf("%s\n", data);
	printf("%d items in buffer.\n", ringBuffer->length);
	pthread_cond_broadcast(&condition);

	// Move the Tail Node Pointer *read through the Ring Buffer that is the Circular Buffer.
	ringBuffer->read = ringBuffer->read->next;

	// Release the Mutex.
	pthread_mutex_unlock(&mutex);

	// Return 0 on success. In the case of failure, return -1.
	return 0;
}

// **********************************************************************************************************************************
// The Definition of Function "long delete_buffer_421(void)" is that the Function "long delete_buffer_421(void)" deletes the buffer *
// if it exists. In addition, the Function "long delete_buffer_421(void)" frees memory in user-space that is allocated              *
// in the "init_buffer_421(void)" Function. Furthermore, in terms of the buffer, if it is successful, then the                      *
// Function "long delete_buffer_421()" returns 0, otherwise, if it fails, then the Function "long delete_buffer_421()" returns -1.  *
// **********************************************************************************************************************************
long delete_buffer_421(void)
{
	// Check if the Ring Buffer that is the Circular Buffer is already initialized.
	if(ringBuffer == NULL)
	{
		return -1;
	}

	// Point the temp node that is the Temporary Variable "temp_two_node_421" to the Head Node *write.
	struct node_421* temp_two_node_421 = ringBuffer->write;

	// Traverse throughout the Ring Buffer that is the Circular Buffer with the purpose of checking if the Head Node *write is not
	// pointing to itself to ensure that the Head Node *write is not a single node in the Circular Linked List.
	while(ringBuffer->write->next != ringBuffer->write)
	{
		// Assign the "next" node of the Head Node *write to the temp node that is the Temporary Variable "temp_two_node_421". As a 
		// result, the temp node that is the Temporary Variable "temp_two_node_421" will point to the "next" node of the
		// Head Node *write.
		temp_two_node_421 = ringBuffer->write->next;

		// The Head Node *write next will be assigned with the address in the current temp node that is the
		// Temporary Variable "temp_two_node_421" "next" in order for the temp node "temp_two_node_421" to
		// be deleted. As a result, this will break the link between the Head Node *write and the temp node
		// that is the Temporary Variable "temp_two_node_421".
		ringBuffer->write->next = temp_two_node_421->next;

		// Free the memory of the temp node "temp_two_node_421"
		free(temp_two_node_421);

		// Empty the temp node that is the Temporary Variable "temp_two_node_421".
		temp_two_node_421 = NULL;
	}

	// Free the memory of the Head Node *write.
	free(ringBuffer->write);

	// Set the Variable "buffer" to NULL so that it no longer points to the freed memory.
	free(ringBuffer);
	ringBuffer = NULL;

	// Destroy the Mutex and Condition Variable.
	pthread_mutex_destroy(&mutex);
	pthread_cond_destroy(&condition);
	return 0;
}
