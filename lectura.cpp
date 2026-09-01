struct ListNode {
    string name;
    int time;
    ListNode* next;

    ListNode(string n, int t) {
        name = n;
        time = t;
        next = nullptr;
    }
};
ListNode* head = nullptr;
ListNode* tail = nullptr;

for (int i = 0; i < n; i++) {
    string name;
    int time;

    cin >> name >> time;

    ListNode* nuevo = new ListNode(name, time);

    if (head == nullptr) {
        head = nuevo;
        tail = nuevo;
    }
    else {
        tail->next = nuevo;
        tail = nuevo;
    }
}
resolver(head,  q);
