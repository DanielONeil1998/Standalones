/* File:         pageReplace.c
 * Author:       Daniel O'Neil
 * Date:         19/07/2020
 * Version:      1.0
 * 
 * Purpose:      To simulate page replacement methods
 */

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>
#include <unistd.h>

//The values defined in the assignment
#define max_frame 2500

#define ref_string_length 10000

#define ref_length 5000

int main(int argc, char * argv[])
{

  //Variables declaring which algorithms are being used
  int num_frames = atoi(argv[1]);
  int optimal_faults = -1;
  int fifo_faults = -1;
  int lru_faults = -1;
  int lfu_faults = -1;
  int mfu_faults = -1;
  int second_chance_faults = -1;
  int i;

  //Basic error checking
  if (argc!=2) {
    printf("Error:Incorrect argument format\n");
    exit(1);
  }

  //Allocating space for the reference string
  int *ref_string = malloc(ref_length*sizeof(int));
  
  //Reading in the reference string
  i=0;
  while(scanf("%d",&ref_string[i])!= -1){
    i++;
  }
  int act_ref_length = i;
  
  //Method to simulate Most Frequently Used
  int mfu(int num_frames, int *ref_string, int act_ref_length)
  {
    int page_fault = 0;
    int memory_load = 0;
    //Setting up queue structures
    int *ref_queue = malloc(sizeof(int[num_frames]));
    int endpoint=0;
    int *pages = malloc(sizeof(int[5000]));
    int *usage = malloc(sizeof(int[5000]));
    int i,j,max;
    int maxPage=0;
    //Setting all inital array variables to 0
    for(i=0;i<5000;i++)
      {
        pages[i]=0;
        usage[i]=0;
      }
    //The simulation loop
    for(i=0;i<act_ref_length;i++)
      {

        //If the frames a re fully occupied
        if (memory_load == num_frames)
          {
            //Frames full, new entry
            if ((pages[ref_string[i]])==0)
              {
                page_fault++;
                pages[ref_string[i]]=1;
                max=0;
                maxPage=0;
                for(j=0;j<num_frames;j++)
                  {
                    if(usage[j]>=max)
                      {
                        if(usage[j]==max)
                          {
                            if(ref_queue[j]<maxPage)
                              {
                                maxPage=ref_queue[j];
                              }
                          }
			 else
                          {
                            maxPage=ref_queue[j];
                          }
                        max=usage[j];
                      }
                  }
                for(j=0;j<num_frames;j++)
                  {
                    if(usage[j]==max)
                      {
                        if(ref_queue[j]==maxPage)
                          {
                            pages[ref_queue[j]]=0;
                            ref_queue[j]=ref_string[i];
                            usage[j]=0;
                            j=num_frames;
                          }
                      }
                  }
              }
            //Frames full, recurring entry
            if ((pages[ref_string[i]])==1)
              {
                for(j=0;j!=num_frames;j++)
                  {
                    if(ref_queue[j]==ref_string[i])
                      {
                        usage[j]++;
                      }
                  }
              }
          }
        //Frames not full, new entry
	
        else if ((pages[ref_string[i]])==0)
          {
            memory_load++;
            page_fault++;
            pages[ref_string[i]]=1;
            ref_queue[endpoint]=ref_string[i];
            usage[endpoint]=1;
            endpoint = (endpoint + 1);
          }
        //Frames not full, recurring entry
        else if ((pages[ref_string[i]])==1)
          {
            for(j=0;j!=endpoint;j++)
              {
                if(ref_queue[j]==ref_string[i])
                  {
                    usage[j]++;
                  }
              }
          }
      }
    free(ref_queue);
    free(pages);
    free(usage);
    return page_fault;
  }
  
  //Method to simulate Least Frequently Used
  int lfu(int num_frames, int *ref_string, int act_ref_length)
  {
    int page_fault = 0;
    int memory_load = 0;
    //Setting up queue structures
    int *ref_queue = malloc(sizeof(int[num_frames]));
    int endpoint=0;
    int *pages = malloc(sizeof(int[5000]));
    int *usage = malloc(sizeof(int[5000]));
    int i,j,min;
    int minPage=5000;
    //Setting all inital array variables to 0
    for(i=0;i<5000;i++)
      {
        pages[i]=0;
        usage[i]=0;
      }  
    //The simulation loop
    for(i=0;i<act_ref_length;i++)
      {
	
        //If the frames a re fully occupied
        if (memory_load == num_frames)
          {
            //Frames full, new entry
            if ((pages[ref_string[i]])==0)
              {
                page_fault++;
                pages[ref_string[i]]=1;
                min=5000;
		minPage=5000;
                for(j=0;j<num_frames;j++)
                  {
                    if(usage[j]<=min)
                      {
			if(usage[j]==min)
			  {
			    if(ref_queue[j]<minPage)
			      {
				minPage=ref_queue[j];
			      }
			  }
			else
			  {
			    minPage=ref_queue[j];
			  }
			min=usage[j];
                      }
                  }
		for(j=0;j<num_frames;j++)
                  {
                    if(usage[j]==min)
                      {
			if(ref_queue[j]==minPage)
			  {
			    pages[ref_queue[j]]=0;
			    ref_queue[j]=ref_string[i];
			    usage[j]=0;
			    j=num_frames;
			  }
                      }
                  }
              }
            //Frames full, recurring entry
            if ((pages[ref_string[i]])==1)
              {
                for(j=0;j!=num_frames;j++)
                  {
                    if(ref_queue[j]==ref_string[i])
                      {
                        usage[j]++;
                      }
                  }
              }
          }
	//Frames not full, new entry
        else if ((pages[ref_string[i]])==0)
          {
            memory_load++;
            page_fault++;
            pages[ref_string[i]]=1;
            ref_queue[endpoint]=ref_string[i];
	    usage[endpoint]=1;
            endpoint = (endpoint + 1);
          }
        //Frames not full, recurring entry
        else if ((pages[ref_string[i]])==1)
          {
            for(j=0;j!=endpoint;j++)
              {
                if(ref_queue[j]==ref_string[i])
                  {
                    usage[j]++;
                  }
              }
          }
      }
    free(ref_queue);
    free(pages);
    free(usage);
    return page_fault;
  }
  
  //Method to simulate Least Recently Used
  int lru(int num_frames, int *ref_string, int act_ref_length)
  {
    int page_fault = 0;
    int memory_load = 0;
    //Setting up queue structures
    int *ref_queue = malloc(sizeof(int[num_frames]));
    int endpoint=0;
    int *pages = malloc(sizeof(int[5000]));
    int *time = malloc(sizeof(int[5000]));
    int i,j,max;
    //Setting all inital page variables to 0
    for(i=0;i<5000;i++)
      {
        pages[i]=0;
	time[i]=0;
      }
    //The simulation loop
    for(i=0;i<act_ref_length;i++)
      {
	//If the frames a re fully occupied
        if (memory_load == num_frames)
          {
	    //Frames full, new entry
            if ((pages[ref_string[i]])==0)
              {
                page_fault++;
                pages[ref_string[i]]=1;
		max=0;
		for(j=0;j<num_frames;j++)
		  {
		    if(time[j]>max)
		      {
			max=time[j];
		      }
		  }
		
		for(j=0;j<num_frames;j++)
		  {
		    if(time[j]==max)
		      {
			pages[ref_queue[j]]=0;
			ref_queue[j]=ref_string[i];
			time[j]=0;
			j=num_frames;
		      }
		  }
		for(j=0;j<num_frames;j++)
		  {
		    if(ref_queue[j]!=ref_string[i])
		      {
			time[j]++;
		      }
		  }
              }
	    //Frames full, recurring entry
	    if ((pages[ref_string[i]])==1)
	      {
		for(j=0;j!=num_frames;j++)
		  {
		    if(ref_queue[j]==ref_string[i])
		      {
			time[j]=0;
		      }
		    else
		      {
			time[j]++;
		      }
		  }
	      }
          }
	//Frames not full, new entry
	else if ((pages[ref_string[i]])==0)
          {
            memory_load++;
            page_fault++;
            pages[ref_string[i]]=1;
            ref_queue[endpoint]=ref_string[i];
	    for(j=0;j!=endpoint;j++)
	      {
		time[j]++;
	      }
            endpoint = (endpoint + 1);
          }
	//Frames not full, recurring entry
	else if ((pages[ref_string[i]])==1)
	  {
	    for(j=0;j!=endpoint;j++)
	      {
		if(ref_queue[j]==ref_string[i])
		  {
		    time[j]=0;
		  }
		else
		  {
		    time[j]++;
		  }
	      }
	  }
      }
    free(ref_queue);
    free(pages);
    free(time);
    return page_fault;
  }
  
  //Method to simulate First in First out
  int fifo(int num_frames, int *ref_string, int act_ref_length)
  {
    int page_fault = 0;
    int memory_load = 0;
    //Setting up queue structures
    int *ref_queue = malloc(num_frames*sizeof(int));
    int endpoint=0;
    int *pages = malloc(5000*sizeof(int));
    int i;
    //Setting all inital page variables to 0
    for(i=0;i<5000;i++)
      {
	pages[i]=0;
      }
    //The simulation loop
    for(i=0;i<act_ref_length;i++)
      {
	if (memory_load == num_frames)
	  {
	    if ((pages[ref_string[i]])==0)
	      {
		page_fault++;
		pages[ref_queue[endpoint]]=0;
		ref_queue[endpoint] = ref_string[i];
		pages[ref_string[i]]=1;
		endpoint = (endpoint + 1) % num_frames;
	      }
	  }
	else if ((pages[ref_string[i]])==0)
	  {
	    memory_load++;
	    page_fault++;
	    pages[ref_string[i]]=1;
	    ref_queue[endpoint]=ref_string[i];
	    endpoint = (endpoint + 1) % num_frames;
	  }
      }
    free(ref_queue);
    free(pages);
    return page_fault;
  }

  //Calling the replacement algorithms
  fifo_faults = fifo(num_frames, ref_string, act_ref_length);
  lru_faults = lru(num_frames, ref_string, act_ref_length);
  lfu_faults = lfu(num_frames, ref_string, act_ref_length);
  mfu_faults = mfu(num_frames, ref_string, act_ref_length);
  
  //Printing the requested output in proper format
  printf("For a system with %d frames:\n", num_frames);
  printf("Optimal page faults: %d\n", optimal_faults);
  printf("FIFO page faults: %d\n", fifo_faults);
  printf("LRU page faults: %d\n", lru_faults);
  printf("LFU page faults: %d\n", lfu_faults);
  printf("MFU page faults: %d\n", mfu_faults);
  printf("Second chance page faults: %d\n", second_chance_faults);

  //Freeing up requested memory
  free(ref_string);
  return EXIT_SUCCESS;
  
}