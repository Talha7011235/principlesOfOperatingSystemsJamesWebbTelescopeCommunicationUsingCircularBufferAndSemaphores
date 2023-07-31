# Makefile for Circular Buffer in User Space and Circular Buffer in Kernel Space
obj-y += buffer.o
buffer_user: test_user.c buffer_user.o
	gcc -o buffer_user test_user.c buffer_user.o

buffer_user.o: buffer_user.c
	gcc -c buffer_user.c

buffer_test: test.c buffer.h
	gcc -o buffer_test test.c

clean: 
	-rm buffer_user buffer_test buffer_user.o



