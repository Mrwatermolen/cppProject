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
    TreeNode *mergeTrees(TreeNode *root1, TreeNode *root2)
    {
        return dfs(root1, root2);
    }
    TreeNode *dfs(TreeNode *root1, TreeNode *root2)
    {
        if (root1 != nullptr && root2 != nullptr)
        {
            TreeNode *res = new TreeNode;
            res->val = root1->val + root2->val;
            res->left = dfs(root1->left, root2->left);
            res->right = dfs(root1->right, root2->right);
            return res;
        }
        else if (root1 != nullptr)
        {
            TreeNode *res = new TreeNode;
            res->val = root1->val;
            res->left = dfs(root1->left, root2);
            res->right = dfs(root1->right, root2);
            return res;
        }
        else if (root2 != nullptr)
        {
            TreeNode *res = new TreeNode;
            res->val = root2->val;
            res->left = dfs(root1, root2->left);
            res->right = dfs(root1, root2->right);
            return res;
        }
        else
        {
            return nullptr;
        }
    }
};