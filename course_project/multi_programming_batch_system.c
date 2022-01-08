# include "head.h"

void receive_jobs(job *jobs)
{	
    int n; //n个作业
    char path[80];
    char filename[10] = "\\data.txt";
    
    getcwd(path, sizeof(path));//获取当前目录 
    strcat(path,filename);//定位数据文件(应在与exe相同文件目录下) 

	FILE *fw=fopen(path,"r");
	int i,j,a[5][5];
	for(i=0;i<5;i++)
		{
		for(j=0;j<5;j++)
			{
				fscanf(fw,"%d",&a[i][j]);//读取文件中的数据，遇到空格和换行停止读。
			}
		jobs[i].name = a[i][0];
		jobs[i].arrivalTime = a[i][1];
		jobs[i].runTime = a[i][2];
		jobs[i].memorySize = a[i][3];
		jobs[i].tapesQuantity = a[i][4];
		jobs[i].status = 0;
		}
	fclose(fw);
}


//初始化内存空间 
List init() 
{            
	List list;
	list.node = (datatype*)malloc(sizeof(datatype));
	list.node->base = 0;
	list.node->id = -1;                     
	list.node->size = memory;
	list.node->status = 0;
	list.front = list.next = NULL;
	return list;
}

//接收需要分配内存的作业 
datatype* input(job* jobs, int i) 
{         
	datatype* item = (datatype*)malloc(sizeof(datatype));
	item->id = i;
	item->size = jobs[i].memorySize;
	item->status = 0;
	return item;
}

//打印内存分配情况 
void Momery_state(List* list, job* jobs) 
{
	List* temp = list;
	while (temp)
	{	
		//if (temp->node->size != 0)
		{
			if (temp->node->status == 0 && temp->node->id == -1 ) 
			{
				printf("\n**\tpartition ID：FREE\n");
				printf("**\taddress starting position：%d\n", temp->node->base);
				printf("**\tsize of Memory：%dK\n", temp->node->size);
				printf("**\tpartition status：free\n");
			}
			else
			{
				printf("\n**\tpartition ID：%d\n**\taddress starting position：%d\n", temp->node->id, temp->node->base);
				printf("**\tsize of Memory：%dK\n", temp->node->size);
				printf("**\tpartition status：Allocated\n");
				printf("**\ttapes occupancy:%d\n", jobs[temp->node->id].tapesQuantity);
			}
		}
		temp = temp->next;
	}
}

//内存分配
int memory_allocate(List* list, job* jobs, int i) 
{
	datatype* item = input(jobs, i);
	List* temp = list;                      

	while (temp)
	{

		if (temp->node->status == 0 && temp->node->size > item->size) {       
			List* front = temp->front;                                          
			List* next = temp->next;                                          
			int base = temp->node->base;                                      

			datatype* new_node = (datatype*)malloc(sizeof(datatype));          
			new_node->id = -1;                                                 
			new_node->size = temp->node->size - item->size;         

			temp->node = item;                                  
			temp->node->status = 1;

			new_node->status = 0;
			new_node->base = base + temp->node->size;             


			List* temp_next = (List*)malloc(sizeof(List));           
			temp_next->node = new_node;                             
			temp_next->front = temp_next->next = NULL;

			if (front == NULL && next == NULL) {                      
				temp->node->base = 0;                               
				temp->next = temp_next;
				temp_next->front = temp;
			}
			if (front == NULL && next != NULL) {                 
				temp->node->base = 0;
				temp->node->status = 1;
				temp_next->next = temp->next;
				temp->next = temp_next;
			}
			if (front != NULL) {                      //表明不是第一次分配节点，此时需要在中间插入下一个节点
				temp->node->base = temp->front->node->base + temp->front->node->size;        
				temp_next->next = temp->next;                                       
				temp_next->front = temp;                               
				temp->next = temp_next;                             //最后让所申请的分区节点的下一个节点指向刚刚建立的临时节点
			}
			return 1;
		}
		else if (temp->node->status == 0 && temp->node->size == item->size)
		{
			item->base = temp->front->node->base + temp->front->node->size;               
			item->status = 1;                                           //表示已经分配
			temp->node = item;

			return 1;
		}
		else {
			temp = temp->next;
			continue;
		}
		temp = temp->next;
	}
	return 0;
}

//内存回收 
int memory_recycle(List* list, int number) 
{
	List* temp = list;                      //申请一个链表节点 指向list 的头节点
	while (temp)
	{
		if (temp->node->id == number)            //首先找到 节点id = number 的节点，然后分四种情况讨论 
		{
			// 一、 要回收的是第一个结点
			if (temp->front == NULL) {
				temp->node->status = 0;
				temp->node->id = -1;
				if (temp->next == NULL) {
					temp->node->size = temp->node->size + temp->next->node->size;
					temp->next = temp->next;
					return 1;
				}

				if (temp->next->node->id == -1 && temp->next->node->status == 0) {
					List* next = temp->next;
					// 此时来判断 temp->next 是否是系统的最后一个结点
					// 此时只将当前节点 和下一个结点合并就可以了
					//即 首地址不变，   分区状态 和 分区id进行变化  
					temp->node->size = temp->node->size + next->node->size;
					temp->node->status = 0;
					temp->node->id = -1;
					temp->next = next->next;
					if (next->next == NULL) {
						free(next);
						return 1;
					}
					//如果不是最后一个结点的话就会多一个步骤
					// 让 next->next->front 指向上一个结点
					else
					{
						next->next->front = temp;
						free(next);
						return 1;
					}
				}

				return 1;
			}
			//二、 前后都没有空闲的分区
		  //最简单，   直接改变 分区的 id 和 分区的状态就可以了。
		  // 如果回收第一个分区的话 必须要先进行处理，如果不先进行处理 ，判断 temp->front->node->id != -1 会报一个段错误。因为temp-》front 此时指向的是null  
			if (temp->front->node->id != -1 && temp->front->node->status != 0 && temp->next->node->id != -1 && temp->next->node->status != 0) {
				temp->node->status = 0;
				temp->node->id = -1;
				return 1;
			}
			
			if (temp->front->node->id == -1 && temp->front->node->status == 0 && temp->next->node->id == -1 && temp->next->node->status == 0) {
				List* front = temp->front;
				List* next = temp->next;
				front->node->size = front->node->size + temp->node->size + next->node->size;
				front->next = next->next;
				if (next->next == NULL) {
					free(temp);
					return 1;
				}
				//如果不是最后一个结点的话就会多一个步骤
				// 让 next->next->front 指向上一个结点
				else
				{

					next->next->front = front;
					free(temp);
					return 1;
				}
				return 1;
			}
			// 前面的节点是空闲的
			//合并后的分区起始地址为前一个结点， 分区大小为前一个节点 与 当前节点之和。
			if (temp->front->node->id == -1 && temp->front->node->status == 0) {
				List* front = temp->front;
				front->next = temp->next;
				temp->next->front = front;
				front->node->size += temp->node->size;
				free(temp);
				return 1;
			}
			//五、后面的额节点是空闲的
			//合并后的分区首地址为当前节点 ，  分区大小为当前节点 与 当前节点的下一个结点大小之和。
			// 这个需要多一个步骤， 改变分区的 id 和  分区的状态。
			// 还要注意一点：  当要回收的空间是和  系统最后的空闲区相邻时 ， temp->next->next 指向的是null；

			if (temp->next->node->id == -1 && temp->next->node->status == 0) {
				List* next = temp->next;
				// 此时来判断 temp->next 是否是系统的最后一个结点
				// 此时只将当前节点 和下一个结点合并就可以了
				//即 首地址不变，   分区状态 和 分区id进行变化  
				temp->node->size = temp->node->size + next->node->size;
				temp->node->status = 0;
				temp->node->id = -1;
				temp->next = next->next;
				if (next->next == NULL) {
					free(next);
					return 1;
				}
				//如果不是最后一个结点的话就会多一个步骤
				// 让 next->next->front 指向上一个结点
				else
				{
					next->next->front = temp;
					free(next);
					return 1;
				}
			}
		}
		temp = temp->next;
	}
	return 0;
}

void job_scheduling(List* list, job* jobs, int i)
{
	int insert_state, recycle_state;
	
	//为这个作业分配资源 
	if((insert_state = memory_allocate(list, jobs, i)) == 1 && jobs[i].tapesQuantity <= tapes_quantity)
	{	
		tapes_quantity -= jobs[i].tapesQuantity;
		jobs[i].memoryState = 1;
		Momery_state(list, jobs);
		printf("\n**\trest tape drive: %d\n", tapes_quantity);
	}
	else jobs[i].memoryState = 0; 
}

//筛选出获得资源分配资格的作业 
int fcfs(job* jobs, int current_time)
{
	int i,j;
	for(i = 0; i<Job_number; i++)
	{	
		if(jobs[i].memoryState == 0 && current_time >= jobs[i].arrivalTime)
		{
			for(j = 0; j<Job_number; j++)
			{
				if(jobs[j].memoryState == 1 || jobs[j].memoryState == 2) continue;  //直接跳过与正在执行或者已完成的作业进行比对 
				else if(jobs[i].arrivalTime <= jobs[j].arrivalTime) continue;  //继续检索是否有到达时间比i作业更早的作业 
				else break;
			}
			if(jobs[i].memoryState == 0) return i;
			else continue;
		}
	}
	return -1;
}

int sjf(job* jobs, int current_time)
{
	int i,j;
	for(i = 0; i<Job_number; i++)
	{	
		if(jobs[i].memoryState == 0 && current_time >= jobs[i].arrivalTime)
		{
			for(j = 0; j<Job_number; j++)
			{
				if(jobs[j].memoryState == 1 || jobs[j].memoryState == 2) continue;
				else if(jobs[i].runTime <= jobs[j].runTime) continue;
				else break;
			}
			if(jobs[i].memoryState == 0) return i;
			else continue;
		}
	}
	return -1;
}

int check_process(job* jobs)
{	
	int i;
	for(i = 0; i < Job_number; i++)
	{
		if(jobs[i].status == 0 || jobs[i].status == 2)
		{
			return 0;
		}
	}
	return 1;
}

char *printf_time(int btime)
{
	char time_str[20];
	int hour = btime / 60;
	int minute = btime % 60;
	sprintf(time_str,"%d:%d\0",hour, minute);
	return time_str;
}

int process_scheduling(List* list, job* jobs, int current_time, char op1, char op2)
{	
	int i = 0;
	int num;
	int op = 0; 
	for(; i < Job_number;i++)
		if(jobs[i].memoryState == 1 && jobs[i].status == 0)
		{	
			jobs[i].serviceTime = current_time;
			jobs[i].finishTime = jobs[i].serviceTime + jobs[i].runTime;
			printf("\nstart job%d execution\n", i);
			jobs[i].status = 2; 
			while(op != 1)
			{	printf("\n*******\tsystem time：%s\t*******\n", printf_time(current_time + 600));
				if(jobs[i].finishTime != current_time)
				{	
					current_time += 5;
				}
				else 
				{	
					jobs[i].status = 1;
					memory_recycle(list, i);
					tapes_quantity += jobs[i].tapesQuantity;
					printf("\njob%d is finished\n", i);
					op = 1;
				}
			}
		}
	return current_time;
} 

void main()
{	
	char op1, op2;
	int insert_status;
	int i;
	float averageTime = 0.00;
	List list = init();
	//询问用户需要使用的算法 
	
	printf("*********************************\n");
	printf("*\tGDUT-国际教育学院\t*\n");
	printf("*\t 19计科李颂豪\t\t*\n");
	printf("*\t  3119009436\t\t*\n");
	printf("*********************************\n");
	
	
	
	printf("1:First come first service; 2:the shortest job first.\n"); 
	printf("please choose the algorithm that would be used in job scheduling：");
	op1 = getchar();
	getchar();
	
	printf("1:First come first service; 2:the shortest process first.\n"); 
	printf("please choose the algorithm that would be used in process scheduling：");
	op2 = getchar();
	getchar();
	
	//读取作业情况 
	receive_jobs(jobs);
	i = fcfs(jobs, current_time);
	
	job_scheduling(&list, jobs, i);
	//开始调度 
	do
	{	
		if(op1 == '1') i = fcfs(jobs, current_time);
		else i = sjf(jobs, current_time);
		if(i != -1) job_scheduling(&list, jobs, i); //如果在process中已经分配完了还怎么用这个i 
		current_time = process_scheduling(&list, jobs, current_time, op1, op2); 
	}while(check_process(jobs) == 0);
	
	//  
	for(i = 0; i < Job_number; i++)
	{
		jobs[i].priorityTime = jobs[i].finishTime - jobs[i].arrivalTime;
		averageTime += (float)jobs[i].priorityTime;
	}
	averageTime /= Job_number;

	printf("\naverage time cost = %.2f(min)", averageTime);
}
