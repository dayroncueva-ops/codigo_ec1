#include <iostream>
using namespace std;

template <typename T>
struct NodoD {
    T dato;
    NodoD<T>* sig;
    NodoD<T>* ant;
    NodoD(T val) : dato(val), sig(nullptr), ant(nullptr) {}
};

template <typename T>
class ListaDoble {
private:
    NodoD<T>* cabeza;
    NodoD<T>* cola;
    int tam;

public:
    ListaDoble() : cabeza(nullptr), cola(nullptr), tam(0) {}
    ~ListaDoble() { vaciar(); }

    bool estaVacia() const { return tam == 0; }
    int tamanio() const { return tam; }

    // ---------- INSERCIONES ----------
    void insertarInicio(T val) {
        NodoD<T>* nuevo = new NodoD<T>(val);
        if (tam == 0) {
            cabeza = cola = nuevo;
        } else {
            nuevo->sig = cabeza;
            cabeza->ant = nuevo;
            cabeza = nuevo;
        }
        tam++;
    }

    void insertarFinal(T val) {
        NodoD<T>* nuevo = new NodoD<T>(val);
        if (tam == 0) {
            cabeza = cola = nuevo;
        } else {
            nuevo->ant = cola;
            cola->sig = nuevo;
            cola = nuevo;
        }
        tam++;
    }

    bool insertarEnPosicion(int pos, T val) {
        if (pos < 0 || pos > tam) return false;
        if (pos == 0) { insertarInicio(val); return true; }
        if (pos == tam) { insertarFinal(val); return true; }

        NodoD<T>* actual = obtenerNodo(pos);
        NodoD<T>* nuevo = new NodoD<T>(val);
        NodoD<T>* previo = actual->ant;

        nuevo->sig = actual;
        nuevo->ant = previo;
        previo->sig = nuevo;
        actual->ant = nuevo;
        tam++;
        return true;
    }

    // ---------- ELIMINACIONES ----------
    bool eliminarInicio() {
        if (tam == 0) return false;
        NodoD<T>* temp = cabeza;
        cabeza = cabeza->sig;
        if (cabeza != nullptr) cabeza->ant = nullptr;
        else cola = nullptr;
        delete temp;
        tam--;
        return true;
    }

    bool eliminarFinal() {
        if (tam == 0) return false;
        NodoD<T>* temp = cola;
        cola = cola->ant;
        if (cola != nullptr) cola->sig = nullptr;
        else cabeza = nullptr;
        delete temp;
        tam--;
        return true;
    }

    bool eliminarEnPosicion(int pos) {
        if (pos < 0 || pos >= tam) return false;
        if (pos == 0) return eliminarInicio();
        if (pos == tam - 1) return eliminarFinal();

        NodoD<T>* actual = obtenerNodo(pos);
        actual->ant->sig = actual->sig;
        actual->sig->ant = actual->ant;
        delete actual;
        tam--;
        return true;
    }

    bool eliminarValor(T val) {
        NodoD<T>* actual = cabeza;
        while (actual != nullptr) {
            if (actual->dato == val) {
                if (actual == cabeza) return eliminarInicio();
                if (actual == cola) return eliminarFinal();
                actual->ant->sig = actual->sig;
                actual->sig->ant = actual->ant;
                delete actual;
                tam--;
                return true;
            }
            actual = actual->sig;
        }
        return false;
    }

    // Elimina el nodo apuntado directamente en O(1) REAL.
    // Como tenemos ->ant y ->sig, no hace falta ningun truco ni busqueda.
    bool eliminarNodo(NodoD<T>* nodo) {
        if (nodo == nullptr || tam == 0) return false;
        if (nodo == cabeza) return eliminarInicio();
        if (nodo == cola) return eliminarFinal();
        nodo->ant->sig = nodo->sig;
        nodo->sig->ant = nodo->ant;
        delete nodo;
        tam--;
        return true;
    }

    void vaciar() {
        while (!estaVacia()) eliminarInicio();
    }

    // ---------- BUSQUEDA / ACCESO ----------
    NodoD<T>* obtenerNodo(int pos) const {
        if (pos < 0 || pos >= tam) return nullptr;
        NodoD<T>* actual;
        // recorre desde el extremo mas cercano
        if (pos <= tam / 2) {
            actual = cabeza;
            for (int i = 0; i < pos; i++) actual = actual->sig;
        } else {
            actual = cola;
            for (int i = tam - 1; i > pos; i--) actual = actual->ant;
        }
        return actual;
    }

    T& obtener(int pos) const {
        NodoD<T>* n = obtenerNodo(pos);
        if (n == nullptr) throw out_of_range("Posicion invalida");
        return n->dato;
    }

    int buscar(T val) const {
        NodoD<T>* actual = cabeza;
        int idx = 0;
        while (actual != nullptr) {
            if (actual->dato == val) return idx;
            actual = actual->sig;
            idx++;
        }
        return -1;
    }

    bool contiene(T val) const { return buscar(val) != -1; }

    // ---------- UTILIDADES ----------
    void invertir() {
        NodoD<T>* actual = cabeza;
        NodoD<T>* temp = nullptr;
        while (actual != nullptr) {
            temp = actual->ant;
            actual->ant = actual->sig;
            actual->sig = temp;
            actual = actual->ant; // avanza al "siguiente" original
        }
        temp = cabeza;
        cabeza = cola;
        cola = temp;
    }

    T obtenerMaximo() const {
        if (tam == 0) throw out_of_range("Lista vacia");
        T maxVal = cabeza->dato;
        NodoD<T>* actual = cabeza->sig;
        while (actual != nullptr) {
            if (actual->dato > maxVal) maxVal = actual->dato;
            actual = actual->sig;
        }
        return maxVal;
    }

    T obtenerMinimo() const {
        if (tam == 0) throw out_of_range("Lista vacia");
        T minVal = cabeza->dato;
        NodoD<T>* actual = cabeza->sig;
        while (actual != nullptr) {
            if (actual->dato < minVal) minVal = actual->dato;
            actual = actual->sig;
        }
        return minVal;
    }

    void ordenar() {
        if (tam < 2) return;
        bool huboSwap = true;
        while (huboSwap) {
            huboSwap = false;
            NodoD<T>* actual = cabeza;
            while (actual->sig != nullptr) {
                if (actual->dato > actual->sig->dato) {
                    swap(actual->dato, actual->sig->dato);
                    huboSwap = true;
                }
                actual = actual->sig;
            }
        }
    }

    void imprimirAdelante() const {
        NodoD<T>* actual = cabeza;
        cout << "[ ";
        while (actual != nullptr) {
            cout << actual->dato << " ";
            actual = actual->sig;
        }
        cout << "] (tam=" << tam << ")" << endl;
    }

    void imprimirAtras() const {
        NodoD<T>* actual = cola;
        cout << "[ ";
        while (actual != nullptr) {
            cout << actual->dato << " ";
            actual = actual->ant;
        }
        cout << "] (tam=" << tam << ")" << endl;
    }
};

// ---------------- DEMO / PRUEBAS ----------------
int main() {
    ListaDoble<int> lista;

    lista.insertarFinal(10);
    lista.insertarFinal(20);
    lista.insertarFinal(30);
    lista.insertarInicio(5);
    lista.insertarEnPosicion(2, 15);
    cout << "Adelante: "; lista.imprimirAdelante();
    cout << "Atras:    "; lista.imprimirAtras();

    lista.eliminarEnPosicion(2);
    cout << "Tras eliminar pos 2: "; lista.imprimirAdelante();

    cout << "Buscar 20 -> indice: " << lista.buscar(20) << endl;

    lista.invertir();
    cout << "Invertida: "; lista.imprimirAdelante();

    cout << "Maximo: " << lista.obtenerMaximo() << " | Minimo: " << lista.obtenerMinimo() << endl;

    lista.ordenar();
    cout << "Ordenada: "; lista.imprimirAdelante();

    lista.eliminarValor(20);
    cout << "Tras eliminar valor 20: "; lista.imprimirAdelante();

    lista.vaciar();
    cout << "Vacia? " << (lista.estaVacia() ? "Si" : "No") << endl;

    return 0;
}
