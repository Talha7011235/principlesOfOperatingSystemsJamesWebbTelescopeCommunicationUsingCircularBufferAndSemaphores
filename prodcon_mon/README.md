Name: Talha Hussain

# Project 3 Part 3 Webb Telescope Video and the Bounded Buffer Using Monitors: Use a Monitor instead of a Semaphore for Locking in User Space

## User Space
Implementing a Monitor on a Circular Buffer was both similar and different to implementing a Semaphore on the Circular Buffer that I created in
User Space and Kernel Space for Part 1 of Project 3. The reason is that a Monitor involved creating a pair of variables which act together
to lock a resource until the resource was able to perform its action. By using the 'pthread_mutex_lock()' Function and 'pthread_cond_wait()'
Function from the built-in pthread Header File 'include <pthread.h>' as part of the POSIX pthread Application Programming Interface API, I was
capable of ensuring only a singular processc can connect to and operate on the Circular Buffer at a time. Then, from the built-in pthread
Header File 'include<pthread.h>' that is part of the POSIX pthread Application Programming Interface API, I used the 'pthread_cond_broadcast()'
Function to signal to the waiting threads that the buffer has entered a state in which it can perform its action, either to produce to the
buffer or consume from the buffer. Furthermore, due to only changing the synchronization mechanism within the buffer, I was able to reuse the
test file 'test_user_sem.c' from Part 2 of Project 3.

## Instructions
### Compiling
A 'Makefile' has been created to make it easier for Compiling the Monitor on a Circular Buffer that uses a Mutex and Conditional
Variables. Hence, in order to properly make and compile the Monitor on a Circular Buffer that uses a Mutex and Conditional Variables,
type the command 'make buffer_mon' in the Directory Folder 'prodcon_mon' within the VirtualBox Debian Terminal. In short, simply
use the 'make buffer_mon' to make the user space build.

### Running
To run the User Space Test File, first type the executable command './buffer_mon' in the VirtualBox Debian Terminal and then 
on your computer keyboard, press the "Enter" key. 


