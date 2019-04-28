#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdlib.h>
#include <string.h>
//#include <readlline/readline.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <fcntl.h>


#define MAX_LINE 80



void get_input(char *input,char *a[])
{
	//char **command = malloc((MAX_LINE/2+1)*sizeof(char*));
	char *separator =" \n";
	char *parsed;
	int index=0;
	parsed=strtok(input,separator);
	while(parsed!=NULL){
		a[index]=parsed;
		index++;
		parsed=strtok(NULL,separator);
	}
	a[index]=NULL;
	//return command;
}



int main(void)
{
	pid_t pid = 0;
	

		
	//char **pastargs;
	//char *pastargs[MAX_LINE/2+1];
	char *args[MAX_LINE/2+1];
	int should_run = 1;
	char *command;
	char commandPlus[256];
	char *pargs[MAX_LINE/2+1];
	pargs[0]=NULL;
	
	while(should_run){

		
		printf("osh>");
		fflush(stdout);
		
		command=(char*)malloc(sizeof(char)*256);
		fgets(command,255,stdin);
		//strcpy(commandPlus,command);
		
		if(command[0]==command[1]&&command[1]=='!'){	
			get_input(command,args);
			for(int i=0;pargs[i];i++)
				printf("%s",pargs[i]);
			printf("\n");
		
		//printf("%s",commandPlus);
			
		}
		else
		{
			strcpy(commandPlus,command);
			get_input(command,args);
			get_input(commandPlus,pargs);
			//printf("%s",pargs[0]);
		}
		pid = fork();
		if (pid < 0){
			fprintf(stderr, "Fork Failed");
			return 1;
		}
		else if (pid == 0){   //haven't deleted '&'
			int index;
			int index1=0;
			int sign=0;
			int fd;
			for(index=0;args[index];index++)
			{
				if(!strcmp(args[index],">")){
					
					sign=1;
					index1=index;
					fflush(stdout);
					fd=open(args[index+1],O_RDWR|O_CREAT);
					
					//args[index]=NULL;
					//printf("%s",args[0]);
					
					
					
				}
				if(!strcmp(args[index],"<")){
					
					sign=2;
					index1=index;
					fd=open(args[index+1],O_RDWR|O_CREAT);
					//dup2(fd,STDIN_FILENO);
					
				}
				
				if(!strcmp(args[index],"|")){

					pid_t npid=0;
					char *newargs[MAX_LINE/2+1];
					int i=0;
					int j=0;
					int fda[2];	//0 for read
					//for( ;strcpy(args[i],"|")!=0;i++);
					args[index]=NULL;
					i=index+1;
					for(j=0;args[i];i++,j++){
						newargs[j]=args[i];
					}
					newargs[j]=NULL;
					pipe(fda);
					npid = fork();
					if(npid>0)	//father
					{	
						close(fda[0]);
						//dup2(fda[1],STDOUT_FILENO);
						execvp(args[0],args);
						close(fda[1]);
						
					}
					else	//child
					{	
						close(fda[1]);
						dup2(fda[0],STDIN_FILENO);
						execvp(newargs[0],newargs);
						close(fda[0]);
					}
					
				}
			}
			if(sign!=0)
				args[index1]=NULL;
			if(!strcmp(args[index-1],"&"))
				args[index-1]=NULL;	//delete successfully

			if(!strcmp(args[0],"!!")){
				if(pargs[0]){
					printf("%s",commandPlus);
					
					int Index;
					for(Index=0;pargs[Index];Index++);
					if(!strcmp(pargs[Index-1],"&"))
						pargs[Index-1]=NULL;	//delete successfully again
					execvp(pargs[0],pargs);
				}
				else
					printf("There is no history!\n");
				}

			else
			{	
				
				if(sign==1)
				{
					dup2(fd,STDOUT_FILENO);
				}
				if(sign==2)
				{
					dup2(fd,STDIN_FILENO);
				}
				execvp(args[0],args);
				
			}
			
			
		}
			
		else{

			int flag=1;
			for(int i=1;args[i]!=NULL;i++)
				if(args[i][0]=='&'){
					flag=0;
					break;
				}
			if(flag==1)	wait(NULL);

		}
		free(command);
		}
	return 0;
}


	
