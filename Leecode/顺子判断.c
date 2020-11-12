#include <stdlib.h>
#include <stdio.h>


bool isStraight(int* nums, int numsSize){
	int min=14,max=-1,counter=0,a[14]={0};
	for(int i = 0;i<numsSize;i++){
        a[nums[i]]++;
        if(a[nums[i]]>=2 && nums[i]) return false;
		if(min>nums[i])
            if(nums[i])
                min = nums[i];
		if(max<nums[i])
            if(nums[i])
                max = nums[i];
	}
	return 4>=(max-min);
	return false;
	
}

int main(){
 	  int nums[5];
	  while(1){
		for(int i=0;i<5;i++) scanf("%d",nums+i);
	  	printf("%d\n",isStraight(nums,5));
	  }
	  return 0;
} 
