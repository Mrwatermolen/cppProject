/*
给定一个二叉树，检查它是否是镜像对称的。
*/
struct TreeNode
{
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
};

bool isSymmetric(struct TreeNode *root)
{
    bool isSame(struct TreeNode * l, struct TreeNode * r);

    if (root == NULL)
        return true;
    return isSame(root->left, root->right);
}

bool isSame(struct TreeNode *l, struct TreeNode *r)
{
    if (l == r)
        return true;
    if (l == NULL || r == NULL || l->val != r->val)
        return false;
    return isSame(l->left, r->right) && isSame(l->right, r->left);
}