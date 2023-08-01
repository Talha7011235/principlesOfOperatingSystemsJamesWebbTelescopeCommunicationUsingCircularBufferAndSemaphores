obj-y += buffer_sem.o
buffer_user_sem: test_user_sem.c buffer_user_sem.o
	gcc -o buffer_user_sem test_user_sem.c buffer_user_sem.o -lpthread

buffer_user_sem.o: buffer_user_sem.c
	gcc -c buffer_user_sem.c

buffer_test_sem:
	gcc -o buffer_test_sem test_sem.c -lpthread
clean:
	-rm buffer_test_sem buffer_user_sem buffer_user_sem.o


