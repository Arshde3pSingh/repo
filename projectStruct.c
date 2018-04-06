#include<stdio.h>
#include<stdlib.h>
#include<string.h>
struct cpu{
    char proc_id[10];
    int execTime;
    int priority, burst, time_quantum;
};
struct process{
    char id[10];
	int priority,burst,arrival;
};
struct process *add_queue(struct process *queue, int *last_pointer, struct process proc){
	if(*last_pointer==-1){
		queue=malloc(sizeof(struct process));
		*queue=proc;
		*last_pointer=*last_pointer+1;
	}
	else{
		queue=realloc(queue,sizeof(struct process)*(*last_pointer+2));
		*(queue+*last_pointer+1)=proc;
		*last_pointer=*last_pointer+1;
	}
	return queue;
}
struct process *del_queue(struct process *queue, int *last_pointer, struct process *proc){
	*proc=*(queue);
	int i=0;
	for(i=0;i<*last_pointer;i++){
		*(queue+i)=*(queue+i+1);
	}
	queue=realloc(queue,*last_pointer*sizeof(struct process));
	*last_pointer=*last_pointer-1;
	return queue;
}
int search(struct process *list, char *proc_id, int total_processes){
    for(int i=0;i<total_processes;i++){
        if(strcmp(list[i].id,proc_id)==0){
            return i;
        }
    }
}
void quicksort(struct process * proc,int first,int last, int flag)
{
   int i, j, pivot;
   struct process temp;
   if(first<last)
   {
      pivot=first;
      i=first;
      j=last;
      if(flag==0){
        while(i<j)
        {
            while(proc[i].arrival<=proc[pivot].arrival&&i<last)
                i++;
            while(proc[j].arrival>proc[pivot].arrival)
                j--;
            if(i<j){
                temp=proc[i];
                proc[i]=proc[j];
                proc[j]=temp;
            }
        }
      }
      else{
        while(i<j)
        {
            while(proc[i].priority<=proc[pivot].priority&&i<last)
                i++;
            while(proc[j].priority>proc[pivot].priority)
                j--;
            if(i<j){
                temp=proc[i];
                proc[i]=proc[j];
                proc[j]=temp;
            }
        }
      }
      temp=proc[pivot];
      proc[pivot]=proc[j];
      proc[j]=temp;
      quicksort(proc,first,j-1,flag);
      quicksort(proc,j+1,last, flag);
   }
}
void main(){
    int total_processes, i=0, last_pointer1=-1, last_pointer2=-1;
    struct process *queue1, *queue2;
    printf("Enter the no. of Processes to be Scheduled : ");
	scanf("%d",&total_processes);
    struct process process_list[total_processes];
    printf("Enter Details:\n");
    while(i<total_processes){
		printf("For Process %d:\nProcess ID: ",i+1);
		scanf("%s",process_list[i].id);
		printf("Priority: ");
		scanf("%d",&process_list[i].priority);
		printf("Burst Time: ");
		scanf("%d",&process_list[i].burst);
		printf("Arrival Time: ");
		scanf("%d",&process_list[i].arrival);
		i++;
	}
    printf("Details Entered:");	
	printf("\nProcess\tPrior\tBurst\tArrival\n\t-ty\tTime\tTime\n");
	for(i=0;i<total_processes;i++){
		printf("%s\t",process_list[i].id);
		printf("%d\t ",process_list[i].priority);
		printf("%d\t",process_list[i].burst);
		printf("%d\n",process_list[i].arrival);
	}
	quicksort(process_list,0,total_processes-1, 0);
    printf("Details Entered (Sorted according to Arrival Time):");	
	printf("\nProcess\tPrior\tBurst\tArrival\n\t-ty\tTime\tTime\n");
	for(i=0;i<total_processes;i++){
		printf("%s\t",process_list[i].id);
		printf("%d\t ",process_list[i].priority);
		printf("%d\t",process_list[i].burst);
		printf("%d\n",process_list[i].arrival);
	}
    struct cpu *cpu_burst=malloc(sizeof(struct cpu));
    strcpy(cpu_burst[0].proc_id,process_list[0].id);
    cpu_burst[0].execTime=0;
    cpu_burst[0].priority=process_list[0].priority;
    cpu_burst[0].time_quantum=10000;
    cpu_burst[0].burst=process_list[0].burst;
    if(total_processes==1)
        cpu_burst[0].execTime=process_list[0].burst;
    i=0;
    for(int time=process_list[0].arrival, k=1, proc_in_cpu=0;(k>total_processes)||(last_pointer1>-1)||(last_pointer2>-1)||(cpu_burst[i].burst>0);time++){
        if(k!=total_processes){
            if(time==process_list[k].arrival){
                for(int x=k;x<total_processes;x++){
                    if(time>=process_list[x].arrival){
                        queue1=add_queue(queue1, &last_pointer1,process_list[x]);
                        k++;
                    }
                }
                k--;
                quicksort(queue1,0,last_pointer1,1);
                if(queue1[0].priority<cpu_burst[i].priority){
                    if(cpu_burst[i].burst>0&&cpu_burst[i].time_quantum>0){
                        proc_in_cpu=search(process_list, cpu_burst[i].proc_id,total_processes);
                        struct process process_eliminated;
                        queue1=del_queue(queue1,&last_pointer1, &process_eliminated);
                        queue2=add_queue(queue2, &last_pointer2,process_list[proc_in_cpu]);
                        cpu_burst=realloc(cpu_burst,sizeof(struct cpu)*(i+2));
                        i++;
                        strcpy(cpu_burst[i].proc_id,process_eliminated.id);
                        cpu_burst[i].execTime=0;
                        cpu_burst[i].priority=process_eliminated.priority;
                        cpu_burst[i].burst=process_eliminated.burst;
                        cpu_burst[i].time_quantum=10000;
                        cpu_burst[i].execTime++;
                        cpu_burst[i].burst--;
                        proc_in_cpu=search(process_list, cpu_burst[i].proc_id,total_processes);
                        process_list[proc_in_cpu].burst--;
                        cpu_burst[i].time_quantum--;
                        k++;
                    }
                    else{
                        cpu_burst=realloc(cpu_burst,sizeof(struct cpu)*(i+2));
                        i++;
                        struct process process_eliminated;
                        queue1=del_queue(queue1,&last_pointer1, &process_eliminated);
                        strcpy(cpu_burst[i].proc_id,process_eliminated.id);
                        cpu_burst[i].execTime=0;
                        cpu_burst[i].priority=process_eliminated.priority;
                        cpu_burst[i].burst=process_eliminated.burst;
                        cpu_burst[i].time_quantum=10000;
                        cpu_burst[i].execTime++;
                        cpu_burst[i].burst--;
                        proc_in_cpu=search(process_list, cpu_burst[i].proc_id,total_processes);
                        process_list[proc_in_cpu].burst--;
                        cpu_burst[i].time_quantum--;
                        k++;
                    }
                }
                else{
                    if(cpu_burst[i].burst>0&&cpu_burst[i].time_quantum>0){
                        cpu_burst[i].execTime++;
                        cpu_burst[i].burst--;
                        proc_in_cpu=search(process_list, cpu_burst[i].proc_id,total_processes);
                        process_list[proc_in_cpu].burst--;
                        cpu_burst[i].time_quantum--;
                        k++;
                    }
                    else{
                        cpu_burst=realloc(cpu_burst,sizeof(struct cpu)*(i+2));
                        i++;
                        struct process process_eliminated;
                        queue1=del_queue(queue1,&last_pointer1, &process_eliminated);
                        strcpy(cpu_burst[i].proc_id,process_eliminated.id);
                        cpu_burst[i].execTime=0;
                        cpu_burst[i].priority=process_eliminated.priority;
                        cpu_burst[i].burst=process_eliminated.burst;
                        cpu_burst[i].time_quantum=10000;
                        cpu_burst[i].execTime++;
                        cpu_burst[i].burst--;
                        proc_in_cpu=search(process_list, cpu_burst[i].proc_id,total_processes);
                        process_list[proc_in_cpu].burst--;
                        cpu_burst[i].time_quantum--;
                        k++;
                    }
                }
            }
            else{
                if(cpu_burst[i].burst>0&&cpu_burst[i].time_quantum>0){
                    cpu_burst[i].execTime++;
                    cpu_burst[i].burst--;
                    proc_in_cpu=search(process_list, cpu_burst[i].proc_id,total_processes);
                    process_list[proc_in_cpu].burst--;
                    cpu_burst[i].time_quantum--;
                }
                else{
                    if(strcmp(cpu_burst[i].proc_id,"Idle")!=0&&(last_pointer1==-1)&&(last_pointer2==-1)){
                        cpu_burst=realloc(cpu_burst,sizeof(struct cpu)*(i+2));
                        i++;
                        strcpy(cpu_burst[i].proc_id,"Idle");
                        cpu_burst[i].execTime=0;
                        cpu_burst[i].priority=10000;
                        cpu_burst[i].time_quantum=10000;
                        cpu_burst[i].execTime++;
                    }
                    else{
                        if((last_pointer1==-1)&&(last_pointer2==-1)&&strcmp(cpu_burst[i].proc_id,"Idle")==0)
                            cpu_burst[i].execTime++;
                        else{
                            if((last_pointer1!=-1)){
                                if(cpu_burst[i].burst>0){
                                    proc_in_cpu=search(process_list, cpu_burst[i].proc_id,total_processes);
                                    queue2=add_queue(queue2, &last_pointer2,process_list[proc_in_cpu]);
                                    cpu_burst[i].burst=0;
                                }
                                struct process process_eliminated;
                                queue1=del_queue(queue1,&last_pointer1, &process_eliminated);
                                cpu_burst=realloc(cpu_burst,sizeof(struct cpu)*(i+2));
                                i++;
                                strcpy(cpu_burst[i].proc_id,process_eliminated.id);
                                cpu_burst[i].execTime=0;
                                cpu_burst[i].priority=process_eliminated.priority;
                                cpu_burst[i].burst=process_eliminated.burst;
                                cpu_burst[i].time_quantum=10000;
                                cpu_burst[i].execTime++;
                                cpu_burst[i].burst--;
                                proc_in_cpu=search(process_list, cpu_burst[i].proc_id,total_processes);
                                process_list[proc_in_cpu].burst--;
                                cpu_burst[i].time_quantum--;
                            }
                            else{
                                if(last_pointer2!=-1){
                                    if(cpu_burst[i].burst>0){
                                        proc_in_cpu=search(process_list, cpu_burst[i].proc_id,total_processes);
                                        queue2=add_queue(queue2, &last_pointer2,process_list[proc_in_cpu]);
                                        cpu_burst[i].burst=0;
                                    }
                                    struct process process_eliminated;
                                    queue2=del_queue(queue2,&last_pointer2, &process_eliminated);
                                    cpu_burst=realloc(cpu_burst,sizeof(struct cpu)*(i+2));
                                    i++;
                                    strcpy(cpu_burst[i].proc_id,process_eliminated.id);
                                    cpu_burst[i].execTime=0;
                                    cpu_burst[i].priority=process_eliminated.priority;
                                    cpu_burst[i].burst=process_eliminated.burst;
                                    if(cpu_burst[i].burst<2){
                                        cpu_burst[i].time_quantum=cpu_burst[i].burst;
                                    }
                                    else
                                        cpu_burst[i].time_quantum=2;
                                    cpu_burst[i].execTime++;
                                    cpu_burst[i].burst--;
                                    proc_in_cpu=search(process_list, cpu_burst[i].proc_id,total_processes);
                                    process_list[proc_in_cpu].burst--;
                                    cpu_burst[i].time_quantum--;
                                }
                                else{
                                    if((cpu_burst[i].burst>0)&&(cpu_burst[i].time_quantum==0)){
                                        proc_in_cpu=search(process_list, cpu_burst[i].proc_id,total_processes);
                                        queue2=add_queue(queue2, &last_pointer2,process_list[proc_in_cpu]);
                                        cpu_burst[i].burst=0;
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
        else{
            if((cpu_burst[i].burst>0)&&(cpu_burst[i].time_quantum>0)){
                cpu_burst[i].execTime++;
                cpu_burst[i].burst--;
                proc_in_cpu=search(process_list, cpu_burst[i].proc_id,total_processes);
                process_list[proc_in_cpu].burst--;
                cpu_burst[i].time_quantum--;
            }
            else{
                if(last_pointer1!=-1){
                    if(cpu_burst[i].burst>0){
                        proc_in_cpu=search(process_list, cpu_burst[i].proc_id,total_processes);
                        queue2=add_queue(queue2, &last_pointer2,process_list[proc_in_cpu]);
                        cpu_burst[i].burst=0;
                    }
                    struct process process_eliminated;
                    queue1=del_queue(queue1,&last_pointer1, &process_eliminated);
                    cpu_burst=realloc(cpu_burst,sizeof(struct cpu)*(i+2));
                    i++;
                    strcpy(cpu_burst[i].proc_id,process_eliminated.id);
                    cpu_burst[i].execTime=0;
                    cpu_burst[i].priority=process_eliminated.priority;
                    cpu_burst[i].burst=process_eliminated.burst;
                    cpu_burst[i].time_quantum=1000;
                    cpu_burst[i].execTime++;
                    cpu_burst[i].burst--;
                    proc_in_cpu=search(process_list, cpu_burst[i].proc_id,total_processes);
                    process_list[proc_in_cpu].burst--;
                    cpu_burst[i].time_quantum--;
                }
                else{
                    if(last_pointer2!=-1){
                        if(cpu_burst[i].burst>0){
                            proc_in_cpu=search(process_list, cpu_burst[i].proc_id,total_processes);
                            queue2=add_queue(queue2, &last_pointer2,process_list[proc_in_cpu]);
                            cpu_burst[i].burst=0;
                        }
                        struct process process_eliminated;
                        queue2=del_queue(queue2,&last_pointer2, &process_eliminated);
                        printf("%d\n",process_eliminated.burst);
                        cpu_burst=realloc(cpu_burst,sizeof(struct cpu)*(i+2));
                        i++;
                        strcpy(cpu_burst[i].proc_id,process_eliminated.id);
                        cpu_burst[i].execTime=0;
                        cpu_burst[i].priority=process_eliminated.priority;
                        cpu_burst[i].burst=process_eliminated.burst;
                        if(cpu_burst[i].burst<2){
                            cpu_burst[i].time_quantum=cpu_burst[i].burst;
                        }
                        else
                            cpu_burst[i].time_quantum=2;
                        proc_in_cpu=search(process_list, cpu_burst[i].proc_id,total_processes);
                        cpu_burst[i].execTime++;
                        cpu_burst[i].burst--;
                        proc_in_cpu=search(process_list, cpu_burst[i].proc_id,total_processes);
                        process_list[proc_in_cpu].burst--;
                        cpu_burst[i].time_quantum--;
                    }
                    else{
                        if((cpu_burst[i].burst>0)&&(cpu_burst[i].time_quantum==0)){
                            proc_in_cpu=search(process_list, cpu_burst[i].proc_id,total_processes);
                            queue2=add_queue(queue2, &last_pointer2,process_list[proc_in_cpu]);
                            cpu_burst[i].burst=0;
                        }
                    }
                }
            }
        }
    }
    printf("\nCPU Utilization:\n");
	for(int k=0;k<=i;k++){
        if(strcmp(cpu_burst[k].proc_id,"Idle")!=0)
            printf("CPU:%s\t  %d\n",cpu_burst[k].proc_id,cpu_burst[k].execTime);
        else
            printf("CPU:%s  %d\n",cpu_burst[k].proc_id,cpu_burst[k].execTime);
	}
	int sum=process_list[0].arrival;
    if(sum!=0)
        printf("Idle:\t from 0 to %d\n",sum); 
	for(int k=0;k<=i;k++){
        int temp=sum;
        sum=sum+cpu_burst[k].execTime;
        printf("%s:\t from %d to %d\n",cpu_burst[k].proc_id,temp,sum);
    }
    for(i=0;i<=last_pointer1;i++){
        printf("QUEUE1:%s\n",queue1[i].id);
	}
	for(i=0;i<=last_pointer2;i++){
        printf("QUEUE2:%s \n",queue2[i].id);
	}
}
