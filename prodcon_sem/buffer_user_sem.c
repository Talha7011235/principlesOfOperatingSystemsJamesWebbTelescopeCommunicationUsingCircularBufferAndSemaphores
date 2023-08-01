// Project 3 Part 2 Webb Telescope Video and the Bounded Buffer Using Semaphores: Semaphores in User Space
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "buffer_sem.h"

static bb_buffer_421_t *buffer;
static sem_t mutex;
static sem_t fill_count;
static sem_t empty_count;

// *********************************************************************************************************************************************
// The Definition of Function "long init_buffer_421(void)" is that the Function "long init_buffer_421(void)" initializes a new Circular        *
// Buffer, in other words it initializes a new Ring Buffer, in user memory for each Node. The Function "long init_buffer_421(void)" does not   *
// reinitialize the buffer if it already exists. In addition, the Function "long init_buffer_421(void)" returns 0 on success and returns -1 on *
// failure.                                                                                                                                    *
// *********************************************************************************************************************************************
long init_buffer_421(void) {
	// Write your code to initialize buffer
	// Check to see if the buffer is already initialized.
	if(buffer != NULL)
	{
		// Return -1 as the function has failed.
		return -1;
	}

	// Initialize the buffer to hold the Node List.
	buffer = (bb_buffer_421_t  *)malloc(sizeof(bb_buffer_421_t));
	buffer->length = 0;

	// Initialize the temp node that is the Temporary Variable "temp_node_421".
	struct bb_node_421* temp_node_421 = NULL;

	// Create a for loop() in order to iterate "SIZE_OF_BUFFER" times because the "SIZE_OF_BUFFER" is defined
	// in the "buffer_sem.h" Header File. In addition, the "SIZE_OF_BUFFER" is initially defined as 20.
	for(int i = 0; i < SIZE_OF_BUFFER; i++)
	{
		// Create a Node Object.
		bb_node_421_t *pointerOne = (bb_node_421_t *)malloc(sizeof(bb_node_421_t));

		// Initialize the Node Object Data to a Null Terminator to indicate an empty string.
		pointerOne->data[0] = '\0';
		// Check if the temp node that is the Temporary Variable "temp_node_421" is empty. In addition, the temp node that is the
		// Temporary Variable "temp_node_421" will be empty in the initial case.
		if(temp_node_421 == NULL)
		{
			// Point the Head Node Pointer *write and the Tail Node Pointer *read to the Node Object. Furthermore, point the
			// temp node pointer that is the Temporary Variable "temp_node_421" to the Node Object.
			buffer->read = buffer->write = pointerOne;
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
	buffer->write->next = temp_node_421;

	// If Initialization is a success, then return 0. In the case of failure for any reason, return -1.
	// Initialize your semaphores here.
	sem_init(&mutex, 0, 1);
	sem_init(&fill_count, 0, 0);
	sem_init(&empty_count, 0, SIZE_OF_BUFFER);
	return 0;
}

// *************************************************************************************************************************************
// First, the Definition of Function "long enqueue_buffer_421(char *data)" is that the Function "long enqueue_buffer_421(char *data)"  *
// copies 1024 Bytes from the "data" into the "write" node's data variable. Second, the Function "long enqueue_buffer_421(char *data)" *
// correctly updates the buffer's "length" and Tail Node Pointer *write. The Function "long enqueue_buffer_421(char *data)" cannot     *
// insert "data" into a buffer that is not initialized. In addition, the Function "long enqueue_buffer_421(char *data)" cannot         *
// insert "data" into a full buffer and when this happens, the caller has to be blocked as a result of using a Semaphore. Finally, the *
// Function "long enqueue_buffer_421(char *data)" returns 0 on success and returns -1 on failure.                                      *
// *************************************************************************************************************************************
long enqueue_buffer_421(char * data) {
	// Write your code to enqueue data into the buffer
	// Check if the buffer is already initialized.
	if(buffer == NULL)
	{
		// Return -1 as the Function has failed.
		return -1;
	}

	// Check if the buffer is already a full block.
	sem_wait(&empty_count);

	sem_wait(&mutex);

	// The sem_wait(&empty_count) Function made sure that the buffer is not full at this point. Therefore, proceed with enqueueing. Then,
	// retrieve the data from the provided pointer and pass it to the buffer.
	strcpy(buffer->write->data, data);
	buffer->length++;

	printf(":: Enqueueing element into buffer. ::\n");
	printf("%s\n", data);
	printf("%d items in buffer.\n", buffer->length);
	sem_post(&fill_count);
	print_semaphores();

	// Move the Head Node Pointer *write to the "next" space in the Circular Buffer.
	buffer->write = buffer->write->next;

	// Release the Mutex for working with the Circular Buffer.
	sem_post(&mutex);
	// Return 0 on success. In the case of failure, return -1.
	return 0;
}

// ******************************************************************************************************************************************
// First, the Definition of Function "long dequeue_buffer_421(char *data)" is that the Function "long dequeue_buffer_421(char *data)"       *
// copies 1024 Bytes from the Head Node "read" into the provided buffer data. Second, the Function "long dequeue_buffer_421(char *data)"    *
// correctly updates the buffer's "length" and Head Node Pointer "*read". The Function "long dequeue_buffer_421(char *data)" cannot         *
// dequeue a buffer that is not initialized. In addition, the Function "long dequeue_buffer_421(char *data)" cannot dequeue and as a result *
// of this, the length has to equal to 0. Furthermore, in the Function "long dequeue_buffer_421(char *data)", in order to make sure the     *
// Function "long dequeue_buffer_421(char *data)" cannot dequeue an empty buffer, the caller has to be blocked as a result of               *
// using a Semaphore. Finally, the Function "long dequeue_buffer_421(char *data)" returns 0 on success and returns -1 on failure.           *
// ******************************************************************************************************************************************
long dequeue_buffer_421(char * data) {

	// Write your code to dequeue data from the buffer
	// Check if the buffer is already initialized.
	if(buffer == NULL)
	{
		// Return -1 as the function has failed.
		return -1;
	}
	// Check if the buffer is already full.
	sem_wait(&fill_count);

	sem_wait(&mutex);

	// The sem_wait(&fill_count) Function made sure that the buffer is not empty at this point. Therefore, proceed with dequeueing.
	strcpy(data, buffer->read->data);
	buffer->read->data[0] = '\0';
	buffer->length--;

	printf(":: Dequeueing element from buffer. ::\n");
	printf("%s\n", data);
	printf("%d items in the buffer.\n", buffer->length);
	sem_post(&empty_count);
	print_semaphores();

	// Move the Tail Node Pointer *read to the "next" space in the Circular Buffer.
	buffer->read = buffer->read->next;

	// Release the Mutex for working with the Circular Buffer.
	sem_post(&mutex);

	// Return 0 on success. In the case of failure, return -1.
	return 0;
}

// **********************************************************************************************************************************
// The Definition of Function "long delete_buffer_421(void)" is that the Function "long delete_buffer_421(void)" deletes the buffer *
// if it exists. In addition, the Function "long delete_buffer_421(void)" frees memory in user-space that is allocated              *
// in the "init_buffer_421()" Function. Furthermore, in terms of the buffer, if it is successful, then the                          *
// Function "long delete_buffer_421()" returns 0, otherwise, if it fails, then the Function "long delete_buffer_421()" returns -1.  *
// **********************************************************************************************************************************
long delete_buffer_421(void) {
	// Tip: Don't call this while any process is waiting to enqueue or dequeue.
	sem_wait(&mutex);

	// Check if the buffer is already initialized.
	if(buffer == NULL)
	{
		// Return -1 as the function has failed.
		return -1;
	}

	// Point the temp node that is the Temporary Variable "temp_two_node_421" to the Head Node *write.
	bb_node_421_t* temp_two_node_421 = buffer->write;

	// Traverse throughout the Buffer with the purpose of checking if the Head Node *write is not pointing to itself to ensure
	// that the Head Node *write is not a single node in the Circular Linked List.
	while(buffer->write->next != buffer->write)
	{
		// Assign the "next" node of the Head Node *write to the temp node that is the Temporary Variable "temp_two_node_421". As a
		// result, the temp node that is the Temporary Variable "temp_two_node_421" will point to the "next" node of the
		// Head Node *write.
		temp_two_node_421 = buffer->write->next;

		// The Head Node *write next will be assigned with the address in the current temp node that is the
		// Temporary Variable "temp_two_node_421" "next" in order for the temp node "temp_two_node_421" to
		// be deleted. As a result, this will break the link between the Head Node *write and the temp node
		// that is the Temporary Variable "temp_two_node_421".
		buffer->write->next = temp_two_node_421->next;

		// Free the malloc memory in the temp node "temp_two_node_421".
		free(temp_two_node_421);

		// Empty the temp node that is the Temporary Variable "temp_two_node_421".
		temp_two_node_421 = NULL;
	}
	// Free the memory of the Head Node *write.
	free(buffer->write);

	free(buffer);
	buffer = NULL;

	// write your code to delete buffer and other unwanted components
	sem_post(&mutex);

	sem_destroy(&mutex);
	sem_destroy(&fill_count);
	sem_destroy(&empty_count);
	return 0;
}

void print_semaphores(void) {
	// You can call this method to check the status of the semaphores.
	// Don't forget to initialize them first!
	// YOU DO NOT NEED TO IMPLEMENT THIS FOR KERNEL SPACE.
	int value;
	sem_getvalue(&mutex, &value);
	printf("sem_t mutex = %d\n", value);
	sem_getvalue(&fill_count, &value);
	printf("sem_t fill_count = %d\n", value);
	sem_getvalue(&empty_count, &value);
	printf("sem_t empty_count = %d\n", value);
	return;
}
