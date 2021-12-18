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
	printf("������id��");
	scanf("%d", &item->id);
	printf("������ڴ��С��");
	scanf("%d", &item->size);
	item->status = 0;
	return item;
}
void Momery_state(List* list) {
	List* temp = list;
	while (temp)
	{
		if (temp->node->status == 0 && temp->node->id == -1) {
			printf("\n**\t�����ţ�FREE\n");
			printf("**\t��ʼ��ַ��%d\n", temp->node->base);
			printf("**\t�ڴ��С��%d\n", temp->node->size);
			printf("**\t����״̬������\n");
		}
		else
		{
			printf("\n**\t�����ţ�%d\n**\t��ʼ��ַ��%d\n", temp->node->id, temp->node->base);
			printf("**\t�ڴ��С��%d\n", temp->node->size);
			printf("**\t����״̬���ѷ���\n");
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

int Momory_recycle(List* list) {
	List* temp = list;                      //����һ������ڵ� ָ��list ��ͷ�ڵ�
	int number;                         //���ڴ��Ҫ�ͷŵĽڵ�ķ�����
	printf("��������Ҫ���յ�ID�ţ�");
	scanf("%d", &number);
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


int Best_fit(List* list) {
	int min = 0;        //��¼ ��С�����Ľ��Ĵ�С
	int base_min = 0;      //��¼ ��С�ڵ�Ľ�����ʼ��ַ
	List* temp = list;
	datatype* item = input();              // Ҫ�� item �� ��ʼ��ַ  �� ����״̬���г�ʼ��

	while (temp)
	{
		//�������δ�����Ҫ���бȽϲ���,���Ҽ�¼��ֵ�ͷ�����
		if (temp->node->status == 0 && temp->node->id == -1 && temp->node->size > item->size) {
			if (min == 0) {          //����minΪ0 ��ʾ��δ�ҵ�һ�����Է���ķ���
				min = temp->node->size;
				base_min = temp->node->base;
			}
			else
			{
				if (temp->node->size < min) {      // �ҵ�һ��֮����Ҫ�ҳ���С�ķ�����
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

	//��Ϊ����û���κ�һ���ռ��������Ҫ����Ҫ��һ���жϴ���   
	temp = list;
	while (temp)
	{
		if (temp->node->base == base_min) {

			datatype* temp_node = (datatype*)malloc(sizeof(datatype));      //���ж���Ŀռ�����  ������Ҫ�ڽ���һ�������뵽������
			temp_node->id = -1;
			temp_node->status = 0;
			temp_node->base = base_min + item->size;
			temp_node->size = temp->node->size - item->size;

			temp->node = item;                          //��item���������ĳ�ʼ��
			temp->node->base = base_min;
			temp->node->status = 1;

			List* temp_list_node = (List*)malloc(sizeof(List));         //������һ�� ����Ľ�� ���ҳ�ʼ��
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
	printf("������Ҫִ�е��㷨\n");
	printf("1-�״���Ӧ�㷨�� 2-�����Ӧ�㷨:");
	scanf("%d", &select);
	do
	{
		printf("\n������Ҫִ�еĲ���\n");
		printf("-1-�˳��� 0-�����ڴ棬 1-�����ڴ�:");
		scanf("%d", &op);
		printf("\n");
		getchar();
		switch(op)
		{
		case 1:			// 1. �����ڴ�
			switch (select)
			{
			case 1:              // 1. �״���Ӧ�㷨
				insert_state = First_fit(&list);
				if (insert_state == 0) {
					printf("����ʧ��\n");
				}
				else {
					printf("����ɹ���\n");
				}
				break;
			case 2:             // 2. �����Ӧ�㷨
				insert_state_best = Best_fit(&list);
				if (insert_state_best == 1) {
					printf("����ɹ�\n");
				}
				else {
					printf("����ʧ��\n");
				}
				break;
			}
			break;
		case 0:             // 0. �ڴ����
			recycle_state = Momory_recycle(&list);
			if (recycle_state == 1) {
				printf("���ճɹ���\n");
			}
			else {
				printf("����ʧ��\n");
			}
			break;
		}
	Momery_state(&list);             //4.��ʾ�ڴ�״��
	} while (op != -1);

	system("pause");
}
