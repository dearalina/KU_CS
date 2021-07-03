#include<linux/syscalls.h>
#include<linux/kernel.h>
#include<linux/linkage.h>

#define MAXSIZE 500

int queue[MAXSIZE];
int front = 0;
int rear = 0;
int i, res = 0;

SYSCALL_DEFINE1(oslab_enqueue, int, a){
	
	// Report error message when queue is full
	if(rear >= MAXSIZE - 1){
		printk(KERN_INFO "[Error] - QUEUE IS FULL --------------\n");
		return -2;	
	}
	// Traverse the queue to check if value 'a' existed; If existed, not insert
	for(i = front; i < rear; i++){
		if(a == queue[i]){
		printk(KERN_INFO "[Error] - EXISTED VALUE --------------\n");
		return a;
		}	
	}
	
	// Insert the value into the queue(array)
	queue[rear] = a;
	rear++;

	printk(KERN_INFO "[System call] oslab_enqueue(); -------\n");
	printk("Queue Front ------------------\n");
	for(i = front; i < rear; i++){
		printk("%d\n", queue[i]);	
	}
	printk("Queue Rear -------------------\n");
	
	return a;
}

SYSCALL_DEFINE0(oslab_dequeue){
	
	// Report error message when queue is empty; cannot dequeue;
	if(rear == front){
		printk(KERN_INFO "[Error] - EMPTY QUEUE --------------\n");
		return -2;	
	}
	// Get the value of the element to be removed
	res = queue[front];
	
	// Fill the removed element by moving all the values forward
	for(i = front; i < rear - 1; i++){
		queue[i] = queue[i+1];	
	}
	rear--;
	printk(KERN_INFO "[System call] oslab_dequeue(); -------\n");
	printk("Queue Front ------------------\n");
	for(i = front; i < rear; i++){
		printk("%d\n", queue[i]);	
	}
	printk("Queue Rear -------------------\n");
	
	return res;
}
