/*
 * File:         threadSimult.c
 * Author:       Daniel O'Neil    B00753635
 * Date:         2020/07/05
 * Version:      1.0
 *
 * Purpose:      To demonstrate the concurrency of threads
 */


#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>
#include <unistd.h>
#include <semaphore.h>

//Global Variables
int sv=0;
int *changes;
sem_t mutex;


//The thread designed to implement semaphores, creating
//a synchronous thread environment
void *
thread_code_sync(void * p)
{
  int my_id = *(int *)p;
  printf("I am thread %d, starting up now\n",my_id);
  //The loop to read the variable sv and determine a course of action
  while(sv!=2)
    {
      if(sv==1)
	{
	  //Semaphore begins here
	  sem_wait(&mutex);
	  if(sv==1)
	    {
	      sv=0;
	      changes[my_id]++;
	    }
	  //Semaphore exits here
	  sem_post(&mutex);
	}
      else if(sv==0)
	{
	  usleep(10);
	}
    }
  //Printing out the specified output befoe closing
  printf("I am thread %d; I changed the value %d times\n",
	 my_id,changes[my_id]);
  return NULL;
}

void *
thread_code(void * p)
{
  int my_id = *(int *)p;
  printf("I am thread %d, starting up now\n",my_id);
  //The loop to read the variable sv and determine a course of action
  while(sv!=2)
    {
      if(sv==1)
        {
          if(sv==1)
            {
              sv=0;
              changes[my_id]++;
            }
        }
      else if(sv==0)
        {
          usleep(10);
        }
    }
  //Printing out the specified output befoe closing
  printf("I am thread %d; I changed the value %d times\n",my_id,changes[my_id]);
  return NULL;
}


int main(int argc, char * argv[])
{
  sem_init(&mutex,0,1);
  int threadCount=0;
  int iteration=0;
  char c;
  //Basic error checking to ensure proper input
  if(argc==3)
    {
      //Properly intaking the given variables
      if (sscanf(argv[1], "%d%c", &threadCount, &c) != 1
	  || threadCount <= 0)
	{
	  printf("Error: invalid arguments for Thread Count\n");
	  exit(1);
	}
      
      if (sscanf(argv[2], "%d%c", &iteration, &c) != 1
	  || iteration <= 0)
	{
	  printf("Error: invalid arguments for iterations\n");
	  exit(1);
	}
    }
  if (argc==4)
    {
      //Properly intaking the given variables
      if (sscanf(argv[2], "%d%c", &threadCount, &c) != 1
          || threadCount <= 0)
        {
          printf("Error: invalid arguments for Thread Count\n");
          exit(1);
        }
      
      if (sscanf(argv[3], "%d%c", &iteration, &c) != 1
          || iteration <= 0)
        {
          printf("Error: invalid arguments for iterations\n");
          exit(1);
        }
    }  
  

  //Gathering space for the threads and their IDs to exist
  pthread_t *threads =  malloc(sizeof(pthread_t)*threadCount);
  int *ids = malloc(sizeof(int)*threadCount);
  changes = malloc(sizeof(int)*threadCount);

  //Error checking to ensure that the malloc succeeded
  if(threads==NULL)
    {
      printf("Error: Malloc Failed\n");
      exit(1);
    }
  if(ids==NULL)
    {
      printf("Error: Malloc Failed\n");
      exit(1);
    }
  if(changes==NULL)
    {
      printf("Error: Malloc Failed\n");
      exit(1);
    }
			
  int ret;
  int count=0;

  //Creating the unique process IDs
  for(count=0;count<threadCount;count++)
    {
      ids[count]=count;    
    }
  //Creating the processes themselves
  //If arg == 3, does not engage sync methods
  if(argc==3)
    {
      for(count=0;count<threadCount;count++)
	{
	  ret = pthread_create(&(threads[count]), NULL, thread_code, (void *)&(ids[count]));
	  if(ret)
	    {
	      printf("Thread reated incorrectly\n");
	      exit(1);
	    }
	}
    }
  else{
    for(count=0;count<threadCount;count++)
      {
	ret = pthread_create(&(threads[count]), NULL, thread_code_sync, (void *)&(ids[count]));
	if(ret)
	  {
	    printf("Thread reated incorrectly\n");
	    exit(1);
	  }
      }
  }
  
  //Maintaining the loop where the main function and the threads flip sv
  sv=1;
  int progress=0;
  while(progress!=iteration)
    {
      if(sv==0)
	{
	  sv=1;
	  progress+=1;
	}
      else if(sv==1)
	{
	  usleep(10);
	}
    }
  sv=2;
  printf("main(): setting sv to 2 and joining the threads\n");
  fflush(stdout);
  sv=2;
  
  //Rejoining all created threads
  for(count=0;count<threadCount;count++)
    { 
      pthread_join(threads[count], NULL);
    }

  printf("main(): all the threads have finished\n");
  fflush(stdout);
  
  int sum=0;
  for(count=0;count<threadCount;count++)
    {
      sum = sum + changes[count];
    }
  //Printing the desired output
  printf("main(): I set sv to 1 %d times, the threads reset it %d times.\n",iteration,sum);
  
  //Freeing the allocated space for the arrays
  free(threads);
  free(ids);
  free(changes);
  sem_destroy(&mutex);
  
}