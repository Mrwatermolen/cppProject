

//给你一个链表的头节点 head ，旋转链表，将链表每个节点向右移动 k 个位置。

/*
 * Definition for singly-linked list.

 */
struct ListNode
{
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};
class Solution
{
public:
    ListNode *rotateRight(ListNode *head, int k)
    {
        int lenght = 0, offset = 0;
        ListNode *pre, *cur = head;
        while (cur != nullptr)
        {
            ++lenght;
            pre = cur;
            cur = cur->next;
        }
        if (lenght == 0)
            return head;
        offset = k % lenght;
        if (offset == 0)
            return head;
        offset = lenght - offset;
        pre->next = head;
        cur = head;

        while (offset > 0)
        {
            --offset;
            pre = cur;
            cur = cur->next;
        }
        pre->next = nullptr;
        return cur;
    }
};