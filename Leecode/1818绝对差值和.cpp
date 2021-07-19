#include <vector>
#include<algorithm>
using namespace std;

class Solution {
public:
    int minAbsoluteSumDiff(vector<int>& nums1, vector<int>& nums2) {
        vector<int> temp(nums1);
        sort(temp.begin(),temp.end());
        int offset = 0, sum = 0;
        for(int i = 0; i < nums1.size(); ++i)
        {
            int add = abs(nums1[i]-nums2[i]);
            sum = (sum + add)%100000007;
            int j = lower_bound(temp.begin(),temp.end(),nums2[i]) - temp.begin();
            if(j < nums1.size())
            {
                offset = max(offset,add - (temp[j] - nums2[i]));
            }
            if(j > 0)
            {
                offset = max(offset,add - ( nums2[i] - temp[j-1]));
            }
        }
        
        return (sum - offset + 100000007)%100000007;
    }
};