Name: Talha Hussain

# Project 3 Part 2 Webb Telescope Video and the Bounded Buffer Using Semaphores: Semaphore in User Space and Semaphore in Kernel Space.

## User Space

The general structure of the Circular Buffer did not change. However, there were some additions to allow for concurrency and access as a result
of using Semaphores. In the Function 'long init_buffer_421(void)' that is defined as part of the 'buffer_user_sem.c' File, as a result of
calling 'sem_init()' three times, I was able to set the Semaphores up for the appropriate styles of use by applying the syntax rules
of the POSIX Semaphore Library that would '#include <semaphore.h>'. The 'mutex' Semaphore was set up in a traditional way with 1 available
resource. In addition, the 'mutex' Semaphore was used to do the primary blocking on the enqueue and dequeue functions. The 'fill_count'
Semaphore, the 'empty_count' Semaphore, and the Constant Variable 'SIZE_OF_BUFFER' are all initialized to 0 for the purpose of functioning as 
safeguards from trying to enqueue or dequeue from the buffer when that operation is not possible. Finally, I added a 'sem_wait()' Function 
to the Function 'long delete_buffer_421(void)' to prevent it from being called so long as an enqueue or a dequeue operation was being carried
out. For the test file that is 'test_user_sem.c', I had to create two POSIX threads, in other words I had to make two pthreads, that included the
Producer Thread to allow for the production of the buffer and the Consumer Thread to allow for the consumption of the buffer. Furthermore, it was
fairly easy for me to create the Producer Thread and Consumer Thread along with implementing a randomized sleep Function called the 'usleep()'
Function that is already built in as part of the Header File '#include <unistd.h>' in order to have the Producer Thread and Consumer Thread rest
between cycles for a random amount of time between 0 milliseconds and 10 milliseconds. 

## Kernel Space
When it came to creating a buffer using Semaphores in Kernel Space, the main problem that I had to tackle was the fact that both the buffer
kernel files from the 'buffer' Sub-Directory Folder and the Producer-Consumer Semaphore Files from the 'prodcon_sem' Sub-Directory Folder as part
of my main Directory Folder 'project3-talhavi0499' defined the same 'init_buffer_421()' Function and 'delete_buffer_421()' Function as System
Calls. Therefore, I modified the Functions 'init_buffer_421()' and 'delete_buffer_421()' in the 'buffer_sem.c' File from the 'prodcon_sem'
Directory Folder to include the "_sem" Suffix to bring the Functions 'init_buffer_421()' and 'delete_buffer_421()' inline with the naming
of the System Call Definitions 'NR_init_buffer_sem_421' and 'NR_delete_buffer_sem_421' and to prevent naming collisions with the C Code for
creating the Circular Buffer in User Space and creating the Circular Buffer in Kernel Space from the Directory Folder 'buffer' for Part 1
of Project 3. In addition, while I was creating the C code to solve the Bounded Buffer Problem that is the Producer-Consumer Problem in Part 2
of Project 3 by using a Circular Buffer and Semaphores, I realized that implementing Semaphores in Kernel Space are a lot different than 
implementing Semaphores in User Space because instead of using the 'sem_post()' Function and 'sem_wait()' Function from the built-in Header File
that functions as the Preprocessor Directive 'include <semaphore.h>', I only had to use the 'up()' Function and 'down()' Function from the
built-in Header File 'include <linux/sempahore.h>' that is stated in the 'buffer_sem.h' Header File because I learned that I was working
with the direct memory structure of a Semaphore instead of an abstraction like in user space. This meant that things like the 'sem_getvalue()'
Function could be replaced with 'semaphore.count' and directly access the count value. Beyond that, there was little change to the
overall C Code from the 'buffer' Directory Folder for Part 1 of Project 3.

## Instructions
### Compiling
A 'Makefile' has been created to make it easier for Compiling the Semaphores along with the Circular Buffer from Part 1 of Project 3 in User
Space. Hence, in order to properly make and compile the Semaphores along with the Circular Buffer from Part 1 of Project 3, type the
command 'make buffer_user_sem' in the Directory Folder 'prodcon_sem' within the VirtualBox Debian Terminal. In short, simply use the
command 'make buffer_user_sem' to make the user space build.

In order to properly make and compile the kernel space test for the Semaphores and the Circular Buffer from Part of Project 3 in Kernel Space,
type the command 'make buffer_test_sem' in the Directory Folder 'prodcon_sem' within the VirtualBox Debian Terminal for the Kernel Space Test
Program. The 'Makefile' in the 'prodcon_sem' Directory Folder has a target 'make buffer_test_sem' for the Kernel Space Test Program.

### Running
To run the User Space Test File, first type the executable command './buffer_user_sem' in the VirtualBox Debian Terminal and then 
on your computer keyboard, press the "Enter" key.

To run the Kernel Space test file, first type the executable command './buffer_test_sem' in the VirtualBox Debian Terminal and then
on your computer keyboard, press the "Enter" key. 
