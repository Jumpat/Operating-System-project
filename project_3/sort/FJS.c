#include <stdio.h>
#include <pthread.h>

#define threshold 10

typedef struct {
	int start;
	int end;
} Index;
int partation_single(int a[],int begin,int end);
void quicksort(Index index);
void *quicksortchild(void * args);

int array[100];

void swap(int a[],int i,int j)
{
	int temp=a[i];
	a[i]=a[j];
	a[j]=temp;
}


void* sort(void *args){
	//return;
	Index * index = (Index *)args;
	//elemType temp;
    	int i, j;

	i=index->start;
	j=index->end;
	//printf("but i do %d %d \n" ,i,j);
	//printf("so let me show you");
	for (i=0; i<index->end-index->start-1; i++) 
	for (j=index->start; j<index->end-1-i; j++) { 
	    if (array[j] > array[j+1]) { 
		swap(array,j,j+1);
	    }
	}
	/*for (i=0; i<index->end-index->start-1; i++) 
	for (j=0; j<index->end-index->start-1-i; j++) { 
	    if (array[j] > array[j+1]) { 
		swap(array,j,j+1);
	    }
	}*/
	//for (i=index->start; i<index->end; i++) 	printf("%d ",array[i]);
}


int initArray(){
	FILE *fp;
	fp = fopen("input", "r");
	int i=0;

	while(fscanf(fp, "%d", &array[i])!=EOF){
		i++;
		if(i>100){
			printf("error:最多接受100个数字！\n");
			break;
		}
	}
	//printf("\n");
	fclose(fp);
	return i;
}




//void mergesort(int array[]);
//void mergesort(void * args);


int main(void)
{
	int i;
	int size;
	size=initArray();
	for(i=0;i<size;i++) printf("%d ",array[i]);
	printf("\n");
	Index index;
	index.start=0;
	index.end=size;
	quicksort(index);
	for(i=0;i<size;i++) printf("%d ",array[i]);
	printf("\n");
	
}

void quicksort(Index index)
{
	pthread_t tid;
	pthread_attr_t attr;
	pthread_attr_init(&attr);
	pthread_create(&tid, &attr, quicksortchild, &index);
	pthread_join(tid, NULL);
}

void *quicksortchild(void * args)
{
	Index * index = (Index *)args;
	if(index->end-index->start+1<=threshold)
	{
		pthread_t tid;
		pthread_attr_t attr;
		pthread_attr_init(&attr);
		pthread_create(&tid, &attr, sort, index);
		pthread_join(tid, NULL);
		//printf("why not\n");

		//printf("%d %d \n",index->start,index->end);
		pthread_exit(0);
	}
	else
	{
		int c;
		Index ind[2];
		c=partation_single(array,index->start,index->end);
		ind[0].start=index->start;
		ind[0].end=c;
		ind[1].start=c+1;
		ind[1].end=index->end;
		pthread_t tid[2];
		pthread_attr_t attr;
		pthread_attr_init(&attr);
		pthread_create(&tid[0], &attr, quicksortchild, &ind[0]);
		pthread_create(&tid[1], &attr, quicksortchild, &ind[1]);
		pthread_join(tid[0], NULL);
		
		pthread_join(tid[1], NULL);
		
		pthread_exit(0);
		
	}
}

int partation_single(int a[],int begin,int end)
{
	int left,right;
	int key=a[begin];

	left=begin;
	right=end-1;

	while(left!=right)
	{
		for( ;left<right;right--)
		{
			if(a[right]<key)
			{
				//cur++;
				swap(a,left,right);
				break;
			}
		}
		for( ;left<right;left++)
		{
			if(a[left]>key)
			{
				//cur++;
				swap(a,left,right);
				break;
			}
		}
	}
	
	
	a[left]=key;
	return left;
}
