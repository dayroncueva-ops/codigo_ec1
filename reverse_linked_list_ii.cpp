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

ListNode* reverseBetween(ListNode* head, int left, int right) {
    if (head == nullptr || left == right) {
        return head;
    }

    ListNode* dummy = new ListNode(0);
    dummy->next = head;

    ListNode* anterior = dummy;

    for (int i = 1; i < left; i++) {
        anterior = anterior->next;
    }

    ListNode* actual = anterior->next;

    for (int i = 0; i < right - left; i++) {
        ListNode* siguiente = actual->next;

        actual->next = siguiente->next;
        siguiente->next = anterior->next;
        anterior->next = siguiente;
    }

    head = dummy->next;
    delete dummy;

    return head;
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

    int left = 2;
    int right = 4;

    head = reverseBetween(head, left, right);

    imprimir(head);

    return 0;
}
