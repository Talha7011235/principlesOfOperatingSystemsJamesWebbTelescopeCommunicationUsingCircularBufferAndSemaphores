Name: Talha Hussain

# Project 3 Part 1 Creating Circular Buffer in User Space and Creating Circular Buffer in Kernel Space

## User Space
In terms of making an effort to successfully create a Circular Buffer in User Space, I began with using "malloc" in order to initialize the
Structure of the Ring Buffer, also known as a Circular Buffer, that is initialize the 'ring_buffer_421' struct and set the initial length 
of the 'ring_buffer_421' struct to 0. I then used a while() loop to build the node path and fill the path set of the buffer. After I finished 
creating the node path and filling the buffer's path set, I connected the last node in the buffer to the first node in order to create the
Ring Buffer that is the Circular Buffer and ensured the 'ringBuffer->read' and 'ringBuffer->write' Pointers, where *write is the Head Node Pointer
and *read is the Tail Node Pointer, were set to the beginning of the loop. The next step that I had to carry out while creating a Circular Buffer
in User Space was to verify that the Ring Buffer that is the Circular Buffer was created and its contents were not at capacity. Then, I began
searching for the 'next' available location of 'write'. As a result, when an available location was determined, I placed the new data 
into the 'ringBuffer->write' Pointer at that location. This ensured that the buffer would continue to circle the Linked List inside the
Ring Buffer that is the Circular Buffer. In contrast to initializing data and inserting data, printing data was not complicated because I simply
needed to print the data at the buffer location and then move the "ringBuffer->read" Pointer along the ring until it reached it's Initial
Postion. When it came to deleting the buffer, I created and followed a path that included moving around the loop and freeing allocated memory in
order to prevent memory leaks. Finally, once it is completed as a Single Node that then comes out of the loop, I used valgrind to free the buffer
itself which led to 0 memory leaks remaining.

## Kernel Space
In contrast to the operations that were used to create a Circular Buffer in User Space, the Kernel Space Operations used to create a Circular
Buffer were unique because those Kernel Space Operations required a different pattern of freeing, a different pattern of allocation, and the use
of the 'printk' Function instead of the 'printf' Function for displaying, printing out, the Output. Furthermore, the System Calls that are used
to create a Circular Buffer in Kernel Space are defined differently than there corresponding Functions that are applied to create a Circular
Buffer in User Space. For example, the Function 'long insert_buffer_421(int i)' that is one of the Functions needed to implement the Circular
Buffer in User Space becomes, in other words it changes to, the System Call 'SYSCALL_DEFINE1(insert_buffer_421, int, i)'. Therefore, I had to
use macro instructions in order to fulfill the requirements for creating every single System Call when it comes to implementing the
Circular Buffer in Kernel Space. Furthermore, I had to add to add definitions to the 'syscall.h' Header File from the 'include/linux/' directory
to successfully append each System Call Function Signature and the 'syscalls_64.tbl' from the 'arch/x86/entry/syscalls/' directory to allow every
single System Call that I implemented for the Circular Buffer in Kernel Space to be properly accessible.

## Instructions 
### Compiling
A 'Makefile' has been created to make it easier for Compiling the Circular Buffer  in User Space. Hence, in order to properly make and compile the
Circular Buffer in User Space, type the command 'make buffer_user' in the Directory Folder 'buffer' within the VirtualBox Debian Terminal. In
short, simply use the 'make buffer_user' to make the user space build.

In order to properly make and compile the kernel space test for the Circular Buffer in Kernel Space, type the command 'make buffer_test' in the
Directory Folder 'buffer' within the VirtualBox Debian Terminal for the Kernel Space Test Program. The 'Makefile' in the 'buffer' Directory
Folder has a target 'make buffer_test' for the Kernel Space Test Program. 

### Running
To run the User Space test file, first type the executable command './buffer_user' in the VirtualBox Debian Terminal and then on your computer 
keyboard, press the "Enter" key.

To run the Kernel Space test file, first type the executable command './buffer_test' in the VirtualBox Debian Terminal and then on your
computer keyboard, press the "Enter" key.

