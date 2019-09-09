#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <fcntl.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
//extern char ** environ;
void redirection(char **args)
{
	int i = 0,fd,fd2;
        while (args[i]) 
        {   
            if (*args[i] == '>' && strcmp(args[i],">>")!=0)
             {
                if ((fd = open (args[i+1], O_WRONLY | O_CREAT, S_IRUSR | S_IWUSR )) == -1) 
                {
                    perror (args[i+1]);
                    exit (0);
                }
                dup2 (fd, 1);
                //dup2 (fd, 2);
                close (fd);
                while (args[i])
                 {
                    args[i] = args[i+2];
                    i++; 
                }
                break;
            }
            
            else if(strcmp(args[i],">>")==0  && args[i+1])
            {
            	
            	if((fd2=open(args[i+1],O_WRONLY | O_APPEND, S_IRUSR | S_IWUSR))==-1)
            	{
            		perror (args[i+1]);
            		exit(0);
            	}
            	dup2(fd2,1);
            	close(fd2);
            	while (args[i])
                {
                    args[i] = args[i+2];
                    i++; 
                }
                break;
			
        }
        i++;

    }
}
           

int geten(char **args)
{
	pid_t pid;
	char * pt=args[1];
	
  
	//printf("%s\n",args[0] );
	if (strcmp(args[0] , "~HOME")==0 )
	{
	printf("bash: %s: is a directory \n",getenv("PWD") );
	return 1;
	}
	if (strcmp(args[0] ,"echo")==0 && args[1]!=NULL)
  {


	if (strcmp(args[1] ,"$PATH")==0 )
	{
	printf("PATH=%s\n",getenv("PATH") );
	return 1;
	}
	if (strcmp(args[1] ,"$HOME")==0 )
	{
		printf("HOME=%s\n",getenv("HOME") );
		return 1;
	}
	if (strcmp(args[1] ,"$USER")==0 )
	{
		printf("USER=%s\n",getenv("USER") );
		return 1;
	}
	if (strcmp(args[1] ,"$hostname")==0 )
	{
		printf("harshit-Inspiron-3558");
		return 1;
	}

	if (strcmp(args[1] ,"$PS1")==0 )
	{
		printf("\\u@h\\W]\\-> \n" );
		return 1;
	}

	if (strcmp(args[1] ,  "$PWD")==0 )
		{
		printf("%s\n",getenv("PWD") );
		return 1;
		}
	if (strcmp(args[1], "$$")==0)
	{
		printf("%d\n",getpid());
		return 1;
	}
		
		
	
    }

	if(strcmp(args[0],"open")==0 && (pt = strrchr(args[1],'.')) != NULL )
		 {
	     if(strcmp(pt,".mp4") == 0)
	      {
	     	execvp("vlc",args);
	     	pt=args[1];
	     	return 1;
		  
	      }

	      else if (strcmp(pt,".txt") == 0)
	      {
	      	execvp("subl",args);
	     	return 1;
	      }


	
		}
   return 0;

}

int seten(char **args)

{
	// if ((strcmp(args[1] ,"=")==0)  && args[2]!=NULL)
	// {
	// if(strcmp(args[0],"open")==0)
 //    	{
 //    		execvp("vlc",args);
    	
 //    	return 1;
    //}
	if (strcmp(args[0] ,"USER")==0 )
	{
	setenv("USER",args[2],1);
	return 1;
	}

	if (strcmp(args[0] ,"PATH")==0 )
	{
	setenv("PATH",args[2],1);
	return 1;
	}

	if (strcmp(args[0] ,"PWD")==0 )
	{
	setenv("PWD",args[2],1);
	return 1;
	}

	if (strcmp(args[0] ,"HOSTNAME")==0 )
	{
	setenv("HOSTNAME",args[2],1);
	return 1;
	}
// }

}

int status1;
char re[100];
char *cp[100];


int crt(char **args)
{

	if (strcmp(args[0],"alias")==0)
	{

		printf("++");
		re[0]=*args[1];
		
		printf("re:%s\n",re);
		for (int i=0;args[i+3]!=NULL;i++)
		cp[i]=args[i+3];
	return 1;

	 }
	// printf("+++");

	printf("args:%s\n",args[0] );
	printf("re:%s\n",re);
	
	printf("cp:%s\n",cp[0] );

	if(*args[0]==re[0])
	{
		printf("++++");
		pid_t pid;
   // pid = fork ();
    //int y=pid;
    


    // if (pid < 0) {
    //     perror ("fork");
        
    // }
    // else if (pid > 0) {
    //     while (wait (&status1) != pid)
    //         continue;
    // }
    // else if (pid == 0) {
  
        
        if (execvp (cp[0], cp) == -1) {
            perror ("execvp");
        }
   
        //exit (0);  
    return 1;                  
	}

	return 0;
}	





