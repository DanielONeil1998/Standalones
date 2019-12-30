#include <stdio.h>
#include <stdlib.h>

//THIS PROGRAM WILL ONLY WORK CORRECTLY IF COMPILED IN C99

/* A happy number is a number of which the sum-of-squared-digits, if given sufficient iterations, will eventually
   lead back to 1. The first examples of this are 1,7,10,13, and 19.   */

int main(){

  int test,i,ans;
  
  printf("Enter how many number ranges are to be tested: ");
  scanf("%d",&test);

  int a[test];
  int b[test];

  int know[1000001];//0 means blank, 1 means happy, 2 means unhappy, 3 means waiting
  int num[1000001];//amt of happy numbers up to and including i

  know[1]=1;
  num[0]=0;

  //Gathering the information
printf("Enter a low bound, followed by a high bound\n");
 for(i=0;i!=test;i++){
   printf("");
   scanf("%d %d",&a[i],&b[i]);
  }

  for(i=1;i<=1000000;i++){
    know[i]=check((i),know);
    num[i]=num[i-1];
    if(know[i]==1){
      num[i]=num[i-1]+1;
    }else{
      num[i]=num[i-1];
    }
  }

  for(i=0;i!=test;i++){
    ans=(num[b[i]]-num[a[i]]);
    if(ans!=0){
      ans+=1;
    }
    printf("%d\n",ans);
  }

}

int check(int num,int *know){
  if(know[num]==1){
    return 1;
  }
  int sum=0;
  int rem=0;
  if(know[num]==0){
    know[num]=3;
    while(num!=0){
      rem=num%10;
      sum=sum+(rem*rem);
      num=(num-rem)/10;
    }
    know[sum] = check(sum,know);
    return know[sum];
  }
  if((know[num]==2)||(know[num]==3)){
    return 2;
  }
}
