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

ListNode* rotateRight(ListNode* head, int k) {
    if (head == nullptr || head->next == nullptr || k == 0) {
        return head;
    }

    int n = 1;
    ListNode* last = head;

    while (last->next != nullptr) {
        last = last->next;
        n++;
    }

    k = k % n;

    if (k == 0) {
        return head;
    }

    last->next = head;

    int pasos = n - k;
    ListNode* nuevoFinal = last;

    while (pasos--) {
        nuevoFinal = nuevoFinal->next;
    }

    ListNode* nuevoInicio = nuevoFinal->next;
    nuevoFinal->next = nullptr;

    return nuevoInicio;
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
    head->next = new ListNode(2);
    head->next->next = new ListNode(3);
    head->next->next->next = new ListNode(4);
    head->next->next->next->next = new ListNode(5);

    int k = 2;

    head = rotateRight(head, k);

    imprimir(head);

    return 0;
}
