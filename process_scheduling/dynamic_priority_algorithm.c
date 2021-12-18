#include <stdio.h> 
#include <stdlib.h> 
#define getpch(type) (type*)malloc(sizeof(type)) 
#define EMPTY 0 

struct pcb { /* Define PCB */ 
char name[10]; 
char state; 
int super; 
int ntime; 
int rtime; 
struct pcb* link; 
}*ready=EMPTY,*p; 
typedef struct pcb PCB;   

void sort() /* a function of process priority sorting */ 
{ 
PCB *first, *second; 
int insert=0; 
if((ready==EMPTY)||((p->super)>(ready->super))) /* a process with the highest priority is added to the front */ 
{ 
p->link=ready; 
ready=p; 
} 
else /* compare the priority of the processes and insert the process to the appropriate position */ 
{ 
first=ready; 
second=first->link; 
while(second!=EMPTY) 
{ 
if((p->super)>(second->super)) /* if the inserted process has a higher priority than the current process */ 
{ /* insert it to the front of the current process */ 
p->link=second; 
first->link=p; 
second=EMPTY; 
insert=1; 
} 
else /* the inserted process has the lowest priority, then inert it to the end */ 
{ 
first=first->link; 
second=second->link; 
} 
} 
if(insert==0) first->link=p; 
} 
}

void input() /* a function of initializing PCB */ 
{ 
int i,num; 
printf("\n Please input the number of processes?"); 
scanf("%d",&num); 
printf("%d",num);
for(i=0;i<num;i++) 
{ 
printf("\n Process No.%d:\n",i); 
p=getpch(PCB); 
printf("\n Input process name:"); 
scanf("%s",p->name); 
printf("\n Input the priority number of the process:"); 
scanf("%d",&p->super); 
printf("\n Input the running time of the process:"); 
scanf("%d",&p->ntime); 
printf("\n"); 
p->rtime=0;p->state='w'; 
p->link=EMPTY; 
sort(); /* call the function of sort */ 
} 
} 

int space() 
{ 
int l=0; PCB* pr=ready; 
while(pr!=EMPTY) 
{ 
l++; 
pr=pr->link; 
} 
return(l); 
}
 
void disp(PCB * pr) /* a function of displaying the information of the current process */ 
{ 
printf("\n qname \t state \t super \t ndtime \t runtime \n"); 
printf("|%s\t",pr->name); 
printf("|%c\t",pr->state); 
printf("|%d\t",pr->super); 
printf("|%d\t",pr->ntime); 
printf("|%d\t",pr->rtime); 
printf("\n"); 
} 

void check() /* a function of checking the status of the processes */ 
{ 
PCB* pr; 
printf("\n **** The running process is:%s",p->name); /* to show the running process */ 
disp(p); 
pr=ready; 
printf("\n **** The status of the ready queue is:\n"); /* to show the status of the ready queue*/ 
while(pr!=EMPTY) 
{ 
disp(pr); 
pr=pr->link; 
} 
} 

destroy() /* a function of process termination (after the process is finished, it will be terminated)*/ 
{ 
printf("\n Process [%s] is finished.\n",p->name); 
free(p); 
} 

void running() /* a function of process running (when the time slice is used up, set the process to be ready) */ 
{ 
(p->rtime)++; 
if(p->rtime==p->ntime) 
destroy(); /* call destroy function*/ 
else 
{ 
(p->super)--; //dynamic 
p->state='w'; 
sort(); /*call sort function*/ 
} 
}
 
void main() /*main function*/ 
{ 
int len,h=0; 
char ch; 
input(); 
len=space(); 
while((len!=0)&&(ready!=EMPTY)) 
{ 
ch=getchar(); 
h++; 
printf("\n The execute number:%d \n",h); 
p=ready; 
ready=p->link; 
p->link=EMPTY; 
p->state='R'; 
check(); 
running(); 
printf("\n Press any key to continue......"); 
ch=getchar(); 
} 
printf("\n\n The process is finished.\n"); 
ch=getchar(); 
} 
