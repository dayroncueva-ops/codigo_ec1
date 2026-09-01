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
    
    ListNode* swapPairs(ListNode* head) {
        if (head == nullptr || head->next == nullptr) {
            return head;
        }

        ListNode* primero = head;
        ListNode* segundo = head->next;
        ListNode* siguiente = segundo->next;
        ListNode* anterior = nullptr;

        while (primero != nullptr && segundo != nullptr) {

            // Intercambiar el par
            segundo->next = primero;
            primero->next = siguiente;

            // Conectar con el par anterior
            if (anterior != nullptr) {
                anterior->next = segundo;
            }
            else {
                // Es el primer par, así que cambia el head
                head = segundo;
            }

            // Avanzar al siguiente par
            anterior = primero;
            primero = siguiente;

            if (primero != nullptr) {
                segundo = primero->next;

                if (segundo != nullptr) {
                    siguiente = segundo->next;
                }
            }
        }

        return head;
    }
};
