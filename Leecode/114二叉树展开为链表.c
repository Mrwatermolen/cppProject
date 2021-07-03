//给定一个二叉树，将它展开为一个单链表。
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */
#include <stdlib.h>

struct TreeNode
{
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
};

void flatten(struct TreeNode *root)
{
    void PostOrderList(struct TreeNode * root);
    PostOrderList(root);
}

//递归
void PostOrderList(struct TreeNode *root)
{
    if (root != NULL)
    {
        PostOrderList(root->left);
        PostOrderList(root->right);
        struct TreeNode *tmp;
        if (root->left != NULL)
        {
            tmp = root->left;
            while (tmp->right != NULL)
            {
                tmp = tmp->right;
            }
            tmp->right = root->right;
            root->right = root->left;
            root->left = NULL;
        }
    }
}

//找前序遍历的前驱
void PreNodeList(struct TreeNode *root)
{
    struct TreeNode *current = root;//先找root->right的前驱 再找root->left->right的前驱
    while (current != NULL)
    {

        if (current->left != NULL)
        {
            struct TreeNode *next = current->left;
            struct TreeNode *pre = next;

            while (pre->right != NULL)
            {
                pre = pre->right;
            }
            pre->right = current->right;
            current->left = NULL;
            current->right = next;
        }
        current = current->right;
    }
}
