#include <iostream>
using namespace std;

struct ListNode {
    int val;
    ListNode* next;

    ListNode(int x) {
        val = x;
        next = nullptr;
    }
};

ListNode* mezclar(ListNode* a, ListNode* b) {
    ListNode* dummy = new ListNode(0);
    ListNode* actual = dummy;

    while (a != nullptr && b != nullptr) {
        if (a->val <= b->val) {
            actual->next = a;
            a = a->next;
        } else {
            actual->next = b;
            b = b->next;
        }

        actual = actual->next;
    }

    if (a != nullptr) {
        actual->next = a;
    } else {
        actual->next = b;
    }

    ListNode* resultado = dummy->next;
    delete dummy;

    return resultado;
}

ListNode* sortList(ListNode* head) {
    if (head == nullptr || head->next == nullptr) {
        return head;
    }

    ListNode* lento = head;
    ListNode* rapido = head->next;

    while (rapido != nullptr && rapido->next != nullptr) {
        lento = lento->next;
        rapido = rapido->next->next;
    }

    ListNode* mitad = lento->next;
    lento->next = nullptr;

    ListNode* izquierda = sortList(head);
    ListNode* derecha = sortList(mitad);

    return mezclar(izquierda, derecha);
}

void imprimir(ListNode* head) {
    while (head != nullptr) {
        cout << head->val;
        if (head->next != nullptr) {
            cout << " -> ";
        }
        head = head->next;
    }
    cout << endl;
}

int main() {
    ListNode* head = new ListNode(4);
    head->next = new ListNode(2);
    head->next->next = new ListNode(1);
    head->next->next->next = new ListNode(3);

    head = sortList(head);

    imprimir(head);

    return 0;
}
