#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define WAIT "Wait"//就绪状态 
#define RUN "Run"//运行状态 
#define FINISH "Finish"//完成状态 
#define true 1
int JOBNUMBER; //设置进程测试数为5   

typedef struct PCB{	
	char jobName[10];//作业名 
	int arriveTime;//到达时间 
	int runTime;//需要运行时间 
	int startTime;//开始时间 
	int endTime;//完成时间 
	int turnoverTime;//周转时间 
	float useWeightTurnoverTime;//带权周转时间
	char processStatus[10];//进程状态 	
};
static int currentTime = 0;//当前时间 
static int finishNumber = 0;//进程完成数量 
char JobArray[10][10];//存放数组名信息的二元数组 
float priority[10];//存放进程优先级的一元数组 
 
//创建PCB
void createJCB(struct PCB* pcb){	
	int i,num; 
	printf("\n Please input the number of processes?"); 
	scanf("%d",&num); 
	JOBNUMBER = num;
 	for(i = 0; i < num; i++){
 		printf("\n Process No.%d:\n",i); 
 		printf("\n Input process name:"); 
	 	scanf("%s", &pcb[i].jobName);//作业号 
	 	printf("\n Input the priority number of the process:"); 
	 	scanf("%d", &pcb[i].arriveTime);//到达时间 
	 	printf("\n Input the running time of the process:"); 
	 	scanf("%d", &pcb[i].runTime);//需要运行时间 
	 	printf("\n"); 
	 	pcb[i].startTime = 0;
	 	pcb[i].endTime = 0;
	 	pcb[i].turnoverTime = 0;
	 	pcb[i].useWeightTurnoverTime = 0.0;
	 	strcpy(pcb[i].processStatus, WAIT);
	 	printf("%s\t%d\t%d\n",pcb[i].jobName, pcb[i].arriveTime,pcb[i].runTime);
	}
	printf("---------------------------------------------\n");
 }
 
//打印用途
void printJob(struct PCB* pcb){
	int i;
	printf("当前时间为%d\n", currentTime);
	printf("作业号 到达时间 需要运行时间 开始时间 完成时间 周转时间 带权周转时间 进程状态\n");
	for(i = 0; i < JOBNUMBER; i++){	
		if(strcmp(pcb[i].processStatus, FINISH) == 0)//如果进程为finish状态，这样输出 
			printf("%s\t%d\t%4d\t\t%d\t%d\t  %d\t  %.2f\t  %s\n", pcb[i].jobName, pcb[i].arriveTime, pcb[i].runTime, pcb[i].startTime, pcb[i].endTime, pcb[i].turnoverTime, pcb[i].useWeightTurnoverTime, pcb[i].processStatus);	
		else if(strcmp(pcb[i].processStatus, RUN) == 0)//如果进程为run状态，这样输出 
			printf("%s\t%d\t%4d\t\t%d\t运行中\t  none\t  none    %s\n", pcb[i].jobName, pcb[i].arriveTime, pcb[i].runTime, pcb[i].startTime, pcb[i].processStatus);	
		else //如果进程为wait状态，这样输出
			printf("%s\t%d\t%4d\t\t未运行\tnone\t  none\t  none    %s\n", pcb[i].jobName, pcb[i].arriveTime, pcb[i].runTime, pcb[i].processStatus);
	}
	printf("---------------------------------------------\n");
}
 
//计算平均带权周转时间 
float weightTurnoverTimeCount(struct PCB* pcb){
	int i;
	float sum = 0.0;
	for(i = 0; i < JOBNUMBER; i++)
		sum += pcb[i].useWeightTurnoverTime;
	return sum / JOBNUMBER;
}
 
//计算平均周转时间 
float turnOverTimeCount(struct PCB* pcb){
	int i;
	float sum = 0.0;
	for(i = 0; i < JOBNUMBER; i++)
		sum += pcb[i].turnoverTime;
	return sum / JOBNUMBER;
}
 
//比较各个进程之间的到达时间,按升序排列 
void compare(struct PCB* pcb){
	int i,j;
	for(i = 0; i < JOBNUMBER; i++){
		int min = pcb[i].arriveTime, minIndex = i;
		for(j = i + 1; j < JOBNUMBER; j++){
			if(pcb[j].arriveTime < min){
				min = pcb[j].arriveTime;
				minIndex = j;		
			}	
		}
		struct PCB temp = pcb[i];
		pcb[i] = pcb[minIndex];
		pcb[minIndex] = temp;
	}	
}
 
//打印进程调度顺序，平均周转时间及平均带权周转时间 
void printInfo(struct PCB* pcb){
	int i;
	printf("1、进程调度顺序为：%s",JobArray[0]);
	for(i=1;i<JOBNUMBER;i++)
	{
		printf("-> %s",JobArray[i]);
	}
	printf("\n");
	printf("2、平均周转时间为：%.2f\n",turnOverTimeCount(pcb));
	printf("3、平均带权周转时间为：%.2f\n", weightTurnoverTimeCount(pcb));
}
 
//算法循环遍历部分 
void loop(struct PCB* pcb, int i){
	pcb[i].startTime = currentTime;
	pcb[i].endTime = pcb[i].startTime + pcb[i].runTime;
	pcb[i].turnoverTime = pcb[i].endTime - pcb[i].arriveTime;
	pcb[i].useWeightTurnoverTime = pcb[i].turnoverTime * 1.0 / pcb[i].runTime;
	strcpy(pcb[i].processStatus, RUN);
	while(true){
		if(currentTime == pcb[i].endTime){	
			strcpy(pcb[i].processStatus, FINISH);
			finishNumber++;
			if(finishNumber == JOBNUMBER)
				printJob(pcb);
			currentTime--;
			break;
		}
		else{
			printJob(pcb);
			currentTime++;	
		}	
	}
} 

//高响应比优先调度算法 
void highestResponseRatioNext(struct PCB* pcb){
	createJCB(pcb);
	compare(pcb);
	int i = 0, j = 0; 
	for(; finishNumber != JOBNUMBER; currentTime++){
		float maxPriority = 0.0;
		int indexPriority = 0;
		if(currentTime < pcb[0].arriveTime)//当前时间小于第一个节点到来时间时，直接打印 
			printJob(pcb);
		else{
			for(i = 0; i < JOBNUMBER; i++){
				if(strcmp(pcb[i].processStatus, FINISH) != 0){
					int waitTime = currentTime - pcb[i].arriveTime;
				 	priority[i] = (waitTime + pcb[i].runTime) * 1.0 / pcb[i].runTime;
				 	if(priority[i] > maxPriority){
			 			maxPriority = priority[i];
			 			indexPriority = i;
			 		}
				}			 	
			}
			strcpy(JobArray[j++], pcb[indexPriority].jobName);
			loop(pcb, indexPriority);
		}
	}
	printInfo(pcb);//打印进程调度顺序，平均周转时间及平均带权周转时间 
	currentTime = 0;//当前时间置位
	finishNumber = 0;//完成进程数量置位 
}
 
//菜单函数
void menu(struct PCB* pcb){
	int input; 
	while(true){
		printf("----------------------------------------------\n");
		printf("|        1、响应比高者优先调度算法           |\n");
		printf("|        0、退出                             |\n");
		printf("----------------------------------------------\n");
		printf("请输入序号以继续程序：");
		scanf("%d", &input);
		switch(input){
			case 1:highestResponseRatioNext(pcb);
				break;
			case 0:
				exit(0);
			default:printf("输入有误，请重新输入!!!\n");
				break; 
		}	
	}
} 
 
//主函数 
int main(){
	struct PCB pcb[JOBNUMBER];
	menu(pcb);
    system("pause");
	return 0;
}

