/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class Solution {
public:
    vector<double> averageOfLevels(TreeNode* root) {
        vector<double> res;
        queue<TreeNode *> q;
        q.push(root);
        while(!q.empty())
        {
            int counter = q.size();
            int n = counter;
            double sum = 0;
            while(counter-- > 0)
            {
                TreeNode* t = q.front();
                sum += double(t->val);
				if (t->left != nullptr)
				{
					q.push(t->left);
				}
				if (t->right != nullptr)
				{
					q.push(t->right);
				}
				q.pop();
            }
            res.push_back(sum / n);
        }
        return res;
    }
};