/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */


struct TreeNode* buildTree(int* preorder, int preorderSize, int* inorder, int inorderSize){
    if(preorderSize < 1) return NULL;

    int index = -1;
    
    struct TreeNode* root = (struct TreeNode*)malloc(sizeof(struct TreeNode));
    root->val = preorder[0];
    root->left = root->right = NULL;
    for(int i = 0; i < inorderSize; ++i)
    {
        if(inorder[i] == preorder[0])
        {
            index = i;
            break;
        }
    }
    if(index == -1) return NULL;
    int lLenght = index;
    int rLength = inorderSize - 1 - index;
    root->left = buildTree((preorder+1), lLenght, (inorder+index-lLenght), lLenght);
    root->right = buildTree((preorder+1+lLenght), rLength, (inorder+index+1), rLength);
    return root;
}