#include <iostream>
using namespace std;

template <typename T>
struct Nodo {
    T dato;
    Nodo<T>* sig;
    Nodo(T val) : dato(val), sig(nullptr) {}
};

template <typename T>
class ListaSimple {
private:
    Nodo<T>* cabeza;
    Nodo<T>* cola;
    int tam;

public:
    ListaSimple() : cabeza(nullptr), cola(nullptr), tam(0) {}

    ~ListaSimple() { vaciar(); }

    bool estaVacia() const { return tam == 0; }
    int tamanio() const { return tam; }

    // ---------- INSERCIONES ----------
    void insertarInicio(T val) {
        Nodo<T>* nuevo = new Nodo<T>(val);
        nuevo->sig = cabeza;
        cabeza = nuevo;
        if (tam == 0) cola = nuevo;
        tam++;
    }

    void insertarFinal(T val) {
        Nodo<T>* nuevo = new Nodo<T>(val);
        if (tam == 0) {
            cabeza = cola = nuevo;
        } else {
            cola->sig = nuevo;
            cola = nuevo;
        }
        tam++;
    }

    // pos entre 0 y tam (0 = inicio, tam = final)
    bool insertarEnPosicion(int pos, T val) {
        if (pos < 0 || pos > tam) return false;
        if (pos == 0) { insertarInicio(val); return true; }
        if (pos == tam) { insertarFinal(val); return true; }

        Nodo<T>* actual = cabeza;
        for (int i = 0; i < pos - 1; i++) actual = actual->sig;

        Nodo<T>* nuevo = new Nodo<T>(val);
        nuevo->sig = actual->sig;
        actual->sig = nuevo;
        tam++;
        return true;
    }

    // ---------- ELIMINACIONES ----------
    bool eliminarInicio() {
        if (tam == 0) return false;
        Nodo<T>* temp = cabeza;
        cabeza = cabeza->sig;
        delete temp;
        tam--;
        if (tam == 0) cola = nullptr;
        return true;
    }

    bool eliminarFinal() {
        if (tam == 0) return false;
        if (tam == 1) return eliminarInicio();

        Nodo<T>* actual = cabeza;
        while (actual->sig != cola) actual = actual->sig;
        delete cola;
        cola = actual;
        cola->sig = nullptr;
        tam--;
        return true;
    }

    bool eliminarEnPosicion(int pos) {
        if (pos < 0 || pos >= tam) return false;
        if (pos == 0) return eliminarInicio();
        if (pos == tam - 1) return eliminarFinal();

        Nodo<T>* actual = cabeza;
        for (int i = 0; i < pos - 1; i++) actual = actual->sig;

        Nodo<T>* aEliminar = actual->sig;
        actual->sig = aEliminar->sig;
        delete aEliminar;
        tam--;
        return true;
    }

    // elimina la primera ocurrencia de val
    bool eliminarValor(T val) {
        if (tam == 0) return false;
        if (cabeza->dato == val) return eliminarInicio();

        Nodo<T>* actual = cabeza;
        while (actual->sig != nullptr && actual->sig->dato != val)
            actual = actual->sig;

        if (actual->sig == nullptr) return false; // no encontrado

        Nodo<T>* aEliminar = actual->sig;
        actual->sig = aEliminar->sig;
        if (aEliminar == cola) cola = actual;
        delete aEliminar;
        tam--;
        return true;
    }

    void vaciar() {
        while (!estaVacia()) eliminarInicio();
    }

    // ---------- BUSQUEDA / ACCESO ----------
    int buscar(T val) const {
        Nodo<T>* actual = cabeza;
        int idx = 0;
        while (actual != nullptr) {
            if (actual->dato == val) return idx;
            actual = actual->sig;
            idx++;
        }
        return -1; // no encontrado
    }

    bool contiene(T val) const { return buscar(val) != -1; }

    // devuelve por referencia; lanza si no existe
    T& obtener(int pos) const {
        if (pos < 0 || pos >= tam) throw out_of_range("Posicion invalida");
        Nodo<T>* actual = cabeza;
        for (int i = 0; i < pos; i++) actual = actual->sig;
        return actual->dato;
    }

    // ---------- UTILIDADES ----------
    void invertir() {
        Nodo<T>* prev = nullptr;
        Nodo<T>* actual = cabeza;
        cola = cabeza;
        while (actual != nullptr) {
            Nodo<T>* sigTemp = actual->sig;
            actual->sig = prev;
            prev = actual;
            actual = sigTemp;
        }
        cabeza = prev;
    }

    T obtenerMaximo() const {
        if (tam == 0) throw out_of_range("Lista vacia");
        T maxVal = cabeza->dato;
        Nodo<T>* actual = cabeza->sig;
        while (actual != nullptr) {
            if (actual->dato > maxVal) maxVal = actual->dato;
            actual = actual->sig;
        }
        return maxVal;
    }

    T obtenerMinimo() const {
        if (tam == 0) throw out_of_range("Lista vacia");
        T minVal = cabeza->dato;
        Nodo<T>* actual = cabeza->sig;
        while (actual != nullptr) {
            if (actual->dato < minVal) minVal = actual->dato;
            actual = actual->sig;
        }
        return minVal;
    }

    // ordenamiento simple por intercambio (bubble sort sobre nodos)
    void ordenar() {
        if (tam < 2) return;
        bool huboSwap = true;
        while (huboSwap) {
            huboSwap = false;
            Nodo<T>* actual = cabeza;
            while (actual->sig != nullptr) {
                if (actual->dato > actual->sig->dato) {
                    swap(actual->dato, actual->sig->dato);
                    huboSwap = true;
                }
                actual = actual->sig;
            }
        }
    }

    void imprimir() const {
        Nodo<T>* actual = cabeza;
        cout << "[ ";
        while (actual != nullptr) {
            cout << actual->dato << " ";
            actual = actual->sig;
        }
        cout << "] (tam=" << tam << ")" << endl;
    }
};

// ---------------- DEMO / PRUEBAS ----------------
int main() {
    ListaSimple<int> lista;

    lista.insertarFinal(10);
    lista.insertarFinal(20);
    lista.insertarFinal(30);
    lista.insertarInicio(5);
    lista.insertarEnPosicion(2, 15);
    cout << "Lista tras inserciones: ";
    lista.imprimir();

    lista.eliminarEnPosicion(2);
    cout << "Tras eliminar pos 2: ";
    lista.imprimir();

    cout << "Buscar 20 -> indice: " << lista.buscar(20) << endl;
    cout << "Contiene 100? " << (lista.contiene(100) ? "Si" : "No") << endl;

    lista.invertir();
    cout << "Lista invertida: ";
    lista.imprimir();

    cout << "Maximo: " << lista.obtenerMaximo() << endl;
    cout << "Minimo: " << lista.obtenerMinimo() << endl;

    lista.ordenar();
    cout << "Lista ordenada: ";
    lista.imprimir();

    lista.eliminarValor(20);
    cout << "Tras eliminar valor 20: ";
    lista.imprimir();

    lista.vaciar();
    cout << "Vacia? " << (lista.estaVacia() ? "Si" : "No") << endl;

    return 0;
}
