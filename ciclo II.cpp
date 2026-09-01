/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
class Solution {
public:
    ListNode *detectCycle(ListNode *head) {
        if (head==nullptr || head->next==nullptr) {return nullptr;}
        ListNode* lento = head;
        ListNode* fast  =head;

        while (fast!=nullptr && fast->next!=nullptr ){
            fast = fast->next->next;
            lento=lento->next;
            if (fast==lento) {
                ListNode* inicio = head;
                while(inicio!=lento) {
                    inicio=inicio->next;
                    lento=lento->next;
                }
                return inicio;
            }
          
        }
        return nullptr;
    }
};
