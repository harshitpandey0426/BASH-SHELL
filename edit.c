#include<stdio.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
int status;
char *morefunction[] = {"cd","exit"};
int k=sizeof(morefunction) / sizeof(char *);


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
int (*builtin_func[]) (char **) = {&cdsh, &exitsh};

int strt(char **args)
{
  pid_t pid;
  
  pid = fork();
  if (pid == 0) {
    
    if (execvp(args[0], args) == -1)
      perror("lsh");

    exit(0);
  } 
  else if (pid < 0)
    perror("str");

  else {
    
    do {
         waitpid(pid, &status, WUNTRACED);
       } 
    while (!WIFEXITED(status) ); //&& !WIFSIGNALED(status)
    //wait(NULL);
  }

  return 1;
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

  do {
  	char cwd[1024]; 
    getcwd(cwd, sizeof(cwd)); 
    printf("harshit@harshit-Inspiron-3558%s$ ", cwd); 
    char **args;
     char *line = NULL;
  ssize_t bufsize = 1024; 
  getline(&line, &bufsize, stdin);
     
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
  status = execute(args);

    free(line);
    free(args);
  } while (status);
  }