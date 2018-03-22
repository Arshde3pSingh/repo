# repo
# Day 1: Basic Queue functions (Enqueue and Dequeue)
#include<stdio.h>
#include<stdlib.h>
int *add_queue(int *queue, int *last_pointer, int pid){
	if(*last_pointer==-1){
		queue=malloc(sizeof(int));
		*queue=pid;
		*last_pointer=*last_pointer+1;
	}
	else{
		queue=realloc(queue,sizeof(int)*(*last_pointer+2));
		*(queue+*last_pointer+1)=pid;
		*last_pointer=*last_pointer+1;
	}
	return queue;
}
int *del_queue(int *queue, int *last_pointer, int *pid){
	*pid=*(queue);
	for(int i=0;i<*last_pointer;i++){
		*(queue+i)=*(queue+i+1);
	}
	queue=realloc(queue,*last_pointer*sizeof(int));
	*last_pointer=*last_pointer-1;
	return queue;
}
void main(){
	int total_processes, i, last_pointer1=-1, process_eliminated;
	int *queue1, *queue2;
	printf("Enter the no. of Processes to be Scheduled : ");
	scanf("%d",&total_processes);
	char queue_processes[total_processes][10];
	int queue_priority[total_processes],queue_burst[total_processes],queue_arrival[total_processes];
	printf("Enter Details:\n");
//	printf("\nComplete the following Table with required scheduling information : \n(Note: Use Tab to switch between Columns)");
//	printf("\nProcess\tPrior\tBurst\tArrival\n\t-ty\tTime\tTime\n");
	/*while(i<total_processes){
		printf("For Process %d:\nProcess ID: ",i+1);
		scanf("%s",queue_processes[i]);
		printf("Priority: ");
		scanf("%d",&queue_priority[i]);
		printf("Burst Time: ");
		scanf("%d",&queue_burst[i]);
		printf("Arrival Time: ");
		scanf("%d",&queue_arrival[i]);
//		scanf("%s\t%d\t%d\t%d\n",queue_processes[i],&queue_priority[i],&queue_burst[i],&queue_arrival[i]);
		i++;
	}
	printf("Details Entered:");	
	printf("\nProcess\tPrior\tBurst\tArrival\n\t-ty\tTime\tTime\n");
	for(i=0;i<total_processes;i++){
		printf("%s\t",queue_processes[i]);
		printf("%d\t ",queue_priority[i]);
		printf("%d\t",queue_burst[i]);
		printf("%d\n",queue_arrival[i]);
	}*/
/*	queue1=add_queue(queue1, &last_pointer1, 8);
	queue1=add_queue(queue1, &last_pointer1, 2);
	for(i=0;i<=last_pointer1;i++){
		printf("%d\n",*(queue1+i));
	}
	queue1=del_queue(queue1,&last_pointer1, &process_eliminated);
	printf("Process: %d\n",process_eliminated);
	for(i=0;i<=last_pointer1;i++){
		printf("%d\n",*(queue1+i));
	}Test queue functions*/
}
