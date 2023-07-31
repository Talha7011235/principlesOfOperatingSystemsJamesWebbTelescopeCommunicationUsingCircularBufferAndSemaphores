// Project 3 Part 1 Creating a Circular Buffer for User Space
#include <stdio.h>
#include <stdlib.h>
#include "buffer.h"

struct ring_buffer_421* ringBuffer = NULL;

// ************************************************************************************************************************************
// First, the Definition of Function "long init_buffer_421(void)" is that the Function "long_init_buffer_421(void)" initializes a new *
// Circular Buffer, in other words it initializes a new Ring Buffer, in memory and allocates memory for each Node. Second, the        *
// Function "long_init_buffer_421(void)" includes a total of "SIZE_OF_BUFFER" Nodes for the size of the buffer. Third, in the         *
// Function "long_init_buffer_421(void)", the last node's next pointer points to the first node to create a Circle. Then, in the      *
// Function "long_init_buffer_421(void)", each Node stores an Initial Integer Value of 0. Finally, in the                             *
// Function "long_init_buffer_421(void)", if Initialization is a success, then it returns 0. However, in the case of failure, if      *
// it fails for any reason, then the Function "long_init_buffer_421(void)", returns -1. Furthermore, the                              *
// Function "long init_buffer_421(void)" does not reinitialize the Circular Buffer that is the Ring Buffer if it already exists.      *
// not reinitialize the buffer if it already exists.                                                                                  *
// ************************************************************************************************************************************
long init_buffer_421(void)
{
	// Check to see if the Ring Buffer that is the Circular Buffer is already initialized.
	if(ringBuffer != NULL)
	{
		// Return -1 as the function has failed.
		return -1;
	}

	int i = 0;

	// Initialize the Ring Buffer, that is the Circular Buffer, to hold the Node List.
	ringBuffer = (struct ring_buffer_421 *)malloc(sizeof(struct ring_buffer_421));
	ringBuffer->length = 0;

	// Initialize the temp node that is the Temporary Variable "temp_node_421".
	struct node_421* temp_node_421 = NULL;

	// Create a while() loop in order to iterate "SIZE_OF_BUFFER" times because the "SIZE_OF_THE_BUFFER" is defined
        // in the "buffer.h" Header File. In addition, the "SIZE_OF_BUFFER" is initially defined as 20.
	while(i < SIZE_OF_BUFFER)
	{
		// Create a Node Object.
		struct node_421 *pointerOne = (struct node_421 *)malloc(sizeof(struct node_421));

		// Check if the temp node that is the Temporary Variable "temp_node_421" is empty. In addition, the temp node that is the
		// Temporary Variable "temp_node_421" will be empty in the initial case.
		if(temp_node_421 == NULL)
		{
			// Point the Head Node Pointer *write and the Tail Node Pointer *read to the Node Object. Furthermore, point the
			// temp node pointer that is the Temporary Variable "temp_node_421" to the Node Object.
			ringBuffer->read = ringBuffer->write = pointerOne;
			temp_node_421 = pointerOne;
		}
		else
		{
			// Initialize the Node Object Data to 0. If 0 is a value given by the user, then it can be -1.
			pointerOne->data = 0;

			// Assign the "next" node to the temp Pointer "temp_node_421" which includes the previously created object.
			pointerOne->next = temp_node_421;

			// Assign the temp Pointer "temp_node_421" to the recently created object.
			temp_node_421 = pointerOne;
		}
		// Increment the Iterator.
		i++;
	}

	// Initialize the head object data.
	ringBuffer->write->data = 0;

	// Assign the head's next node to the last object created. In this case, the temp node that is the Temporary
	// Variable "temp_node_421" includes the last object created. As a result, the Buffer becomes a Circular Linked List
	// from the line of C code shown below that is part of the linked list.
	ringBuffer->write->next = temp_node_421;

	// If Initialization is a success, then return 0. In the case of failure for any reason, return -1.
	return 0;
}

// ***********************************************************************************************************************************
// The Definition of Function "long insert_buffer_421(int i) is that the Function "long insert_buffer_421(int i)" inserts the        *
// Integer i into the next available node. In addition, the Function "long insert_buffer_421(int i)" increments the length           *
// of the buffer. The Function "long insert_buffer_421(int i)" cannot insert data into an uninitialized buffer. Moreover, in the     *
// Function "long insert_buffer_421(int i)", if the buffer is already full, then that means the inserting fails. Furthermore, in the *
// Function "long insert_buffer_421(int i)", if the insert is successful, then it returns 0. However, if the insert fails in the     *
// Function "long isnert_buffer_421(int i)", then it returns -1.                                                                     *
// ***********************************************************************************************************************************
long insert_buffer_421(int i)
{
	// Check if the Ring Buffer that is the Circular Buffer is already initialized.
	if(ringBuffer == NULL)
	{
		// Return -1 as the function has failed.
		return -1;
	}
	// Check if the Ring Buffer that is the Circular Buffer is already full.
	if(ringBuffer->length >= SIZE_OF_BUFFER)
	{
		// Return -1 as the function has failed.
		return -1;
	}

	// Initialize the variable "iterator".
	int iterator = 0;

	// Iterate throughout the buffer.
	while(iterator <= SIZE_OF_BUFFER)
	{
		// Consider zero as an empty block and check whether the temp data is zero because the data is initialized to zero.
		if(ringBuffer->write->data == 0)
		{
			printf("Enqueue: %d\n", i);
			// If the temp data is zero, then the passed value is assigned to "data" and returns 0 to indicate
			// that the insert is successful.
			ringBuffer->write->data = i;
			ringBuffer->length++;
			return 0;
		}
		// In the case if the data is not zero, then it means the data is previously assigned. Therefore, traverse through the next node
		// by assigning temp to the "next" node of temp.
		ringBuffer->write = ringBuffer->write->next;

		// Increment the iterator.
		iterator++;
	}
	// If the buffer is already full, then inserting fails. In other words, this means that outside of the while() loop, all the data
	// becomes filled up. Therefore, in this case, after the while() loop completes, it will return -1.
	return -1;
}

// *********************************************************************************************************************************************
// The Definition of Function "long print_buffer_421()" is that the Function "long print_buffer_421()" writes a string representation of       *
// every Node in the buffer, along with the data in each Node, and prints to the stdout. In addition, the Function "long print_buffer_421()"   *
// starts at the buffer's read pointer. The Function "long print_buffer_421()" prints the values of the buffer. However, when it comes         *
// to a buffer that is not initialized, the Function "long print_buffer_421()" cannot print an uninitialized buffer. Furthermore, in terms     *
// of the buffer, if it is successful, then the Function "long print_buffer_421()" returns 0, otherwise, if it fails, then the Print           *
// Function "long print_buffer_421()" returns -1.                                                                                              *
// *********************************************************************************************************************************************
long print_buffer_421()
{
	// Check if the Ring Buffer that is a Circular Buffer is already initialized.
	if(ringBuffer == NULL)
	{
		// Return -1 as the function has failed.
		return -1;
	}
	// Initialize the variable "iterator".
	int iterator = 0;

	// Traverse through the buffer.
	while(iterator < SIZE_OF_BUFFER)
	{
		// Print the node data.
		printf("%d\n", ringBuffer->read->data);
		// Change temp to point to the next node of temp.
		ringBuffer->read = ringBuffer->read->next;
		// Increment the iterator.
		iterator++;
	}
	return 0;
}

// **********************************************************************************************************************************************
// The Definition of Function "long delete_buffer_421(void)" is that the Function "long delete_buffer_421(void)" is used to delete the complete *
// buffer and not the single node. In other words, the Function "long delete_buffer_421(void)" deletes the buffer if it exists. Moreover, the   *
// Function "long delete_buffer_421(void)" frees any memory in the user space that is allocated in the Function "long init_buffer_421()". In    *
// addition, in terms of the buffer, if it is successful, then the Function "long delete_buffer_421(void)" returns 0, otherwise, if it fails,   *
// then the Function "long delete_buffer_421(void)" returns -1.                                                                                 *
// **********************************************************************************************************************************************
long delete_buffer_421(void)
{
	// Check if the Ring Buffer that is the Circular Buffer is already initialized.
	if(ringBuffer == NULL)
	{
		// Return -1 as the function has failed.
		return -1;
	}

	// Point the temp node that is the Temporary Variable "temp_two_node_421" to the Head Node *write.
	struct node_421* temp_two_node_421 = ringBuffer->write;

	// Traverse throughout the Buffer with the purpose of checking if the Head Node *write is not pointing to itself to ensure
	// that the Head Node *write is not a single node in the Circular Linked List.
	while(ringBuffer->write->next != ringBuffer->write)
	{
		// Assign the "next" node of the Head Node *write to the temp node that is the Temporary Variable "temp_two_node_421". As a
		// result, the temp node that is the Temporary Variable "temp_two_node_421" will point to the "next" node of the
		// Head Node *write.
		temp_two_node_421 = ringBuffer->write->next;

		// The Head Node *write next will be assigned with the address in the current temp node that is the
		// Temporary Variable "temp_two_node_421" "next" in order for the temp node "temp_two_node_421" to
		// be deleted. As a result, this will break the link between the Head Node *write and the temp node
		// that is the Temporary Variable "temp_two_Node_421".
		ringBuffer->write->next = temp_two_node_421->next;

		// Free the memory of the temp node that is the Temporary Variable "temp_two_node_421".
		free(temp_two_node_421);

		// Empty the temp node that is the Temporary Variable "temp_two_node_421".
		temp_two_node_421 = NULL;
	}
	// Once it is a single node, it will come out of the loop. Therefore, free the memory of the Head Node *write.
	free(ringBuffer->write);

	// Once all of the memory is inside the variable "ringBuffer", free the variable "ringBuffer" itself.
	free(ringBuffer);

	// Set the variable "ringBuffer" to NULL so that it no longer points to the freed memory.
	ringBuffer = NULL;
	return 0;
}
