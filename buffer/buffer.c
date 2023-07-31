// Project 3 Part 1 Creating a Circular Buffer for Kernel Space
#include <linux/kernel.h>
#include <linux/syscalls.h>
#include <linux/module.h>
#include <linux/slab.h>
#include "buffer.h"

static struct ring_buffer_421* ringBuffer = NULL;

// *********************************************************************************************************************************************
// First, the System Macro "SYSCALL_DEFINE0(init_buffer_421)" initializes a new Circular Buffer, in other words, it initializes a new          *
// Ring Buffer, in memory and allocates memory for each Node in kernel space. Second, the System Macro "SYSCALL_DEFINE0(init_buffer_421)"      *
// includes a total of "SIZE_OF_BUFFER" Nodes inside the buffer. Third, in the System Macro "SYCALL_DEFINE0(init_buffer_421)", the             *
// last node's next pointer points to the first node to create a Circle. Then, in the System Macro "SYSCALL_DEFINE0(init_buffer_421)", each    *
// Node stores an Initial Integer Value of 0. Finally, in the System Macro "SYSCALL_DEFINE0(init_buffer_421)", if Initialization is a success, *
// then it returns 0. However, in the case of failure, if it fails for any reason, then the System Macro "SYSCALL_DEFINE0(init_buffer_421)"    *
// returns -1. Furthermore, the System Macro "SYSCALL_DEFINE0(init_buffer_421)" does not reinitialize the Circular Buffer that is the          *
// Ring Buffer if it already exists.                                                                                                           *
// *********************************************************************************************************************************************
SYSCALL_DEFINE0(init_buffer_421)
{
	int i;
	struct node_421 *temp_node_421;
	struct node_421 *pointerOne;

	// Check to see if the Ring Buffer that is the Circular Buffer is already initialized.
	if(ringBuffer != NULL)
	{
		// Return -1 as the function has failed.
		return -1;
	}

	i = 0;
	// Initialize the Ring Buffer, that is the Circular Buffer, to hold the Node List.
	ringBuffer = (struct ring_buffer_421 *)kmalloc(sizeof(struct ring_buffer_421), GFP_KERNEL);
	ringBuffer->length = 0;

	// Initialize the temp node that is the Temporary Variable "temp_node_421".
	temp_node_421 = NULL;

	// Create a while() loop in order to iterate "SIZE_OF_BUFFER" times because the "SIZE_OF_THE_BUFFER" is defined
	// in the "buffer.h" Header File. In addition, the "SIZE_OF_BUFFER" is initially defined as 20.
	while(i < SIZE_OF_BUFFER)
	{
		// Create a Node Object.
		pointerOne = (struct node_421 *)kmalloc(sizeof(struct node_421), GFP_KERNEL);

		// Check if the temp node that is the Temporary Variable "temp_node_421" is empty. In addition, the temp node that is the
		// Temporary Variable "temp_node_421" will be empty in the initial case.
		if(temp_node_421 == NULL)
		{
			// Point the Head Node Pointer *write and Tail Node Pointer *read to the Node Object. Furthermore, point the temp node
			// pointer that is the Temporary Variable "temp_node_421" to the Node Object.
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

	// Initialze the head object data.
	ringBuffer->write->data = 0;

	// Assign the head's next node to the last object created. In this case, the temp node that is the Temporary
	// Variable "temp_node_421" includes the last object created. As a result, the Buffer becomes a Circular Linked List from the line
	// of C code shown below that is a part of that linked list.
	ringBuffer->write->next = temp_node_421;

	// If Initialization is a success, then return 0. In the case of failure for any reason, return -1.
	return 0;
}

// **********************************************************************************************************************************************
// The System Macro "SYSCALL_DEFINE1(insert_buffer_421, int, i)" inserts the Integer i into the next available node. In addition, the           *
// System Macro "SYSCALL_DEFINE1(insert_buffer_421, int, i)" increments the length of the buffer. When it comes to an uninitialized buffer, the *
// System Macro "SYSCALL_DEFINE1(insert_buffer_421, int, i)" cannot insert data into an uninitialized buffer. Moreover, in the                  *
// System Macro "SYSCALL_DEFINE1(insert_buffer_421, int, i)", if the buffer is already full, then that means the inserting fails. Furthermore,  *
// in the System Macro "SYSCALL_DEFINE1(insert_buffer_421, int, i)", if the insert is successful, then it returns 0. However, if the insert     *
// fails in the System Macro "SYSCALL_DEFINE1(insert_buffer_421, int, i)", then it returns -1.                                                  *
// **********************************************************************************************************************************************
SYSCALL_DEFINE1(insert_buffer_421, int, i)
{
	int iterator;
	// Check if the Ring Buffer that is the Circular Buffer is already initialized.
	if(ringBuffer == NULL)
	{
		// Return -1 as the function has failed.
		return -1;
	}
	// Check if the Ring Buffer that is the Circular BUffer is already full.
	if(ringBuffer->length >= SIZE_OF_BUFFER)
	{
		// Return -1 as the function has failed.
		return -1;
	}

	// Initialize the variable "iterator".
	iterator = 0;

	// Iterate throughout the buffer.
	while(iterator <= SIZE_OF_BUFFER)
	{
		// Consider zero as an empty block and check whether the temp data is zero because the data is initialized to zero.
		if(ringBuffer->write->data == 0)
		{
			ringBuffer->write->data = i;
			ringBuffer->length++;
			return 0;
		}
		// In the case if the data is not zero, then it means the data is previously assigned. Therefore, traverse through the next node
		// by assigning temp to the next node of temp.
		ringBuffer->write = ringBuffer->write->next;
		// Increment the iterator.
		iterator++;
	}
	// If the buffer is already full, then inserting fails. In other words, this means that outside of the while() loop, all the data
	// becomes filled up. Therefore, in this case, after the while loop() completes, it will return -1.
	return -1;
}

// *********************************************************************************************************************************************
// The System Macro "SYSCALL_DEFINE0(print_buffer_421)" writes a string representation of every Node in the buffer, along with the data        *
// in each Node, to the kernel log. In addition, the System Macro "SYSCALL_DEFINE0(print_buffer_421)" starts at the buffer's read pointer. The *
// System Macro "SYSCALL_DEFINE0(print_buffer_421)" prints the values of the buffer. However, when it comes to a buffer that is not            *
// initialized, the System Macro "SYSCALL_DEFINE0(print_buffer_421)" cannot print an uninitialized buffer. Furthermore, in terms of the        *
// buffer, if it is successful, then the System Macro "SYSCALL_DEFINE0(print_buffer_421)" returns 0, otherwise, if it fails, then the          *
// System Macro "SYSCALL_DEFINE0(print_buffer_421)" returns -1.                                                                                *
// *********************************************************************************************************************************************
SYSCALL_DEFINE0(print_buffer_421)
{
	int iterator;

	// Check if the Ring Buffer that is the Circular Buffer is already initialized.
	if(ringBuffer == NULL)
	{
		// Return -1 as the function has failed.
		return -1;
	}
	// Initialize the variable "iterator".
	iterator = 0;
	// Traverse through the buffer.
	while(iterator < SIZE_OF_BUFFER)
	{
		// Print the node data.
		printk("%d\n", ringBuffer->read->data);
		// Change temp to point to the next node of temp.
		ringBuffer->read = ringBuffer->read->next;
		// Increment the iterator.
		iterator++;
	}
	return 0;
}

// ******************************************************************************************************************************************
// The System Macro "SYSCALL_DEFINE0(delete_buffer_421)" is used to delete the complete buffer and not the single node. In other words, the *
// System Macro "SYSCALL_DEFINE0(delete_buffer_421)" deletes the buffer if it exists. Moreover, in terms of kernel space and using the      *
// Function kfree(), the System Macro "SYSCALL_DEFINE0(delete_buffer_421)" frees any memory in the kernel space that is allocated in the    *
// System Macro "SYSCALL_DEFINE0(init_buffer_421)". In addition, in terms of the buffer, if it is successful, then the System               *
// Macro "SYSCALL_DEFINE0(delete_buffer_421)" returns 0. However, if it fails, then the System Macro "SYSCALL_DEFINE0(delete_buffer_421)"   *
// returns -1.                                                                                                                              *
// ******************************************************************************************************************************************
SYSCALL_DEFINE0(delete_buffer_421)
{
	struct node_421* temp_two_node_421;

	// Check if the Ring Buffer that is the Circular Buffer is already initialized.
	if(ringBuffer == NULL)
	{
		// Return -1 as the function has failed.
		return -1;
	}

	// Point the temp node that is the Temporary Variable "temp_two_node_421" to the Head Node *write.
	temp_two_node_421 = ringBuffer->write;

	// Traverse throughout the Buffer with the purpose of checking if the Head Node *write is not pointing to itself to ensure
	// that the Head Node *write is not a single node in the Circular Linked List.
	while(ringBuffer->write->next != ringBuffer->write)
	{
		// Assign the "next" node of the Head Node *write to the temp node that is the Temporary Variable "temp_two_node_421". As a
		// result, the temp node that is the Temporary Variable "temp_two_node_421" will point to the "next" node of the
		// Head Node *write.
		temp_two_node_421 = ringBuffer->write->next;

		// The Head Node *write next will be assigned with the address in the current temp node that is the
		// Temporary Variable "temp_two_node_421" "next". As a result, this will break the link between the
		// Head Node *write and the temp node that is the Temporary Variable "temp_two_node_421".
		ringBuffer->write->next = temp_two_node_421->next;

		// Free the memory of the temp node that is the Temporary Variable "temp_two_node_421".
		kfree(temp_two_node_421);

		// Empty the temp node that is the Temporary Variable "temp_two_node_421".
		temp_two_node_421 = NULL;
	}
	// Once it is a single node, it will come out of the while loop. Therefore, free the memory of the Head Node *write.
	kfree(ringBuffer->write);

	// Once all of the memory is inside the variable "ringBuffer", free the variable "ringBuffer" itself.
	kfree(ringBuffer);

	// Set the variable "ringBuffer" to NULL so that it no longer points to the freed memory.
	ringBuffer = NULL;
	return 0;
}


