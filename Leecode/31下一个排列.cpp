#include <vector>
using namespace std;
/*
实现获取 下一个排列 的函数，算法需要将给定数字序列重新排列成字典序中下一个更大的排列。
如果不存在下一个更大的排列，则将数字重新排列成最小的排列（即升序排列）。
必须原地修改，只允许使用额外常数空间。
*/
class Solution {
public:
    void nextPermutation(vector<int>& nums) {
        if( nums.size() <= 1)
        {
            return;
        }
        int len = nums.size();
        int i = len - 2, j = len - 1, k = len - 1;
        while(i>=0 && nums[i] >= nums[j])
        {
            --i,--j;
        }
        if(i >= 0)
        {
            while(k > i && nums[i]>=nums[k])
            {
                --k;
            }
            int temp = nums[i];
            nums[i] = nums[k];
            nums[k] = temp;
        }
            for(int l = j, o = len - 1; o > l; --o,++l)
            {
                int temp = nums[l];
                nums[l] = nums[o];
                nums[o] = temp;                
            }
    }
};