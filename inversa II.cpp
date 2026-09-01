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
class Solution {
public:
    ListNode* reverseBetween(ListNode* head, int left, int right) {
        if (head==nullptr || head->next==nullptr) {return head;}
        else if (left==right) {return head;}
        else {
            ListNode* dummy = new ListNode (0);
            dummy->next = head;
            ListNode* anterior = dummy; // en caso left sea 1
            ListNode* temp = head;
            ListNode* after = head;
            
            for(int i=1;i<left;i++) {
                anterior=anterior->next;    
            }
            temp = anterior->next;

            for (int i=1;i<=right;i++) {
                after = after->next;
            }
            ListNode* prev = after;
            ListNode* actual = temp;
            
            while (actual!=after) {
                ListNode* next = actual->next;
                actual->next = prev;
                prev= actual;
                actual=next;
            }
            // prev ahora es la cabeza del inverso
            anterior->next = prev;
            return dummy->next;
        }
    }
};
