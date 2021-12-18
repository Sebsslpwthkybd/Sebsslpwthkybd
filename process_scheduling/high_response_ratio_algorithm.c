#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define WAIT "Wait"//����״̬ 
#define RUN "Run"//����״̬ 
#define FINISH "Finish"//���״̬ 
#define true 1
int JOBNUMBER; //���ý��̲�����Ϊ5   

typedef struct PCB{	
	char jobName[10];//��ҵ�� 
	int arriveTime;//����ʱ�� 
	int runTime;//��Ҫ����ʱ�� 
	int startTime;//��ʼʱ�� 
	int endTime;//���ʱ�� 
	int turnoverTime;//��תʱ�� 
	float useWeightTurnoverTime;//��Ȩ��תʱ��
	char processStatus[10];//����״̬ 	
};
static int currentTime = 0;//��ǰʱ�� 
static int finishNumber = 0;//����������� 
char JobArray[10][10];//�����������Ϣ�Ķ�Ԫ���� 
float priority[10];//��Ž������ȼ���һԪ���� 
 
//����PCB
void createJCB(struct PCB* pcb){	
	int i,num; 
	printf("\n Please input the number of processes?"); 
	scanf("%d",&num); 
	JOBNUMBER = num;
 	for(i = 0; i < num; i++){
 		printf("\n Process No.%d:\n",i); 
 		printf("\n Input process name:"); 
	 	scanf("%s", &pcb[i].jobName);//��ҵ�� 
	 	printf("\n Input the priority number of the process:"); 
	 	scanf("%d", &pcb[i].arriveTime);//����ʱ�� 
	 	printf("\n Input the running time of the process:"); 
	 	scanf("%d", &pcb[i].runTime);//��Ҫ����ʱ�� 
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
 
//��ӡ��;
void printJob(struct PCB* pcb){
	int i;
	printf("��ǰʱ��Ϊ%d\n", currentTime);
	printf("��ҵ�� ����ʱ�� ��Ҫ����ʱ�� ��ʼʱ�� ���ʱ�� ��תʱ�� ��Ȩ��תʱ�� ����״̬\n");
	for(i = 0; i < JOBNUMBER; i++){	
		if(strcmp(pcb[i].processStatus, FINISH) == 0)//�������Ϊfinish״̬��������� 
			printf("%s\t%d\t%4d\t\t%d\t%d\t  %d\t  %.2f\t  %s\n", pcb[i].jobName, pcb[i].arriveTime, pcb[i].runTime, pcb[i].startTime, pcb[i].endTime, pcb[i].turnoverTime, pcb[i].useWeightTurnoverTime, pcb[i].processStatus);	
		else if(strcmp(pcb[i].processStatus, RUN) == 0)//�������Ϊrun״̬��������� 
			printf("%s\t%d\t%4d\t\t%d\t������\t  none\t  none    %s\n", pcb[i].jobName, pcb[i].arriveTime, pcb[i].runTime, pcb[i].startTime, pcb[i].processStatus);	
		else //�������Ϊwait״̬���������
			printf("%s\t%d\t%4d\t\tδ����\tnone\t  none\t  none    %s\n", pcb[i].jobName, pcb[i].arriveTime, pcb[i].runTime, pcb[i].processStatus);
	}
	printf("---------------------------------------------\n");
}
 
//����ƽ����Ȩ��תʱ�� 
float weightTurnoverTimeCount(struct PCB* pcb){
	int i;
	float sum = 0.0;
	for(i = 0; i < JOBNUMBER; i++)
		sum += pcb[i].useWeightTurnoverTime;
	return sum / JOBNUMBER;
}
 
//����ƽ����תʱ�� 
float turnOverTimeCount(struct PCB* pcb){
	int i;
	float sum = 0.0;
	for(i = 0; i < JOBNUMBER; i++)
		sum += pcb[i].turnoverTime;
	return sum / JOBNUMBER;
}
 
//�Ƚϸ�������֮��ĵ���ʱ��,���������� 
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
 
//��ӡ���̵���˳��ƽ����תʱ�估ƽ����Ȩ��תʱ�� 
void printInfo(struct PCB* pcb){
	int i;
	printf("1�����̵���˳��Ϊ��%s",JobArray[0]);
	for(i=1;i<JOBNUMBER;i++)
	{
		printf("-> %s",JobArray[i]);
	}
	printf("\n");
	printf("2��ƽ����תʱ��Ϊ��%.2f\n",turnOverTimeCount(pcb));
	printf("3��ƽ����Ȩ��תʱ��Ϊ��%.2f\n", weightTurnoverTimeCount(pcb));
}
 
//�㷨ѭ���������� 
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

//����Ӧ�����ȵ����㷨 
void highestResponseRatioNext(struct PCB* pcb){
	createJCB(pcb);
	compare(pcb);
	int i = 0, j = 0; 
	for(; finishNumber != JOBNUMBER; currentTime++){
		float maxPriority = 0.0;
		int indexPriority = 0;
		if(currentTime < pcb[0].arriveTime)//��ǰʱ��С�ڵ�һ���ڵ㵽��ʱ��ʱ��ֱ�Ӵ�ӡ 
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
	printInfo(pcb);//��ӡ���̵���˳��ƽ����תʱ�估ƽ����Ȩ��תʱ�� 
	currentTime = 0;//��ǰʱ����λ
	finishNumber = 0;//��ɽ���������λ 
}
 
//�˵�����
void menu(struct PCB* pcb){
	int input; 
	while(true){
		printf("----------------------------------------------\n");
		printf("|        1����Ӧ�ȸ������ȵ����㷨           |\n");
		printf("|        0���˳�                             |\n");
		printf("----------------------------------------------\n");
		printf("����������Լ�������");
		scanf("%d", &input);
		switch(input){
			case 1:highestResponseRatioNext(pcb);
				break;
			case 0:
				exit(0);
			default:printf("������������������!!!\n");
				break; 
		}	
	}
} 
 
//������ 
int main(){
	struct PCB pcb[JOBNUMBER];
	menu(pcb);
    system("pause");
	return 0;
}

