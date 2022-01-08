# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>

# define Job_number 5
# define Total_memory_size 100
# define Tapes_drives 4
# define Start_hour 10

int memory = Total_memory_size;
int tapes_quantity = Tapes_drives;
int current_time = 0;


typedef struct 
{
    int name;      		//��ҵ������
    int arrivalTime;    //��ҵ����ϵͳʱ��
    int serviceTime;    //��ҵ����ʱ��
    int runTime;        //��ҵ��תʱ��
    int finishTime;     //��ҵ����ʱ��
    float priorityTime;//��Ȩ��תʱ��
    int memorySize;  	//�ڴ���Ҫ(K)
    int memoryState;	//�ڴ������� 
	int tapesQuantity;  //�Ŵ�����Ҫ 
	int status;		//��¼��ҵ�Ƿ���� 
}job;
job jobs[5];

typedef struct item       
{
	int id;                 
	int base;              
	int size;               
	int status;             
}Item;
typedef Item datatype;

typedef struct list
{
	datatype* node;      
	struct list* front;
	struct list* next;
}List;

