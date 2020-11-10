/*
 * File:       lowFuncShell.c
 * Author:     Daniel O'Neil
 * Date:       30/05/2020
 * Version:    1.0
 * 
 * Purpose:    This program emulates a low-functionality shell in which the user 
 *             writes inputs that they would write into a shell, and receive the 
 *             same output from this program.
 */


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>

void cmd(char *indiv_cmd_1[41]);
void twoCmd(char *indiv_cmd_1[41],char *indiv_cmd_2[41]);

int main(int argc,char *argv[])
{

  pid_t pid;
  char cmd_name[81];
  int active = 1;
  int two_cmds = 0;
  char *indiv_cmd_1[41];
  char *indiv_cmd_2[41];
  char *input;
  int waiting = 0;
  int i = 0;
  int j = 0;
  int status;
  int time_to_go = 0;
  size_t bufsize;
  char *buffer;
  
  while (active==1)
    {
      //Resetting all values needed to process input
      i=0;
      j=0;
      memset(&indiv_cmd_1[0],0,sizeof(indiv_cmd_1));
      memset(&indiv_cmd_2[0],0,sizeof(indiv_cmd_2));
      buffer = NULL;
      input = NULL;
      two_cmds = 0;
      //Taking user input and removing \n from user input
      printf("$ ");
      fflush(stdout);
      bufsize = getline(&buffer,&bufsize,stdin);
      if((buffer)[bufsize - 1] == '\n')
	{
	  (buffer)[bufsize - 1] = '\0';
	  --bufsize;
	}
      input = strtok(buffer, " ");
      while(input != NULL)
	{
	  //printf("Current Token: %s\n",input);
	  if(strcmp(input,"&")==0)
	    {
	      waiting = 1;
	      input = strtok(NULL, " ");
	    }
	  //Hardcoded "exit" function
	  else if(strcmp(input,"exit")==0)
	    {
	      active=0;
	      time_to_go = 1;
	      input = NULL;
	      break;
	      }
	  else if(strcmp(input,";")==0)
	    {
	      cmd(indiv_cmd_1);
	      memset(indiv_cmd_1,0,sizeof(indiv_cmd_1));
	      i=0;
	      input = strtok(NULL, " ");
	    }
	  //Statement to determine pipeline
	  else if(strcmp(input,"|")==0)
	    {
	      two_cmds=1;
	      input = strtok(NULL, " ");
	    }
	  //The actual command argument inputs
	  else
	    {
	      if(two_cmds==0)
		{
		  indiv_cmd_1[i] = input;
		  input = strtok(NULL, " ");
		  i++;
		}
	      else
		{
		  indiv_cmd_2[j] = input;
		  input = strtok(NULL," ");
		  j++;
		}
	    }
	}
      //Calling the functions to execute the commands
      if(two_cmds==0)
	{
	  cmd(indiv_cmd_1);
	}
      else{
	twoCmd(indiv_cmd_1,indiv_cmd_2);
      }
    }
}


//Method to perform a command non-pipelined command
void cmd(char *indiv_cmd_1[41])
{
  pid_t pid;
  pid = fork();
  if(pid<0)
    {
      printf("Error: Fork Failed\n");
      exit(-1);
    }
  else if(pid==0)
    {
      execvp(indiv_cmd_1[0],indiv_cmd_1);
      printf("Error: Invalid Input\n");
    }
  wait(NULL);
}


//Method to perform pipelined commands
void twoCmd(char *indiv_cmd_1[41],char *indiv_cmd_2[41])
{
  pid_t pid_1,pid_2;

  int proc[2];
  //Setting up the pipeline
  if(pipe(proc)<0)
    {
      printf("Error: Pipe failed\n");
    }

  //Executing the first command
  if(fork() == 0)
    {
      close(STDOUT_FILENO);
      dup(proc[1]);
      close(proc[0]);
      close(proc[1]);
      execvp(indiv_cmd_1[0],indiv_cmd_1);
      printf("Error: Invalid Input\n");
      exit(1);
    }

  //Executing the second command
  if(fork() == 0)
    {
      close(STDIN_FILENO);
      dup(proc[0]);
      close(proc[1]);
      close(proc[0]);
      execvp(indiv_cmd_2[0],indiv_cmd_2);
      printf("Error: Invalid Input\n");
      exit(1);
    }
  //Wrapping up the processes
  close(proc[0]);
  close(proc[1]);
  wait(0);
  wait(0);
}