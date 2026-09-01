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

ListNode* partition(ListNode* head, int x) {
    ListNode* menores = new ListNode(0);
    ListNode* mayores = new ListNode(0);

    ListNode* menor = menores;
    ListNode* mayor = mayores;

    while (head != nullptr) {
        if (head->val < x) {
            menor->next = head;
            menor = menor->next;
        } else {
            mayor->next = head;
            mayor = mayor->next;
        }

        head = head->next;
    }

    mayor->next = nullptr;
    menor->next = mayores->next;

    ListNode* resultado = menores->next;

    delete menores;
    delete mayores;

    return resultado;
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
    ListNode* head = new ListNode(1);
    head->next = new ListNode(4);
    head->next->next = new ListNode(3);
    head->next->next->next = new ListNode(2);
    head->next->next->next->next = new ListNode(5);
    head->next->next->next->next->next = new ListNode(2);

    int x = 3;

    head = partition(head, x);

    imprimir(head);

    return 0;
}
