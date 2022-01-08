#include <stdio.h>
#include <stdlib.h>
#include <time.h>

//内存
//作为链表节点，存放页面
typedef struct PageInMemory {
	int pageIndex;
	struct PageInMemory* next;
} memory;

//生成随机数
int myrandom(int begin, int end) {
	if (begin == 0) return rand() % (end + 1);
	else return rand() % (end - begin + 1) + begin;
}

//生成指令序列
void makeInstructionSequence(int* instructionSequence) {
	int m;
        //save在前地址选取指令中用于存储m
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

//指令序列变换为页地址流
void instructionToPageAdressStream(int* page, int* instructionSequence) {
	int i;
	for (i = 0; i < 320; i++) page[i] = instructionSequence[i] / 10;
}


int match(int* page, int index, memory* front, int memoryCapacity) {
	memory* new = ((memory*)malloc(sizeof(memory)));
	new->pageIndex = front->pageIndex;
	new->next = NULL;
	//curr为复制内存链表的修改指针，p为原内存链表的当前指针
	memory* frontSimulation = new, * curr = frontSimulation, * p = front->next;
	while (p) {
		new = ((memory*)malloc(sizeof(memory)));
		new->pageIndex = p->pageIndex;
		new->next = NULL;
		curr->next = new;
		curr = curr->next;
		p = p->next;
	}

	//计算已经删除的复制内存链表结点数
	int count = 0;
	int i;
	for (i = index; i < 320; i++) {
		//如果链表头等于循环中的页，直接删除链表头
		if (frontSimulation->pageIndex == page[i]) {
			memory* save = frontSimulation;
			frontSimulation = frontSimulation->next;
			free(save);
			count++;
			//如果删除至1个，则直接返回该结点指针
			if (memoryCapacity - count == 1) return frontSimulation->pageIndex;
			continue;
		}

		memory* pre = frontSimulation;
		curr = frontSimulation->next;
		//用于判断有没有找到需删除的结点，即与当前循环页相同的的结点
		int flag = 0;
		while (curr) {
			if (curr->pageIndex == page[i]) {
				flag = 1;
				break;
			}
			pre = pre->next;
			curr = curr->next;
		}

		//找到需要删除的结点
		if (flag) {
			pre->next = curr->next;
			free(curr);
			count++;
			//如果删除至1个，则直接返回该结点指针
			if (memoryCapacity - count == 1) return frontSimulation->pageIndex;
		}
		//没找到需要删除的结点
		else continue;
	}
	return frontSimulation->pageIndex;
}

//最佳淘汰算法（OPT）
void OPT(int memoryCapacity, int* page) {
	//命中率
	double hitRate;
	//没命中的页面数，初始化为0
	int miss = 0;
	//内存队列的头和尾
	memory* front, * rear;
	front = rear = NULL;
	
	int i;
	for (i = 0; i < 320; i++) {
		memory* curr = front;
		//flag用于判断该指令所在页面是否在内存
		int flag = 0;
		//count统计链表长度，若该页面不在内存中，用于更新指针front
		int count = 0;
		while (curr) {
			if (curr->pageIndex == page[i]) {
				flag = 1;
				break;
			}
			count++;
			curr = curr->next;
		}
		//指针不再使用，置空
		curr = NULL;

		//指令所在页面在内存中，继续下一条指令
		if (flag) continue;

		//指令所在页面不在内存，按先进先出的原则，将所需页面调入内存
		else {
			miss++;
			//创建新结点
			memory* new = ((memory*)malloc(sizeof(memory)));
			if (new == NULL) {
				printf("内存分配不成功！\n");
				exit(1);
			}
			new->pageIndex = page[i];
			new->next = NULL;

			//如果内存中没有页面，相当于初始化front
			if (count == 0)  front = new;
			//如果内存已满
			else if (count == memoryCapacity) {
				//找到要换出的结点的指针
				int replace = match(page, i, front, memoryCapacity);
				//如果队列头要换出，更新队列头，删除原来的队列头结点
				if (replace == front->pageIndex) {
					memory* save = front;
					front = front->next;
					free(save);
				}
				//如果不是队列头要换出
				//则要找到要换出结点的前一个结点
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
			//如果内存中已有页面，将新结点连在队列最后
			else rear->next = new;
			//rear调整为最后
			rear = new;
		}
	}

	//释放资源
	while (front) {
		memory* curr = front;
		front = front->next;
		free(curr);
		curr = NULL;
	}
	rear = NULL;

	//计算命中率
	hitRate = 1 - miss / 320.0;
	printf("OPT: %f%s\t\t", hitRate * 100, "%");
}

//先进先出的算法（FIFO）
void FIFO(int memoryCapacity, int* page) {
	//命中率
	double hitRate;
	//没命中的页面数，初始化为0
	int miss = 0;
	//内存队列的头和尾
	memory* front, * rear;
	front = rear = NULL;
	
	int i;
	for (i = 0; i < 320; i++) {
		memory* curr = front;
		//flag用于判断该指令所在页面是否在内存
		int flag = 0;
		//count统计链表长度，若该页面不在内存中，用于更新指针front
		int count = 0;
		while (curr) {
			if (curr->pageIndex == page[i]) {
				flag = 1;
				break;
			}
			count++;
			curr = curr->next;
		}
		//指针不再使用，置空
		curr = NULL;

		//指令所在页面在内存中，继续下一条指令
		if (flag) continue;

		//指令所在页面不在内存，按先进先出的原则，将所需页面调入内存
		else {
			miss++;
			//创建新结点
			memory* new = ((memory*)malloc(sizeof(memory)));
			if (new == NULL) {
				printf("内存分配不成功！\n");
				exit(1);
			}
			new->pageIndex = page[i];
			new->next = NULL;

			//如果内存已满
			//释放队列头第一个结点，front调整
			if (count == memoryCapacity) {
				memory* curr = front;
				if (front) front = front->next;
				free(curr);
				curr = NULL;
				rear->next = new;
			}

			//如果内存中没有页面，相当于初始化front
			if (count == 0) front = new;
			//如果内存中已有页面，将新结点连在队列最后
			else rear->next = new;
			//rear调整为最后
			rear = new;
		}
	}

	//释放资源
	while (front) {
		memory* curr = front;
		front = front->next;
		free(curr);
		curr = NULL;
	}
	rear = NULL;

	//计算命中率
	hitRate = 1 - miss / 320.0;
	printf("FIFO: %f%s\t", hitRate * 100, "%");
}

//最近最久未使用算法（LRU）
void LRU(int memoryCapacity, int* page) {
	//命中率
	double hitRate;
	//缺页数，初始化为0
	int miss = 0;
	//内存栈的栈顶和栈底
	memory* top, * bottom;
	top = bottom = NULL;
	
	int i;
	for (i = 0; i < 320; i++) {
		memory* curr = bottom;
		//flag用于判断该指令所在页面是否在内存
		int flag = 0;
		//count统计链表长度，若该页面不在内存中，用于更新指针front
		int count = 0;
		while (curr) {
			if (curr->pageIndex == page[i]) {
				flag = 1;
				break;
			}
			count++;
			curr = curr->next;
		}

		//指令所在页面在内存中
		//将该页面从栈中取出，放在栈顶上
		if (flag) {
			//如果该页面在栈底
			if (bottom == curr) {
				top->next = bottom;
				bottom = bottom->next;
				top = top->next;
				top->next = NULL;
			}
			//如果该页面不在栈底
			else {
				//pre为curr的前一个结点的指针
				memory* pre = bottom;
				while (pre->next != curr) pre = pre->next;
				top->next = curr;
				pre->next = curr->next;
				top = top->next;
				top->next = NULL;
			}
			//继续下一条指令
			continue;
		}
		//指令所在页面不在内存，按先进先出的原则，将所需页面调入内存
		else {
			//缺页数+1
			miss++;
			//创建新结点
			memory* new = ((memory*)malloc(sizeof(memory)));
			if (new == NULL) {
				printf("内存分配不成功！\n");
				exit(1);
			}
			new->pageIndex = page[i];
			new->next = NULL;

			//如果内存中没有页面，相当于初始化top和bottom
			if (count == 0) {
				top = new;
				bottom = new;
			}
			//如果内存已满
			//删除栈底元素
			//在将新结点放在栈顶
			else if (count == memoryCapacity) {
				memory* curr = bottom;
				if (bottom) bottom = bottom->next;
				free(curr);
				top->next = new;
				top = top->next;
				top->next = NULL;
			}
			//如果内存中已有页面，将新结点放在栈顶
			else {
				top->next = new;
				top = top->next;
				top->next = NULL;
			}
		}
	}
	//释放资源
	while (bottom) {
		memory* curr = bottom;
		bottom = bottom->next;
		free(curr);
		curr = NULL;
	}
	top = NULL;

	//计算命中率
	hitRate = 1 - miss / 320.0;
	printf("LRU: %f%s\t", hitRate * 100, "%");
}

int main() {
	srand((unsigned)time(NULL));

	//指令序列
	int* instructionSequence = (int*)malloc(sizeof(int) * 320);
	makeInstructionSequence(instructionSequence);

	//将指令序列变换为页地址流
	//页号
	int* page = (int*)malloc(sizeof(int) * 320);
	instructionToPageAdressStream(page, instructionSequence);
	int i;
	printf("随机生成的指令集如下：\n");
	for (i = 0; i < 320; i++) printf("%d ", page[i]);
	printf("\n");
	
	printf("\n");
	//用户内存容量从4页到32页
	for (i = 4; i <= 32; i++)
	{	
		printf("内存容量为%d页\n", i);
		printf("缺页率：\n");
		OPT(i, page);
		FIFO(i, page);
		LRU(i, page);
		printf("\n\n");
	}

	//释放资源
	free(page);
	page = NULL;
	free(instructionSequence);
	instructionSequence = NULL;
	return 0;
}

