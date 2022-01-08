# include "head.h"

void receive_jobs(job *jobs)
{	
    int n; //n����ҵ
    char path[80];
    char filename[10] = "\\data.txt";
    
    getcwd(path, sizeof(path));//��ȡ��ǰĿ¼ 
    strcat(path,filename);//��λ�����ļ�(Ӧ����exe��ͬ�ļ�Ŀ¼��) 

	FILE *fw=fopen(path,"r");
	int i,j,a[5][5];
	for(i=0;i<5;i++)
		{
		for(j=0;j<5;j++)
			{
				fscanf(fw,"%d",&a[i][j]);//��ȡ�ļ��е����ݣ������ո�ͻ���ֹͣ����
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


//��ʼ���ڴ�ռ� 
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

//������Ҫ�����ڴ����ҵ 
datatype* input(job* jobs, int i) 
{         
	datatype* item = (datatype*)malloc(sizeof(datatype));
	item->id = i;
	item->size = jobs[i].memorySize;
	item->status = 0;
	return item;
}

//��ӡ�ڴ������� 
void Momery_state(List* list, job* jobs) 
{
	List* temp = list;
	while (temp)
	{	
		//if (temp->node->size != 0)
		{
			if (temp->node->status == 0 && temp->node->id == -1 ) 
			{
				printf("\n**\tpartition ID��FREE\n");
				printf("**\taddress starting position��%d\n", temp->node->base);
				printf("**\tsize of Memory��%dK\n", temp->node->size);
				printf("**\tpartition status��free\n");
			}
			else
			{
				printf("\n**\tpartition ID��%d\n**\taddress starting position��%d\n", temp->node->id, temp->node->base);
				printf("**\tsize of Memory��%dK\n", temp->node->size);
				printf("**\tpartition status��Allocated\n");
				printf("**\ttapes occupancy:%d\n", jobs[temp->node->id].tapesQuantity);
			}
		}
		temp = temp->next;
	}
}

//�ڴ����
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
			if (front != NULL) {                      //�������ǵ�һ�η���ڵ㣬��ʱ��Ҫ���м������һ���ڵ�
				temp->node->base = temp->front->node->base + temp->front->node->size;        
				temp_next->next = temp->next;                                       
				temp_next->front = temp;                               
				temp->next = temp_next;                             //�����������ķ����ڵ����һ���ڵ�ָ��ոս�������ʱ�ڵ�
			}
			return 1;
		}
		else if (temp->node->status == 0 && temp->node->size == item->size)
		{
			item->base = temp->front->node->base + temp->front->node->size;               
			item->status = 1;                                           //��ʾ�Ѿ�����
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

//�ڴ���� 
int memory_recycle(List* list, int number) 
{
	List* temp = list;                      //����һ������ڵ� ָ��list ��ͷ�ڵ�
	while (temp)
	{
		if (temp->node->id == number)            //�����ҵ� �ڵ�id = number �Ľڵ㣬Ȼ�������������� 
		{
			// һ�� Ҫ���յ��ǵ�һ�����
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
					// ��ʱ���ж� temp->next �Ƿ���ϵͳ�����һ�����
					// ��ʱֻ����ǰ�ڵ� ����һ�����ϲ��Ϳ�����
					//�� �׵�ַ���䣬   ����״̬ �� ����id���б仯  
					temp->node->size = temp->node->size + next->node->size;
					temp->node->status = 0;
					temp->node->id = -1;
					temp->next = next->next;
					if (next->next == NULL) {
						free(next);
						return 1;
					}
					//����������һ�����Ļ��ͻ��һ������
					// �� next->next->front ָ����һ�����
					else
					{
						next->next->front = temp;
						free(next);
						return 1;
					}
				}

				return 1;
			}
			//���� ǰ��û�п��еķ���
		  //��򵥣�   ֱ�Ӹı� ������ id �� ������״̬�Ϳ����ˡ�
		  // ������յ�һ�������Ļ� ����Ҫ�Ƚ��д���������Ƚ��д��� ���ж� temp->front->node->id != -1 �ᱨһ���δ�����Ϊtemp-��front ��ʱָ�����null  
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
				//����������һ�����Ļ��ͻ��һ������
				// �� next->next->front ָ����һ�����
				else
				{

					next->next->front = front;
					free(temp);
					return 1;
				}
				return 1;
			}
			// ǰ��Ľڵ��ǿ��е�
			//�ϲ���ķ�����ʼ��ַΪǰһ����㣬 ������СΪǰһ���ڵ� �� ��ǰ�ڵ�֮�͡�
			if (temp->front->node->id == -1 && temp->front->node->status == 0) {
				List* front = temp->front;
				front->next = temp->next;
				temp->next->front = front;
				front->node->size += temp->node->size;
				free(temp);
				return 1;
			}
			//�塢����Ķ�ڵ��ǿ��е�
			//�ϲ���ķ����׵�ַΪ��ǰ�ڵ� ��  ������СΪ��ǰ�ڵ� �� ��ǰ�ڵ����һ������С֮�͡�
			// �����Ҫ��һ�����裬 �ı������ id ��  ������״̬��
			// ��Ҫע��һ�㣺  ��Ҫ���յĿռ��Ǻ�  ϵͳ���Ŀ���������ʱ �� temp->next->next ָ�����null��

			if (temp->next->node->id == -1 && temp->next->node->status == 0) {
				List* next = temp->next;
				// ��ʱ���ж� temp->next �Ƿ���ϵͳ�����һ�����
				// ��ʱֻ����ǰ�ڵ� ����һ�����ϲ��Ϳ�����
				//�� �׵�ַ���䣬   ����״̬ �� ����id���б仯  
				temp->node->size = temp->node->size + next->node->size;
				temp->node->status = 0;
				temp->node->id = -1;
				temp->next = next->next;
				if (next->next == NULL) {
					free(next);
					return 1;
				}
				//����������һ�����Ļ��ͻ��һ������
				// �� next->next->front ָ����һ�����
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
	
	//Ϊ�����ҵ������Դ 
	if((insert_state = memory_allocate(list, jobs, i)) == 1 && jobs[i].tapesQuantity <= tapes_quantity)
	{	
		tapes_quantity -= jobs[i].tapesQuantity;
		jobs[i].memoryState = 1;
		Momery_state(list, jobs);
		printf("\n**\trest tape drive: %d\n", tapes_quantity);
	}
	else jobs[i].memoryState = 0; 
}

//ɸѡ�������Դ�����ʸ����ҵ 
int fcfs(job* jobs, int current_time)
{
	int i,j;
	for(i = 0; i<Job_number; i++)
	{	
		if(jobs[i].memoryState == 0 && current_time >= jobs[i].arrivalTime)
		{
			for(j = 0; j<Job_number; j++)
			{
				if(jobs[j].memoryState == 1 || jobs[j].memoryState == 2) continue;  //ֱ������������ִ�л�������ɵ���ҵ���бȶ� 
				else if(jobs[i].arrivalTime <= jobs[j].arrivalTime) continue;  //���������Ƿ��е���ʱ���i��ҵ�������ҵ 
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
			{	printf("\n*******\tsystem time��%s\t*******\n", printf_time(current_time + 600));
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
	//ѯ���û���Ҫʹ�õ��㷨 
	
	printf("*********************************\n");
	printf("*\tGDUT-���ʽ���ѧԺ\t*\n");
	printf("*\t 19�ƿ����̺�\t\t*\n");
	printf("*\t  3119009436\t\t*\n");
	printf("*********************************\n");
	
	
	
	printf("1:First come first service; 2:the shortest job first.\n"); 
	printf("please choose the algorithm that would be used in job scheduling��");
	op1 = getchar();
	getchar();
	
	printf("1:First come first service; 2:the shortest process first.\n"); 
	printf("please choose the algorithm that would be used in process scheduling��");
	op2 = getchar();
	getchar();
	
	//��ȡ��ҵ��� 
	receive_jobs(jobs);
	i = fcfs(jobs, current_time);
	
	job_scheduling(&list, jobs, i);
	//��ʼ���� 
	do
	{	
		if(op1 == '1') i = fcfs(jobs, current_time);
		else i = sjf(jobs, current_time);
		if(i != -1) job_scheduling(&list, jobs, i); //�����process���Ѿ��������˻���ô�����i 
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
