#include <iostream>
#include <string>

struct Nodo {
    long long val;
    Nodo* next;
    std::string nombre;
    Nodo(long long val, Nodo* next, std::string nombre)
        : val(val), next(next), nombre(nombre) {}
};

class Lista {
private:
    Nodo* head;
    Nodo* tail;

public:
    Lista() : head(nullptr), tail(nullptr) {}

    bool vacia() const {
        return head == nullptr;
    }

    void push(long long n, std::string nombre) {
        Nodo* no = new Nodo(n, nullptr, nombre);
        if (head == nullptr) {
            head = no;
            tail = no;
            no->next = no;
        } else {
            no->next = head;
            tail->next = no;
            tail = no;
        }
    }

    Nodo* pop() {
        Nodo* frente = head;
        if (head == tail) {
            head = nullptr;
            tail = nullptr;
        } else {
            head = head->next;
            tail->next = head;
        }
        frente->next = nullptr;
        return frente;
    }

    void leer() {
        if (head == nullptr) return;

        Nodo* actual = head;
        do {
            std::cout << actual->nombre << " " << actual->val << "\n";
            actual = actual->next;
        } while (actual != head);
    }

    void Round_robin(long long q) {
        long long reloj = 0;
        while (!vacia()) {
            Nodo* actual = pop();

            if (actual->val <= q) {
                reloj += actual->val;
                std::cout << actual->nombre << " " << reloj << "\n";
            } else {
                long long restante = actual->val - q;
                reloj += q;
                push(restante, actual->nombre);
            }

            delete actual;
        }
    }
};

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n;
    long long q;
    std::cin >> n >> q;

    Lista L;
    for (int i = 0; i < n; i++) {
        std::string nombre;
        long long tiempo;
        std::cin >> nombre >> tiempo;
        L.push(tiempo, nombre);
    }

    L.Round_robin(q);

    return 0;
}