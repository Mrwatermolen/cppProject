/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */
class Solution {
private:
    int result = INT_MIN;
public:

    int maxPathSum(TreeNode* root) {
        dfs(root);
        return result;
    }

    int dfs(TreeNode* root)
    {
        if(root == nullptr) return 0;
        int l = dfs(root->left);
        int r = dfs(root->right);

        int maxChild = max(l,r);
        int maxVal = max(root->val, root->val + maxChild);
        result = max(result,maxVal);
        int routeVal = root->val + r + l;
        int maxRouteVal = max(maxVal,routeVal);
        result = max(maxRouteVal,result);
        return maxVal;
    }
};