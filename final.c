
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <fcntl.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdbool.h>


#include "final.h"

int status;

char *morefunction[] = {"cd","exit","history"};

int k=sizeof(morefunction) / sizeof(char *);
void pipex4(char ** argv,int i);
bool parsepipe(char **args);
void pipex1(char **argv);


int cdsh(char **args)
{
  if (args[1] == NULL) {
    printf("harshit: expected argument to \"cd\"\n");
  } else {
    if (chdir(args[1]) != 0) 
    { 
      perror("harshit");
    }
  }
  return 1;
}

int exitsh(char **args)
{
  return 0;
}


void hist(char ** args)
{
	char sentence[1000];
   FILE *fptr;
   fptr = fopen("history.txt", "a");
   if(fptr == NULL)
   {
      printf("Error!");
      exit(1);
   }
   
   //printf("Enter a sentence:\n");
   //gets(sentence);
   for(int i=0;args[i];i++)
   fprintf(fptr,"%s ", args[i]);
	fprintf(fptr,"%s\n", "");

   fclose(fptr);
}
int historysh(char **args)
{
FILE *fptr;
    char filename[10000];
    char ch;
 
    fptr = fopen("history.txt", "r");
    if (fptr == NULL)
    {
        printf("Cannot open file \n");
        exit(0);
    }
    ch = fgetc(fptr);
    while (ch != EOF)
    {
        printf ("%c", ch);
        ch = fgetc(fptr);
    }
    fclose(fptr);
    return 1;
}


int (*builtin_func[]) (char **) = {&cdsh, &exitsh,&historysh};

int strt(char **args)
{
    pid_t pid;
    hist(args);
    pid = fork ();
    int y=pid;
    


    if (pid < 0) {
        perror ("fork");
        
    }
    else if (pid > 0) {
        while (wait (&status) != pid)
            continue;
    }
    else if (pid == 0) {
    	
    	 int k=crt(args);
    	if (k==1)
    		return 1;
 
    	int sid = setsid();
    	signal (SIGHUP, SIG_IGN);
    	 //pipex(args);
    	
	int x=geten(args);
    	if (x==1)
    		return 1;
    	int y=seten(args);
    	if (y==1)
    		return 1;
    	


    	redirection(args);
        
        if (execvp (args[0], args) == -1) {
            perror ("execvp");
        }
        exit (0);  
    } 
    return 1;                  
}




// 

void tokengen(char **args)
{//char **tok;
	printf("%s+\n",args[1]);
	
	// char *c = " ";
	// int flag =0;
	char **tok=(char**)malloc(sizeof(char**)*100);

	for(int i=0;i<100;i++)
  	tok[i]=(char*)malloc(sizeof(char**)*100);

	int k=0;
	int i=0;
	char *v[]={" "};
	while(args[i])
	{//printf("%s\n", );
		if(strcmp(args[i],"|")!=0)
		{
			strcat(tok[k], args[i]);

			
				strcat(tok[k],v[0]);
				i++;
				continue;
				
			
		}
		else if(strcmp(args[i],"|")==0)
		{
			
			i++;
			k++;
			continue;
		}
		//i++;

	}
	tok[i]=NULL;

	printf("%s",tok[1]);
	//pipex4(tok,i);
	int l=0;
	// while(tok[l])
	// {
	//printf("%s\n",tok[3]);
	l++;
	//}
}

void tokengen1(char *line)
{
	char *str[1024];
	int k=0;
	int i=0;
	
         	char temp[100];
         	//strcpy(temp,args[i]);	
         	int index=0;
         	char*ptr =strtok(line,"|");
         	while(ptr !=NULL)
         	{
         		str[index]=ptr;
         		ptr=strtok(NULL,"|");
         		index++;
         	}
         	printf("%d",index);
         	str[index]=NULL;
         	int l=0;
         	// 	while(str[l])
         	// 	{
         	 //printf("%s\n",str[2]);
         	// l++;
         	// }
         	pipex4(str,index);
         // k++;
         // i++;

	
}


void pipex4(char ** argc,int i )
{
	//int i;
	printf("++");

	char *line[100];
	line[0]=argc[i-1];
 //  	str1[i]=(char*)malloc(sizeof(char)*100);
	
	//char **args;

	int k=0;
	printf("%d@",k);
	int m=0;
    while(argc[m])
    {
     
        int pd[2];
        pipe(pd);

	pid_t pid1=fork();
        if (pid1==0)
        {
         	int bsize = 100000; 
    int pos = 0;
   char **extra = malloc(bsize * sizeof(char*));
  char *token; 
  char **backext;


  if (!extra)
   {
    printf("An error occured in allocation\n");
    exit(0);
   }

 //printf("%s",line);

  //token = strtok(line, " \t\r\n\a");
  
  while (token != NULL) 
  {

    extra[pos] = token;
    pos++;

    if (pos >= bsize) 
    {
      bsize =bsize + 1024;
      backext = extra;
     extra = realloc(extra, bsize * sizeof(char*));
      if (!extra) 
      {
        free(backext);
        printf("An error occured in allocation\n");
        exit(0);
      }
    }
    token = strtok(NULL, " \t\r\n\a");
  }
  extra[pos] = NULL;
  char **args = extra;

         	
         	wait(NULL);
            dup2(pd[1], 1); 
            close(pd[0]);
            //execvp(str[0], str);
            perror("exec4");
            abort();

        }
        else
        {
        	//while(wait(NULL)>0);
        	wait(NULL);
        }

        
        dup2(pd[0], 0);
        close(pd[1]);
        m++;
    }
    

    execvp(line[0], line);
    perror("execstr1");
    abort();
}

bool parsepipe(char **args)
{
	int i=0;
	while (args[i]) 
        {   
            if (*args[i] == '|' && *args[i+1])
            {
            	return 1;
            }
            i++;
        }   
        return 0; 
}




int execute(char **args)
{
  int i;

  if (args[0] == NULL)
    return 1;
  
  for (i = 0; i < k; i++)
   {
    if (strcmp(args[0], morefunction[i]) == 0)
      return (*builtin_func[i])(args);
  }

  return strt(args);  
}


int main(int argc, char **argv)
{
	//Fstr(SIGINT, SIG_IGN);

  do {
  	char cwd[1024]; 
    getcwd(cwd, sizeof(cwd)); 
    printf("harshit@harshit-Inspiron-3558%s-> ", cwd); 
    char **args;
     char *line = NULL;
  ssize_t bufsize = 1024; 
  getline(&line, &bufsize, stdin);
  //printf("initial line:%s\n",line);
  //tokengen1(line);  

     
  int bsize = 100000; 
    int pos = 0;
   char **extra = malloc(bsize * sizeof(char*));
  char *token; 
  char **backext;


  if (!extra)
   {
    printf("An error occured in allocation\n");
    exit(0);
   }

 //printf("%s",line);

  token = strtok(line, " \t\r\n\a");
  
  while (token != NULL) 
  {

    extra[pos] = token;
    pos++;

    if (pos >= bsize) 
    {
      bsize =bsize + 1024;
      backext = extra;
     extra = realloc(extra, bsize * sizeof(char*));
      if (!extra) 
      {
        free(backext);
        printf("An error occured in allocation\n");
        exit(0);
      }
    }
    token = strtok(NULL, " \t\r\n\a");
  }
  extra[pos] = NULL;
  args = extra;
  


 
 
  //tokengen1(line);
  //printf("%s\n",args[0] );
  

 status = execute(args);

    free(line);
    free(args);
  } while (status);

}
  
