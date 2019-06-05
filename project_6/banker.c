#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define NUMBER_OF_CUSTOMERS 5
#define NUMBER_OF_RESOURCES 4

int available[NUMBER_OF_RESOURCES];
int maximum[NUMBER_OF_CUSTOMERS][NUMBER_OF_RESOURCES];
int allocation[NUMBER_OF_CUSTOMERS][NUMBER_OF_RESOURCES];
int need[NUMBER_OF_CUSTOMERS][NUMBER_OF_RESOURCES];

int request_resources(int customer_num, int request[]);
void release_resources(int customer_num, int release[]);


void bankerinit(int a[]);
int judge();

int main(int argc, char **argv)
{
	int i,j;
	int des;
	int resources[4];
	int request[4];
	char command[3];
	for(i=0;i<4;i++)
		resources[i]=atoi(argv[i+1]);
	bankerinit(resources);
	//printf("%d",judge());

	while(1)
	{
	scanf("%s",command);	
	if(strcmp(command,"RQ")==0)
	{
		scanf("%d %d %d %d %d",&des,&request[0],&request[1],&request[2],&request[3]);
		//request_resources(des , request);
		printf("rq : %d\n",request_resources(des , request));
	}	
	if(strcmp(command,"RL")==0)
	{
		scanf("%d %d %d %d %d",&des,&request[0],&request[1],&request[2],&request[3]);
		release_resources(des, request);
		//printf("rl : %d",request[0]);
	}
	if(strcmp(command,"*")==0)
	{
		printf("available!!->\n");
		for(i=0;i<4;i++)	printf("%d ",available[i]);
		printf("\n");
	
		printf("maximum!!->\n");
		for(i=0;i<5;i++)
		{
			for(j=0;j<4;j++)
			{
				printf("%d ",maximum[i][j]);
			}
			printf("\n");
		}
		printf("allocation!!->\n");
		for(i=0;i<5;i++)
		{
			for(j=0;j<4;j++)
			{
				printf("%d ",allocation[i][j]);
			}
			printf("\n");
		}
		printf("need!!->\n");
		for(i=0;i<5;i++)
		{
			for(j=0;j<4;j++)
			{
				printf("%d ",need[i][j]);
			}
			printf("\n");
		}
		
			
	}
	
	}
	//printf("%s",command);
	/*printf("%d %d %d %d \n",resources[0],resources[1],resources[2],resources[3]);
	for(i=0;i<5;i++)
	{
		for(j=0;j<4;j++)
		{
			printf("%d ",maximum[i][j]);
		}
		printf("\n");
	}*/		
}


void bankerinit(int a[])
{
	int i,j,k;
	FILE *fp;
	char tmp[100][9];
	for(i=0; i<NUMBER_OF_CUSTOMERS; i++)
		for(j=0; j<NUMBER_OF_RESOURCES; j++)
			allocation[i][j]=0;
	for(i=0;i<NUMBER_OF_RESOURCES;i++)
		available[i]=a[i];
	
	fp = fopen("input", "r");
	i=0;
	//for(i=0;i<NUMBER_OF_CUSTOMERS;i++)
	while (fgets(tmp[i],80,fp))
	{
		//fgets(tmp,8,fp);
		//printf("%s",tmp[i]);
		for(j=0,k=0;j<8;j++)
		{
			if(tmp[i][j]>='0'&&tmp[i][j]<='9')
			{
				maximum[i][k]=tmp[i][j]-48;
				k++;
			}
			else
				continue;
				
		}
		i++;
	}
	for(i=0; i<NUMBER_OF_CUSTOMERS; i++)
		for(j=0; j<NUMBER_OF_RESOURCES; j++)
			need[i][j]=maximum[i][j]-allocation[i][j];
	fclose(fp);

}

int judge()
{
	int k,i,j;
	int used[5]={0};
	int flag=1;

	//int i,j;
	int COPYavailable[NUMBER_OF_RESOURCES];
	int COPYmaximum[NUMBER_OF_CUSTOMERS][NUMBER_OF_RESOURCES];
	int COPYallocation[NUMBER_OF_CUSTOMERS][NUMBER_OF_RESOURCES];
	int COPYneed[NUMBER_OF_CUSTOMERS][NUMBER_OF_RESOURCES];

	for(i=0;i<5;i++)
	{
		for(j=0;j<4;j++)
		{
			//COPYmaximum[i][j]=maximum[i][j];
			COPYallocation[i][j]=allocation[i][j];
			COPYneed[i][j]=need[i][j];
		}
	}
	for(i=0;i<4;i++)
		COPYavailable[i]=available[i];
	



	for(k=0;k<5;k++)
	{
		for(i=0;i<5;i++)
		{
			if(used[i])	continue;
			for(j=0;j<4;j++)
				if(need[i][j]>available[j])
				{
					flag=0;
					break;
				}
			if(flag!=0)
			{
				used[i]=1;
				for(j=0;j<4;j++)
				{
					available[j]+=allocation[i][j];
					//allocation[i][j]=0;
				}
					
			}
				
					
		}
	}
	for(k=0;k<5;k++)
		if(!used[k])	flag=0;





	for(i=0;i<5;i++)	//回档
		{
			for(j=0;j<4;j++)
			{
				//COPYmaximum[i][j]=maximum[i][j];
				allocation[i][j]=COPYallocation[i][j];
				need[i][j]=COPYneed[i][j];
			}
		}
		for(i=0;i<4;i++)
			available[i]=COPYavailable[i];

		
	

	return flag;
	
		
}

int request_resources(int customer_num, int request[])
{
	//请求失败后需要通过备份回滚
	int i,j;
	int COPYavailable[NUMBER_OF_RESOURCES];
	int COPYmaximum[NUMBER_OF_CUSTOMERS][NUMBER_OF_RESOURCES];
	int COPYallocation[NUMBER_OF_CUSTOMERS][NUMBER_OF_RESOURCES];
	int COPYneed[NUMBER_OF_CUSTOMERS][NUMBER_OF_RESOURCES];

	for(i=0;i<5;i++)
	{
		for(j=0;j<4;j++)
		{
			//COPYmaximum[i][j]=maximum[i][j];
			COPYallocation[i][j]=allocation[i][j];
			COPYneed[i][j]=need[i][j];
		}
	}
	for(i=0;i<4;i++)
		COPYavailable[i]=available[i];
	

	for(i=0;i<4;i++)
	{
		available[i]-=request[i];
		if(available[i]<0)
		{
			printf("你要那么多干嘛辣！辣你去找物管啊！");
			return -1;
		}
		allocation[customer_num][i]+=request[i];
		need[customer_num][i]-=request[i];	
	}
	if(judge())	return 0;
	else
	{
		for(i=0;i<5;i++)	//回档
		{
			for(j=0;j<4;j++)
			{
				//COPYmaximum[i][j]=maximum[i][j];
				allocation[i][j]=COPYallocation[i][j];
				need[i][j]=COPYneed[i][j];
			}
		}
		for(i=0;i<4;i++)
			available[i]=COPYavailable[i];

		return -1;
	
	}	


}
void release_resources(int customer_num, int release[])
{
	int i;
	for(i=0;i<4;i++)
	{
		available[i]+=release[i];
		allocation[customer_num][i]-=release[i];
		if(allocation[customer_num][i]<0)	{printf("无中生有不可取嗷铁汁");	break;}
		maximum[customer_num][i]-=release[i];
		//need[customer_num][i]-=request[i];	
	}
}
