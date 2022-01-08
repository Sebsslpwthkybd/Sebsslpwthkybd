#include <stdio.h>
#include <stdlib.h>
#include <time.h>

//�ڴ�
//��Ϊ����ڵ㣬���ҳ��
typedef struct PageInMemory {
	int pageIndex;
	struct PageInMemory* next;
} memory;

//���������
int myrandom(int begin, int end) {
	if (begin == 0) return rand() % (end + 1);
	else return rand() % (end - begin + 1) + begin;
}

//����ָ������
void makeInstructionSequence(int* instructionSequence) {
	int m;
        //save��ǰ��ַѡȡָ�������ڴ洢m
	int save;
	int i;
	m = myrandom(0, 318);
	for (i = 0; i < 320; i += 4) {
		instructionSequence[i] = m;
		instructionSequence[i + 1] = m + 1;
		save = m + 1;
		do {
			m = myrandom(0, save);
		} while (m >= 317);
		instructionSequence[i + 2] = m;
		instructionSequence[i + 3] = m + 1;
		m = myrandom(m + 2, 318);
	}
}

//ָ�����б任Ϊҳ��ַ��
void instructionToPageAdressStream(int* page, int* instructionSequence) {
	int i;
	for (i = 0; i < 320; i++) page[i] = instructionSequence[i] / 10;
}


int match(int* page, int index, memory* front, int memoryCapacity) {
	memory* new = ((memory*)malloc(sizeof(memory)));
	new->pageIndex = front->pageIndex;
	new->next = NULL;
	//currΪ�����ڴ�������޸�ָ�룬pΪԭ�ڴ�����ĵ�ǰָ��
	memory* frontSimulation = new, * curr = frontSimulation, * p = front->next;
	while (p) {
		new = ((memory*)malloc(sizeof(memory)));
		new->pageIndex = p->pageIndex;
		new->next = NULL;
		curr->next = new;
		curr = curr->next;
		p = p->next;
	}

	//�����Ѿ�ɾ���ĸ����ڴ���������
	int count = 0;
	int i;
	for (i = index; i < 320; i++) {
		//�������ͷ����ѭ���е�ҳ��ֱ��ɾ������ͷ
		if (frontSimulation->pageIndex == page[i]) {
			memory* save = frontSimulation;
			frontSimulation = frontSimulation->next;
			free(save);
			count++;
			//���ɾ����1������ֱ�ӷ��ظý��ָ��
			if (memoryCapacity - count == 1) return frontSimulation->pageIndex;
			continue;
		}

		memory* pre = frontSimulation;
		curr = frontSimulation->next;
		//�����ж���û���ҵ���ɾ���Ľ�㣬���뵱ǰѭ��ҳ��ͬ�ĵĽ��
		int flag = 0;
		while (curr) {
			if (curr->pageIndex == page[i]) {
				flag = 1;
				break;
			}
			pre = pre->next;
			curr = curr->next;
		}

		//�ҵ���Ҫɾ���Ľ��
		if (flag) {
			pre->next = curr->next;
			free(curr);
			count++;
			//���ɾ����1������ֱ�ӷ��ظý��ָ��
			if (memoryCapacity - count == 1) return frontSimulation->pageIndex;
		}
		//û�ҵ���Ҫɾ���Ľ��
		else continue;
	}
	return frontSimulation->pageIndex;
}

//�����̭�㷨��OPT��
void OPT(int memoryCapacity, int* page) {
	//������
	double hitRate;
	//û���е�ҳ��������ʼ��Ϊ0
	int miss = 0;
	//�ڴ���е�ͷ��β
	memory* front, * rear;
	front = rear = NULL;
	
	int i;
	for (i = 0; i < 320; i++) {
		memory* curr = front;
		//flag�����жϸ�ָ������ҳ���Ƿ����ڴ�
		int flag = 0;
		//countͳ�������ȣ�����ҳ�治���ڴ��У����ڸ���ָ��front
		int count = 0;
		while (curr) {
			if (curr->pageIndex == page[i]) {
				flag = 1;
				break;
			}
			count++;
			curr = curr->next;
		}
		//ָ�벻��ʹ�ã��ÿ�
		curr = NULL;

		//ָ������ҳ�����ڴ��У�������һ��ָ��
		if (flag) continue;

		//ָ������ҳ�治���ڴ棬���Ƚ��ȳ���ԭ�򣬽�����ҳ������ڴ�
		else {
			miss++;
			//�����½��
			memory* new = ((memory*)malloc(sizeof(memory)));
			if (new == NULL) {
				printf("�ڴ���䲻�ɹ���\n");
				exit(1);
			}
			new->pageIndex = page[i];
			new->next = NULL;

			//����ڴ���û��ҳ�棬�൱�ڳ�ʼ��front
			if (count == 0)  front = new;
			//����ڴ�����
			else if (count == memoryCapacity) {
				//�ҵ�Ҫ�����Ľ���ָ��
				int replace = match(page, i, front, memoryCapacity);
				//�������ͷҪ���������¶���ͷ��ɾ��ԭ���Ķ���ͷ���
				if (replace == front->pageIndex) {
					memory* save = front;
					front = front->next;
					free(save);
				}
				//������Ƕ���ͷҪ����
				//��Ҫ�ҵ�Ҫ��������ǰһ�����
				else {
					memory* pre = front, * curr = front->next;
					while (curr->pageIndex != replace) {
						pre = pre->next;
						curr = curr->next;
					}
					pre->next = curr->next;
					free(curr);
					rear = front;
					while (rear->next) rear = rear->next;
				}
				rear->next = new;
			}
			//����ڴ�������ҳ�棬���½�����ڶ������
			else rear->next = new;
			//rear����Ϊ���
			rear = new;
		}
	}

	//�ͷ���Դ
	while (front) {
		memory* curr = front;
		front = front->next;
		free(curr);
		curr = NULL;
	}
	rear = NULL;

	//����������
	hitRate = 1 - miss / 320.0;
	printf("OPT: %f%s\t\t", hitRate * 100, "%");
}

//�Ƚ��ȳ����㷨��FIFO��
void FIFO(int memoryCapacity, int* page) {
	//������
	double hitRate;
	//û���е�ҳ��������ʼ��Ϊ0
	int miss = 0;
	//�ڴ���е�ͷ��β
	memory* front, * rear;
	front = rear = NULL;
	
	int i;
	for (i = 0; i < 320; i++) {
		memory* curr = front;
		//flag�����жϸ�ָ������ҳ���Ƿ����ڴ�
		int flag = 0;
		//countͳ�������ȣ�����ҳ�治���ڴ��У����ڸ���ָ��front
		int count = 0;
		while (curr) {
			if (curr->pageIndex == page[i]) {
				flag = 1;
				break;
			}
			count++;
			curr = curr->next;
		}
		//ָ�벻��ʹ�ã��ÿ�
		curr = NULL;

		//ָ������ҳ�����ڴ��У�������һ��ָ��
		if (flag) continue;

		//ָ������ҳ�治���ڴ棬���Ƚ��ȳ���ԭ�򣬽�����ҳ������ڴ�
		else {
			miss++;
			//�����½��
			memory* new = ((memory*)malloc(sizeof(memory)));
			if (new == NULL) {
				printf("�ڴ���䲻�ɹ���\n");
				exit(1);
			}
			new->pageIndex = page[i];
			new->next = NULL;

			//����ڴ�����
			//�ͷŶ���ͷ��һ����㣬front����
			if (count == memoryCapacity) {
				memory* curr = front;
				if (front) front = front->next;
				free(curr);
				curr = NULL;
				rear->next = new;
			}

			//����ڴ���û��ҳ�棬�൱�ڳ�ʼ��front
			if (count == 0) front = new;
			//����ڴ�������ҳ�棬���½�����ڶ������
			else rear->next = new;
			//rear����Ϊ���
			rear = new;
		}
	}

	//�ͷ���Դ
	while (front) {
		memory* curr = front;
		front = front->next;
		free(curr);
		curr = NULL;
	}
	rear = NULL;

	//����������
	hitRate = 1 - miss / 320.0;
	printf("FIFO: %f%s\t", hitRate * 100, "%");
}

//������δʹ���㷨��LRU��
void LRU(int memoryCapacity, int* page) {
	//������
	double hitRate;
	//ȱҳ������ʼ��Ϊ0
	int miss = 0;
	//�ڴ�ջ��ջ����ջ��
	memory* top, * bottom;
	top = bottom = NULL;
	
	int i;
	for (i = 0; i < 320; i++) {
		memory* curr = bottom;
		//flag�����жϸ�ָ������ҳ���Ƿ����ڴ�
		int flag = 0;
		//countͳ�������ȣ�����ҳ�治���ڴ��У����ڸ���ָ��front
		int count = 0;
		while (curr) {
			if (curr->pageIndex == page[i]) {
				flag = 1;
				break;
			}
			count++;
			curr = curr->next;
		}

		//ָ������ҳ�����ڴ���
		//����ҳ���ջ��ȡ��������ջ����
		if (flag) {
			//�����ҳ����ջ��
			if (bottom == curr) {
				top->next = bottom;
				bottom = bottom->next;
				top = top->next;
				top->next = NULL;
			}
			//�����ҳ�治��ջ��
			else {
				//preΪcurr��ǰһ������ָ��
				memory* pre = bottom;
				while (pre->next != curr) pre = pre->next;
				top->next = curr;
				pre->next = curr->next;
				top = top->next;
				top->next = NULL;
			}
			//������һ��ָ��
			continue;
		}
		//ָ������ҳ�治���ڴ棬���Ƚ��ȳ���ԭ�򣬽�����ҳ������ڴ�
		else {
			//ȱҳ��+1
			miss++;
			//�����½��
			memory* new = ((memory*)malloc(sizeof(memory)));
			if (new == NULL) {
				printf("�ڴ���䲻�ɹ���\n");
				exit(1);
			}
			new->pageIndex = page[i];
			new->next = NULL;

			//����ڴ���û��ҳ�棬�൱�ڳ�ʼ��top��bottom
			if (count == 0) {
				top = new;
				bottom = new;
			}
			//����ڴ�����
			//ɾ��ջ��Ԫ��
			//�ڽ��½�����ջ��
			else if (count == memoryCapacity) {
				memory* curr = bottom;
				if (bottom) bottom = bottom->next;
				free(curr);
				top->next = new;
				top = top->next;
				top->next = NULL;
			}
			//����ڴ�������ҳ�棬���½�����ջ��
			else {
				top->next = new;
				top = top->next;
				top->next = NULL;
			}
		}
	}
	//�ͷ���Դ
	while (bottom) {
		memory* curr = bottom;
		bottom = bottom->next;
		free(curr);
		curr = NULL;
	}
	top = NULL;

	//����������
	hitRate = 1 - miss / 320.0;
	printf("LRU: %f%s\t", hitRate * 100, "%");
}

int main() {
	srand((unsigned)time(NULL));

	//ָ������
	int* instructionSequence = (int*)malloc(sizeof(int) * 320);
	makeInstructionSequence(instructionSequence);

	//��ָ�����б任Ϊҳ��ַ��
	//ҳ��
	int* page = (int*)malloc(sizeof(int) * 320);
	instructionToPageAdressStream(page, instructionSequence);
	int i;
	printf("������ɵ�ָ����£�\n");
	for (i = 0; i < 320; i++) printf("%d ", page[i]);
	printf("\n");
	
	printf("\n");
	//�û��ڴ�������4ҳ��32ҳ
	for (i = 4; i <= 32; i++)
	{	
		printf("�ڴ�����Ϊ%dҳ\n", i);
		printf("ȱҳ�ʣ�\n");
		OPT(i, page);
		FIFO(i, page);
		LRU(i, page);
		printf("\n\n");
	}

	//�ͷ���Դ
	free(page);
	page = NULL;
	free(instructionSequence);
	instructionSequence = NULL;
	return 0;
}

