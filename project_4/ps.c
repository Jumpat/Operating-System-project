
#include <stdlib.h>
#include <stdio.h>

#include <getopt.h>
#include <string.h>

struct task
{
	char name[100];
	int priority;
	int brust;
};

struct timeline
{
	char bruster[100];
	int brusttime;
	int time;
};

void sortForTask(struct task task[],int counter)
{
	int i,j;
	struct task tmp;
	int flag=1;
	for(i=0;i<counter-1&&flag;i++)
	{
		flag=0;
		for(j=0;j<counter-i-1;j++)
		{
			if(task[j].priority<task[j+1].priority)
			{
				tmp=task[j];
				task[j]=task[j+1];
				task[j+1]=tmp;
				flag=1;
			}
		}
	}

		
}

int main(int argc, char **argv)
{
	FILE *open;
	char *file;
	struct timeline future[1000];
	char tmp[100][100];
	char taskname[100];
	char num1[10];
	char num2[10];
	int priority;
	int brust;
	//int time=0;
	int counter=0;
	int i=0;
	int k=0;
	struct task t[1000];

        file = argv[1];


	open = fopen(file, "r");
	if (open != NULL) {
		while (fgets(tmp[counter],100,open)) {

			while(tmp[counter][i]!=',')
			{
				t[counter].name[i]=tmp[counter][i];
				i++;
			}
			t[counter].name[i]=0;
			i+=2;

			while(tmp[counter][i]!=',')
			{
				num1[k]=tmp[counter][i];
				i++;k++;
			}
			num1[k]=0;
			i+=2;
			k=0;
			while(tmp[counter][i]!=0)
			{
				num2[k]=tmp[counter][i];
				i++;k++;
			}
			num2[k]=0;

			t[counter].priority=atoi(num1);
			t[counter].brust=atoi(num2);
			//printf("%s\n",tmp[counter]);
			counter++;
			i=0;
			k=0;

			}
		}
	
	/* end of read file */
	sortForTask(t,counter);
	for(i=0;i<counter;i++)
	{
		strcpy(future[i].bruster,t[i].name);
		future[i].brusttime=t[i].brust;
		if(i==0) future[i].time=0;
		else future[i].time=future[i-1].time+future[i-1].brusttime;
	}
	
	for(i=0;i<counter;i++)
	{
		printf( "%s %d   ", future[i].bruster, future[i].time );
	}
		printf( "\n" );
		//printf( "%s, %d, %d\n", t[i].name, t[i].priority, t[i].brust);

	
	
    
	fclose(open);
        //printf("%d,%s \n",counter,file);
	
}

