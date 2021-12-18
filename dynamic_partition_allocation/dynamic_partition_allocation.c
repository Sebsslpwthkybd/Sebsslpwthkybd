#include<stdio.h>
#include<stdlib.h>

typedef struct lei_item       
{
	int id;                 
	int base;              
	int size;               
	int status;             
}Item;
typedef Item datatype;

typedef struct lei_list
{
	datatype* node;      
	struct lei_list* front;
	struct lei_list* next;
}List;

#define Max 640
int memory = Max;       



List init() {            
	List list;
	list.node = (datatype*)malloc(sizeof(datatype));
	list.node->base = 0;
	list.node->id = -1;                     
	list.node->size = memory;
	list.node->status = 0;
	list.front = list.next = NULL;
	return list;
}

datatype* input() {         
	datatype* item = (datatype*)malloc(sizeof(datatype));
	printf("请输入id：");
	scanf("%d", &item->id);
	printf("申请的内存大小：");
	scanf("%d", &item->size);
	item->status = 0;
	return item;
}
void Momery_state(List* list) {
	List* temp = list;
	while (temp)
	{
		if (temp->node->status == 0 && temp->node->id == -1) {
			printf("\n**\t分区号：FREE\n");
			printf("**\t起始地址：%d\n", temp->node->base);
			printf("**\t内存大小：%d\n", temp->node->size);
			printf("**\t分区状态：空闲\n");
		}
		else
		{
			printf("\n**\t分区号：%d\n**\t起始地址：%d\n", temp->node->id, temp->node->base);
			printf("**\t内存大小：%d\n", temp->node->size);
			printf("**\t分区状态：已分配\n");
		}
		temp = temp->next;
	}

}

int First_fit(List* list) {
	datatype* item = input();
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

int Momory_recycle(List* list) {
	List* temp = list;                      //申请一个链表节点 指向list 的头节点
	int number;                         //用于存放要释放的节点的分区号
	printf("请输入需要回收的ID号：");
	scanf("%d", &number);
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


int Best_fit(List* list) {
	int min = 0;        //记录 最小分区的结点的大小
	int base_min = 0;      //记录 最小节点的结点的起始地址
	List* temp = list;
	datatype* item = input();              // 要对 item 的 起始地址  和 分配状态进行初始化

	while (temp)
	{
		//如果分区未分配就要进行比较操作,并且记录差值和分区号
		if (temp->node->status == 0 && temp->node->id == -1 && temp->node->size > item->size) {
			if (min == 0) {          //加入min为0 表示还未找到一个可以分配的分区
				min = temp->node->size;
				base_min = temp->node->base;
			}
			else
			{
				if (temp->node->size < min) {      // 找到一个之后，需要找出最小的分区。
					min = temp->node->size;
					base_min = temp->node->base;
				}
			}

		}
		if (temp->node->status == 0 && temp->node->id == -1 && temp->node->size == item->size) {
			int base = temp->node->base;
			temp->node = item;
			temp->node->status = 1;
			temp->node->base = base;
			return 1;
		}
		temp = temp->next;
	}

	//因为可能没有任何一个空间可以满足要求需要做一个判断处理   
	temp = list;
	while (temp)
	{
		if (temp->node->base == base_min) {

			datatype* temp_node = (datatype*)malloc(sizeof(datatype));      //会有多余的空间多出来  所以需要在建立一个结点插入到链表中
			temp_node->id = -1;
			temp_node->status = 0;
			temp_node->base = base_min + item->size;
			temp_node->size = temp->node->size - item->size;

			temp->node = item;                          //对item进行完整的初始化
			temp->node->base = base_min;
			temp->node->status = 1;

			List* temp_list_node = (List*)malloc(sizeof(List));         //新申请一个 链表的结点 并且初始化
			temp_list_node->node = temp_node;
			temp_list_node->front = temp;
			temp_list_node->next = temp->next;
			if (temp->next != NULL) {
				temp->next->front = temp_list_node;
			}
			temp->next = temp_list_node;
			return 1;
		}
		temp = temp->next;
	}

}


int main() {
	List list = init();
	int select;
	int op;
	int insert_state, recycle_state;
	int insert_state_best;
	printf("请输入要执行的算法\n");
	printf("1-首次适应算法， 2-最佳适应算法:");
	scanf("%d", &select);
	do
	{
		printf("\n请输入要执行的操作\n");
		printf("-1-退出， 0-回收内存， 1-分配内存:");
		scanf("%d", &op);
		printf("\n");
		getchar();
		switch(op)
		{
		case 1:			// 1. 分配内存
			switch (select)
			{
			case 1:              // 1. 首次适应算法
				insert_state = First_fit(&list);
				if (insert_state == 0) {
					printf("分配失败\n");
				}
				else {
					printf("分配成功！\n");
				}
				break;
			case 2:             // 2. 最佳适应算法
				insert_state_best = Best_fit(&list);
				if (insert_state_best == 1) {
					printf("分配成功\n");
				}
				else {
					printf("分配失败\n");
				}
				break;
			}
			break;
		case 0:             // 0. 内存回收
			recycle_state = Momory_recycle(&list);
			if (recycle_state == 1) {
				printf("回收成功！\n");
			}
			else {
				printf("回收失败\n");
			}
			break;
		}
	Momery_state(&list);             //4.显示内存状况
	} while (op != -1);

	system("pause");
}
