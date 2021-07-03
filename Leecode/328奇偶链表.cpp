/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode() : val(0), next(nullptr) {}
 *     ListNode(int x) : val(x), next(nullptr) {}
 *     ListNode(int x, ListNode *next) : val(x), next(next) {}
 * };
 */
class Solution
{
public:
    ListNode *oddEvenList(ListNode *head)
    {
        if (head == nullptr)
            return nullptr;

        ListNode *p = head;
        ListNode *insert, *n, *nextInsert, *nextN;
        n = head->next;
        if (n == nullptr)
            return head;
        insert = n->next;
        nextN = n;

        while (insert != nullptr)
        {
            ListNode *tmp = insert->next;
            if (tmp != nullptr)
            {
                nextInsert = tmp->next;
            }
            else
            {
                nextInsert = nullptr;
            }

            p->next = insert;

            insert->next = n;
            nextN->next = tmp;
            p = insert;
            insert = nextInsert;
            nextN = tmp;
        }

        return head;
    }
};