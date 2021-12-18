#include <stdio.h>
#include <stdlib.h>
 
typedef struct item
{
	int num;		
	int time;		
}Pro;
int pageNum;		
int memoryNum;		
void print(Pro *page1);		
int  Search(int num1, Pro *memory1);	
 
int main(void)
{
	int i;
	int curmemory;		
	int missNum;		
	float missRate;		
	int op;				
 
	Pro *page;		
	Pro *memory;		
  
	page = (Pro*)malloc(sizeof(Pro)*pageNum);
	memory = (Pro*)malloc(sizeof(Pro)*memoryNum);
 
	printf("Enter the number of pages:");
	scanf("%d", &pageNum);
	printf("Enter the number of blocks:");
	scanf("%d", &memoryNum);

	for (i = 0; i<pageNum; i++)
	{
		printf("Enter the %d page number:", i);
		scanf("%d", &page[i].num);
		page[i].time = 0;			
	}
 
	do {
		for (i = 0; i<memoryNum; i++)		
		{
			memory[i].num = -1;				
			memory[i].time = -1;				
		}
		
 		printf("-----------------\n");
		printf("------1:OPT------\n");
		printf("------2:FIFO-----\n");
		printf("------3:LRU------\n");
		printf("------0:exit-----\n");
		printf("-----------------\n");
		
		printf("\n");
		getchar();
		scanf("%1d", &op);
 		printf("\n");
		i = 0;
		curmemory = 0;
 
 		switch(op)
		{
		 	case 1:
				missNum = 0;
				curmemory = 0;
	 
				printf("Optimal outcome:   \n");
				for (i = 0; i<pageNum; i++)
				{
					if (Search(page[i].num, memory) < 0)
					{
	 
						   
						int tem,k;
						int opt = 0;
						for (k = 0; k < memoryNum; k++)
						{
							if (memory[k].num == -1)
							{
								curmemory = k;
								break;
							}
							tem = 0;       
							int j;
							for (j = i+1; j < pageNum; j++)
							{
								if (page[j].num == memory[k].num)
								{
									if (tem > opt)
									{
										opt = tem;
										curmemory = k;
									}
									break;
								}
								else tem++;
							}
							if (j == pageNum)
							{
								opt = tem;
								curmemory = k;
							}
						}
	 
						missNum++;
						memory[curmemory].num = page[i].num;
						print(memory);
					}
				}//end for
				missRate = (float)missNum / pageNum;
				printf("Page fault times£º%d   Page fault percentage:  %f\n", missNum, missRate);
				break;
 
 			case 2:	
				missNum = 0;
	 
				printf("FIFO outcome:   \n");
				for (i = 0; i<pageNum; i++)
				{
					if (Search(page[i].num, memory)<0)
					{
						missNum++;
						memory[curmemory].num = page[i].num;
						print(memory);
						curmemory = (curmemory + 1) % memoryNum;   
					}
				}//end for
				missRate = (float)missNum / pageNum;
				printf("Page fault times£º%d   Page fault percentage:  %f\n", missNum, missRate);
				break;
				
			case 3:
				missNum = 0;
				curmemory = 0;
	 
				printf("LRU outcome:   \n");
				for (i = 0; i<pageNum; i++)
				{
					int rec=Search(page[i].num, memory);
					int j;
					if (rec < 0)    
					{
						missNum++;
						for (j = 0; j<memoryNum; j++)     
							if (memory[j].time == -1) {
								curmemory = j; break;
							}
							else if (memory[j].time > memory[curmemory].time)
								curmemory = j;
	 
						memory[curmemory].num = page[i].num;
						memory[curmemory].time = 0;
						print(memory);
	 
					}
					else memory[rec].time = 0;
	 
					for (j = 0; j<memoryNum; j++)    	
						if (memory[j].num != -1)
							memory[j].time++;
	 
				}//end for
				missRate = (float)missNum / pageNum;
				printf("Page fault times£º%d   Page fault percentage:  %f\n", missNum, missRate);
				break;
			
			default:
				return 0;
				break;
 		}
 		
	}while (op == 1 || op == 2 || op == 3);
	return 0;
}
 
 
void print(Pro *memory1)
{
	int j;
 
	for (j = 0; j<memoryNum; j++)
		printf("%d ", memory1[j].num);
	printf("\n");
}
 

int  Search(int num1, Pro *memory1)
{
	int j;
 
	for (j = 0; j<memoryNum; j++)
	{
		if (num1 == memory1[j].num)
			return j;
	}
	return -1;
}

