// Project 3 Part 2 Webb Telescope and the Bounded Buffer Using Semaphores: Semaphores in Kernel Space
#include <linux/kernel.h>
#include <linux/syscalls.h>
#include <linux/uaccess.h>
#include "buffer_sem.h"

static bb_buffer_421_t *buffer;

// Use Semaphore Structures to keep track of the access to the buffer.
DEFINE_SEMAPHORE(mutex);
DEFINE_SEMAPHORE(fill_count);
DEFINE_SEMAPHORE(empty_count);

// *******************************************************************************************************************************************
// The System Macro "SYCALL_DEFINE0(init_buffer_421)" initializes a new Circular Buffer, in other words, it initializes a new Ring Buffer, in *
// kernel memory for each Node. The System Macro "SYSCALL_DEFINE0(init_buffer_421)" does not reinitialize the buffer if it already exists. In *
// addition, the System Macro "SYSCALL_DEFINE0(init_buffer_421)" returns 0 on success and returns -1 on failure.                              *
// *******************************************************************************************************************************************
SYSCALL_DEFINE0(init_buffer_sem_421)
{
	struct bb_node_421 *temp_node_421;
	int i;
	// Check to see if the buffer is already initialized.
	if(buffer != NULL)
	{
		// Return -1 as the function has failed.
		return -1;
	}

	// Initialize the buffer to hold the Node List.
	buffer = (bb_buffer_421_t *)kmalloc(sizeof(bb_buffer_421_t), GFP_KERNEL);
	buffer->length = 0;

	// Initialize the temp node that is the Temporary Variable "temp_node_421".
	temp_node_421 = NULL;

	// Create a for loop() in order to iterate "SIZE_OF_BUFFER" times because the "SIZE_OF_BUFFER" is defined
	// in the "buffer.h" Header File. In addition, the "SIZE_OF_BUFFER" is initially defined as 20.
	for(i = 0; i < SIZE_OF_BUFFER; i++)
	{
		bb_node_421_t *pointerOne;
		// Create a Node Object.
		pointerOne = (bb_node_421_t *)kmalloc(sizeof(bb_node_421_t), GFP_KERNEL);

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

	// If Initialization is a success, return 0. In the case of failure for any reason, return -1.
	// Initialize the Semaphores.
	fill_count.count = 0;
	empty_count.count = SIZE_OF_BUFFER;
	return 0;
}

// **********************************************************************************************************************************************
// First, the System Macro "SYSCALL_DEFINE1(enqueue_buffer_421, char *, data)" copies 1024 Bytes from the "data" into the "write" node's data   *
// variable. Second, the System Macro "SYSCALL_DEFINE1(enqueue_buffer_421, char *, data)" correctly updates the buffer's "length" and Tail Node *
// Pointer *write. The System Macro "SYSCALL_DEFINE1(enqueue_buffer_421, char *,data)" cannot insert "data" into a buffer that is not           *
// initialized. In addition, the System Macro "SYSCALL_DEFINE1(enqueue_buffer_421, char *, data)" cannot insert "data" into a full buffer and   *
// and when this happens, the caller has to be blocked as a result of using a Semaphore. Finally, when it comes to success and failure, the     *
// System Macro "SYSCALL_DEFINE(enqueue_buffer_421, char *, data)" returns 0 on success and returns -1 on failure.                              *
// **********************************************************************************************************************************************
SYSCALL_DEFINE1(enqueue_buffer_sem_421, char *, data)
{
	int success;
	// Check if the buffer is already initialized.
	if(buffer == NULL)
	{
		// Return -1 as the function has failed.
		return -1;
	}

	// Check if the buffer is already a full block.
	down(&empty_count);

	down(&mutex);

	// Move the "data" into the Current Head Node Pointer *write position in the buffer.
	success = copy_from_user(buffer->write->data, data, sizeof(char)*DATA_LENGTH);

	if(success != 0)
	{
		printk(KERN_ERR "Sorry! Could not copy all of the user buffer: %d bytes not copied\n", success);
	}

	// Increment the number of items in the buffer.
	buffer->length++;

	// Print Out the Information to the kernel log.
	printk(KERN_INFO ":: Enqueueing element into buffer. ::\n");
	printk(KERN_INFO "%s\n", data);
	printk(KERN_INFO "%d items in buffer.\n", buffer->length);

	// In order to print out, that is display, the number of items in the buffer, increment the variable "fill_count".
	up(&fill_count);

	// Print Out the Semaphore Information.
	printk(KERN_INFO "struct semaphore mutex = %d\n", mutex.count);
	printk(KERN_INFO "struct semaphore fill_count = %d\n", fill_count.count);
	printk(KERN_INFO "struct semaphore empty_count = %d\n", empty_count.count);

	// Move the Head Node Pointer *write to the "next" location in the buffer.
	buffer->write = buffer->write->next;

	// Increment the Mutex Count in order to release the Mutex Count and allow other Functions or Threads to use the Semaphore.
	up(&mutex);

	// Return 0 on success. In the case of failure, return -1.
	return 0;
}

// *******************************************************************************************************************************************
// First, the System Macro "SYSCALL_DEFINE1(dequeue_buffer_421, char *, data)" copies 1024 Bytes from the Head Node *read into the provided   *
// buffer data. Second, the System Macro "SYSCALL_DEFINE1(dequeue_buffer_421, char *, data)" correctly updates the buffer's "length" and      *
// Head Node Pointer *read. The System Macro "SYSCALL_DEFINE1(dequeue_buffer_421, char *, data)" cannot dequeue a buffer that is not          *
// initialized. In addition, the System Macro "SYSCALL_DEFINE1(dequeue_buffer_421, char *, data)" cannot dequeue and as a result of this, the *
// length has to equal to 0. Furthermore, in the System Macro "SYSCALL_DEFINE1(dequeue_buffer_421, char *, data)", in order to make sure the  *
// System Macro "SYSCALL_DEFINE1(dequeue, char *, data)" cannot dequeue an empty buffer, the caller has to be blocked as a result of          *
// using a Semaphore. Finally, the System Macro "SYSCALL_DEFINE1(dequeue_buffer_421, char *, data)" returns 0 on success and returns -1 on    *
// failure.                                                                                                                                   *
// *******************************************************************************************************************************************
SYSCALL_DEFINE1(dequeue_buffer_sem_421, char *, data)
{
	int success;
	// Check if the buffer is already initialized.
	if(buffer == NULL)
	{
		// Return -1 as the function has failed.
		return -1;
	}

	// Check if the buffer is already full.
	down(&fill_count);

	// Lock the Mutex Semaphore so that two threads do not try to access the Ring Buffer simultaneously.
	down(&mutex);

	// If the buffer is not empty, then copy the buffer data to the output variable.
	success = copy_to_user(data, buffer->read->data, sizeof(char)*DATA_LENGTH);

	if(success != 0)
	{
		printk(KERN_ERR "Sorry! Could not copy all of the user buffer: %d bytes not copied\n", success);
	}
	// Decrement the "length" of the buffer.
	buffer->length--;

	// Print Out the Information to the kernel log.
	printk(KERN_INFO ":: Dequeueing element from buffer. ::\n");
	printk(KERN_INFO "%s\n", data);
	printk(KERN_INFO "%d items in the buffer.\n", buffer->length);

	// Increment the variable "empty_count".
	up(&empty_count);

	// Print Out the Semaphore Information.
	printk(KERN_INFO "struct semaphore mutex = %d\n", mutex.count);
	printk(KERN_INFO "struct semaphore fill_count = %d\n", fill_count.count);
	printk(KERN_INFO "struct semaphore empty_count = %d\n", empty_count.count);

	// Move the Tail Node Pointer *read to the "next" space in the buffer.
	buffer->read = buffer->read->next;

	// Increment the Mutex Count in order to release the Mutex Count and allow other Functions or Threads to use the Semaphore.
	up(&mutex);

	// Return 0 on success. In the case of failure, return -1.
	return 0;
}

// ****************************************************************************************************************************************
// The System Macro "SYSCALL_DEFINE0(delete_buffer_421)" deletes the buffer if it exists. In addition, in terms of kernel-space and using *
// the Function kfree(), the System Macro "SYSCALL_DEFINE0(delete_buffer_421)" frees memory in kernel-space that is allocated in the      *
// in the "SYSCALL_DEFINE0(init_buffer_421)" System Macro. Furthermore, in terms of the buffer, if it is successful, then the System      *
// Macro "SYSCALL_DEFINE0(delete_buffer_421)" returns 0. However, if it fails, then the System Macro "SYSCALL_DEFINE0(delete_buffer_421)" *
// returns -1.                                                                                                                            *
// ****************************************************************************************************************************************
SYSCALL_DEFINE0(delete_buffer_sem_421)
{
	bb_node_421_t *temp_two_node_421;
	down(&mutex);
	// Check if the buffer is already initialized.
	if(buffer == NULL)
	{
		// Return -1 as the function has failed.
		return -1;
	}

	// Point the temp node that is the Temporary Variable "temp_two_node_421" to the Head Node *write.
	temp_two_node_421 = buffer->write;

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

		// Free the memory of the temp node "temp_two_node_421".
		kfree(temp_two_node_421);

		// Empty the temp node that is the Temporary Variable "temp_two_node_421".
		temp_two_node_421 = NULL;
	}
	// Free the memory of the Head Node *write.
	kfree(buffer->write);

	// Once all of the memory is inside the variable "buffer", free the variable "buffer" itself.
	kfree(buffer);

	// Set the variable "buffer" to NULL so that it no longer points to the freed memory.
	buffer = NULL;

	up(&mutex);

	return 0;
}
