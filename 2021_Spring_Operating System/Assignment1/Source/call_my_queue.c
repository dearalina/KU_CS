#include<unistd.h>
#include<stdio.h>

// the same as the system call number defined in syscall.h
#define my_queue_enqueue 335 
#define my_queue_dequeue 336

int main(){
int a = 0;

a = syscall(my_queue_enqueue, 1); // invoke System Call number 335 and enqueue "1"
printf("Enqueue : ");
printf("%d\n", a);

a = syscall(my_queue_enqueue, 2); // invoke System Call number 335 and enqueue "2"
printf("Enqueue : ");
printf("%d\n", a);

a = syscall(my_queue_enqueue, 3); // invoke System Call number 335 and enqueue "3"
printf("Enqueue : ");
printf("%d\n", a);

a = syscall(my_queue_enqueue, 3); // test if duplicated value "3" can be enqueued
printf("Enqueue : ");
printf("%d\n", a);

a = syscall(my_queue_dequeue);   // invoke System Call number 336 and dequeue
printf("Dequeue : ");
printf("%d\n", a);

a = syscall(my_queue_dequeue);	// invoke System Call 336 number and dequeue
printf("Dequeue : ");
printf("%d\n", a);

a = syscall(my_queue_dequeue);	// invoke System Call 336 number and dequeue
printf("Dequeue : ");
printf("%d\n", a);

return 0;
}
