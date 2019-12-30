#include <stdlib.h>
#include <stdio.h>

//THIS PROGRAM WILL ONLY WORK CORRECTLY IF COMPILED IN C99

/* This program will find the maximum surface area a singular strictly rectangular billboard
   could occupy upon the walls of adjacent buildings, given their height and width in order */

void main(){

  int num,i,j,k,ch,cw,ans;

  printf("Enter number of buildings: ");
  scanf("%d",&num);

  int height[num];
  int width[num];
  int sizeleft[num];
  int sizeright[num];
  int sizemid[num];

  //Gathering the data on the skyscrapers
  printf("Enter building dimensions in sequence(Height Width): ");
  for(i=0;i!=num;i++){
    scanf("%d %d",&height[i],&width[i]);
  }

  //Checking constarint boards
  for(i=0;i!=num;i++){
    j=i;
    k=i+1;
    sizemid[i]=0;
    while(height[j]>=height[i]){
      sizemid[i]+=(height[i]*width[j]);
      j-=1;
    }
    while(height[k]>=height[i]){
      sizemid[i]+=(height[i]*width[k]);
      k+=1;
    }
  }

  //Determining the largest billboard
  ans=0;
  for(i=0;i!=num;i++){
    if(sizemid[i]>ans){
      ans=sizemid[i];
    }
  }

  printf("Largest billboard surface area: %d\n",ans);
}
