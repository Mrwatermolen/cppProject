using namespace std;
struct TreeNode
{
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};
class Solution
{
public:
    int res;
    int diameterOfBinaryTree(TreeNode *root)
    {
        res = 0;
        dfs(root);
        return res;
    }
    int dfs(TreeNode *root)
    {
        if (root != nullptr)
        {
            int l = dfs(root->left) + 1; //每遍历一个非空结点就+1，边数=非空结点数-1
            int r = dfs(root->right) + 1;
            res = max(res, r + l);
            return max(l, r);
        }
        return -1; //空结点返回-1
    }
};