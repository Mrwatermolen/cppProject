/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };对比一下 124二叉树中的最大路径和
 */
class Solution {
public:
    int rob(TreeNode* root) {
        vector<int> result = DoOrDonot(root);
        return max(result[0],result[1]);
    }

    vector<int> DoOrDonot(TreeNode* root)
    {
        if(root == nullptr)
        {
            vector<int> val(2,0); 
            return val;
        }

        vector<int> result(2,0);
        vector<int> l = DoOrDonot(root->left);
        vector<int> r = DoOrDonot(root->right);

        result[0] = root->val + l[1] + r[1];
        result[1] = max(l[0],l[1]) + max(r[0],r[1]);
        return result;
    } 
};