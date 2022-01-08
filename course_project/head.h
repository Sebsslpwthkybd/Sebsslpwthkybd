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
    int name;      		//作业的名字
    int arrivalTime;    //作业到达系统时间
    int serviceTime;    //作业服务时间
    int runTime;        //作业周转时间
    int finishTime;     //作业结束时间
    float priorityTime;//带权周转时间
    int memorySize;  	//内存需要(K)
    int memoryState;	//内存分配情况 
	int tapesQuantity;  //磁带机需要 
	int status;		//记录作业是否完成 
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

