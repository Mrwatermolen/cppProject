#include <queue>
#include <iostream>
#include <vector>
//给你一个二叉树，请你返回其按 层序遍历 得到的节点值。 （即逐层地，从左到右访问所有节点）。

class Solution
{
public:
    vector<vector<int>> levelOrder(TreeNode *root)
    {
        int count = 0;
        queue<TreeNode *> q;
        vector<vector<int>> res;

        if (root == nullptr)
            return res;

        q.push(root);
        while (!q.empty())
        {
            count = q.size();
            vector<int> temp;
            while (count > 0)
            {
                TreeNode *f = q.front();
                temp.push_back(f->val);
                if (f->left != nullptr)
                    q.push(f->left);
                if (f->right != nullptr)
                    q.push(f->right);
                q.pop();
                --count;
            }
            res.push_back(temp);
        }
        return res;
    }
};