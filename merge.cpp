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
    ListNode* mergeTwoLists(ListNode* list1, ListNode* list2) {
        /*ListNode* aux = new ListNode(0);
        ListNode* lista = aux;
        while (list1!=nullptr && list2!=nullptr) {
            if (list1->val<list2->val) {
                lista->next=list1;
                list1=list1->next;
            }
            else {
                lista->next=list2;
                list2=list2->next;
            }
            lista=lista->next;
        }
        if (list1!=nullptr) {
            lista->next=list1;
        }
        else {
            lista->next=list2;
        }
        lista = aux->next;
        return lista;
    }
    */
    
};
