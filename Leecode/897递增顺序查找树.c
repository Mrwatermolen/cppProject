
//Definition for a binary tree node.
struct TreeNode
{
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
};

struct TreeNode *increasingBST(struct TreeNode *root)
{
    void InOrder(struct TreeNode * p, struct TreeNode * nT[], int *counter);
    int *counter = (int *)malloc(sizeof(int));
    *counter = 0;
    struct TreeNode *nT[101];
    InOrder(root, nT, counter);
    nT[*counter] = NULL;
    for (int i = 0; i < (*counter); ++i)
    {
        nT[i]->right = nT[i + 1];
        nT[i]->left = NULL;
    }

    return nT[0];
}

void InOrder(struct TreeNode *p, struct TreeNode *nT[], int *counter)
{
    if (p != NULL)
    {
        InOrder(p->left, nT, counter);
        nT[*counter] = p;
        (*counter)++;
        InOrder(p->right, nT, counter);
    }
}