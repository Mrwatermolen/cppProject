#include <stdio.h>
#include <stdlib.h>

int* maxSlidingWindow(int* nums, int numsSize, int k, int* returnSize){
    int end = numsSize - k,max = nums[0],j=0;
    returnSize = (int *)malloc(sizeof(int)*(end+1));
	for(int i=0;i<=end;i++){
		if(max==nums[i]){
			
		}
		for(int j=0;j<k;j++)
			if(nums[i+j]>max) max=nums[i+j];
        returnSize[i] = max;
        printf("%d\n",max);
	}
    return returnSize;
}
    

int main(){
	int num[]={1,3,-1,-3,5,3,6,7};
	int *p;
	p = maxSlidingWindow(num,8,3,p);
	printf("%d",*p);
	
	return 0;
}
