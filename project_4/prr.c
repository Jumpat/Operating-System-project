
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
	int quantum=10;
	int x;
	//int time=0;
	int flag=1;
	int flag1=1;
	int counter=0;
	int i=0;
	int j=0;
	int thefirstindex;
	int k=0;
	struct task t[1000];

        file = argv[1];


	//printf("start\n");

	open = fopen(file, "r");
	//printf("opened\n");

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
			//printf("reading");
			counter++;
			i=0;
			k=0;

			}
		}
	
	/* end of read file */
	sortForTask(t,counter);
	//printf( "finished with counter of %d",counter );
	//counter=10;
	while(flag)
	{
		i=i%counter;
		//i=0;
		//j=0;	
		if(j==0) 
		{	
			thefirstindex=0;
			i=i%counter;
			//if()
			if(t[i].brust)
			{
				strcpy(future[j].bruster,t[i].name);
				if(t[i].brust>quantum)
				{
					t[i].brust-=quantum;
					future[j].time=0;
					future[j].brusttime=quantum;
					j++;
					i++;
				}
				else
				{
					
					future[j].time=0;
					future[j].brusttime=t[i].brust;
					t[i].brust=0;
					i++;
					j++;
				}

	
			}
			else i++;
			
			

		}
		else
		{
			i=i%counter;
			for(k=thefirstindex;k<i;k++)
				if(t[k].brust!=0)	flag1=0;
			if(t[i].priority!=t[i-1].priority&&flag1==0)	{i=thefirstindex; flag1=1;}
			if(t[i].brust)
			{
				strcpy(future[j].bruster,t[i].name);
				if(t[i].brust>quantum)
				{
					t[i].brust-=quantum;
					future[j].brusttime=quantum;
					future[j].time=future[j-1].time+future[j-1].brusttime;
					j++;
					i++;
				}
				else
				{
					future[j].time=future[j-1].time+future[j-1].brusttime;
					future[j].brusttime=t[i].brust;
					t[i].brust=0;
					i++;
					j++;
				}	
			}
			else i++;
			//printf( "\n%d",i);
		}
		

		flag=0;
		
		for(x=0;x<counter;x++)
			if(t[x].brust!=0)	flag=1;
		//if(flag=100) break;
		
	}
	
	
	for(x=0;x<j;x++)
	{
		printf( "%s %d   ", future[x].bruster, future[x].time );
	}
		printf( "\n");
		//printf( "%s, %d, %d\n", t[i].name, t[i].priority, t[i].brust);

	
	
    
	fclose(open);
        //printf("%d,%s \n",counter,file);
	
}

