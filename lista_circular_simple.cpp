#include <iostream>
using namespace std;

template <typename T>
struct NodoCS {
    T dato;
    NodoCS<T>* sig;
    NodoCS(T val) : dato(val), sig(nullptr) {}
};

// En esta implementacion "cola" siempre apunta al ultimo nodo,
// y cola->sig siempre apunta a la cabeza (por eso es circular).
template <typename T>
class ListaCircularSimple {
private:
    NodoCS<T>* cola; // referencia principal; cola->sig = cabeza
    int tam;

    NodoCS<T>* cabeza() const { return (tam == 0) ? nullptr : cola->sig; }

public:
    ListaCircularSimple() : cola(nullptr), tam(0) {}
    ~ListaCircularSimple() { vaciar(); }

    bool estaVacia() const { return tam == 0; }
    int tamanio() const { return tam; }

    // ---------- INSERCIONES ----------
    void insertarInicio(T val) {
        NodoCS<T>* nuevo = new NodoCS<T>(val);
        if (tam == 0) {
            nuevo->sig = nuevo;
            cola = nuevo;
        } else {
            nuevo->sig = cola->sig;
            cola->sig = nuevo;
        }
        tam++;
    }

    void insertarFinal(T val) {
        insertarInicio(val);
        cola = cola->sig; // el nuevo nodo pasa a ser la cola
    }

    bool insertarEnPosicion(int pos, T val) {
        if (pos < 0 || pos > tam) return false;
        if (pos == 0) { insertarInicio(val); return true; }
        if (pos == tam) { insertarFinal(val); return true; }

        NodoCS<T>* actual = cabeza();
        for (int i = 0; i < pos - 1; i++) actual = actual->sig;

        NodoCS<T>* nuevo = new NodoCS<T>(val);
        nuevo->sig = actual->sig;
        actual->sig = nuevo;
        tam++;
        return true;
    }

    // ---------- ELIMINACIONES ----------
    bool eliminarInicio() {
        if (tam == 0) return false;
        if (tam == 1) {
            delete cola;
            cola = nullptr;
            tam = 0;
            return true;
        }
        NodoCS<T>* viejaCabeza = cabeza();
        cola->sig = viejaCabeza->sig;
        delete viejaCabeza;
        tam--;
        return true;
    }

    bool eliminarFinal() {
        if (tam == 0) return false;
        if (tam == 1) return eliminarInicio();

        NodoCS<T>* actual = cabeza();
        while (actual->sig != cola) actual = actual->sig;
        actual->sig = cola->sig; // apunta a la cabeza
        delete cola;
        cola = actual;
        tam--;
        return true;
    }

    bool eliminarEnPosicion(int pos) {
        if (pos < 0 || pos >= tam) return false;
        if (pos == 0) return eliminarInicio();
        if (pos == tam - 1) return eliminarFinal();

        NodoCS<T>* actual = cabeza();
        for (int i = 0; i < pos - 1; i++) actual = actual->sig;

        NodoCS<T>* aEliminar = actual->sig;
        actual->sig = aEliminar->sig;
        delete aEliminar;
        tam--;
        return true;
    }

    bool eliminarValor(T val) {
        if (tam == 0) return false;
        if (cabeza()->dato == val) return eliminarInicio();

        NodoCS<T>* actual = cabeza();
        for (int i = 0; i < tam - 1; i++) {
            if (actual->sig->dato == val) {
                NodoCS<T>* aEliminar = actual->sig;
                if (aEliminar == cola) return eliminarFinal();
                actual->sig = aEliminar->sig;
                delete aEliminar;
                tam--;
                return true;
            }
            actual = actual->sig;
        }
        return false;
    }

    void vaciar() {
        while (!estaVacia()) eliminarInicio();
    }

    // ---------- BUSQUEDA / ACCESO ----------
    int buscar(T val) const {
        if (tam == 0) return -1;
        NodoCS<T>* actual = cabeza();
        for (int i = 0; i < tam; i++) {
            if (actual->dato == val) return i;
            actual = actual->sig;
        }
        return -1;
    }

    bool contiene(T val) const { return buscar(val) != -1; }

    T& obtener(int pos) const {
        if (pos < 0 || pos >= tam) throw out_of_range("Posicion invalida");
        NodoCS<T>* actual = cabeza();
        for (int i = 0; i < pos; i++) actual = actual->sig;
        return actual->dato;
    }

    // ---------- UTILIDADES ----------
    void invertir() {
        if (tam < 2) return;
        NodoCS<T>* prev = cola; // se conecta al final para mantener circularidad
        NodoCS<T>* actual = cabeza();
        NodoCS<T>* viejaCabeza = actual;
        for (int i = 0; i < tam; i++) {
            NodoCS<T>* sigTemp = actual->sig;
            actual->sig = prev;
            prev = actual;
            actual = sigTemp;
        }
        cola = viejaCabeza; // la vieja cabeza ahora es la cola
    }

    T obtenerMaximo() const {
        if (tam == 0) throw out_of_range("Lista vacia");
        NodoCS<T>* actual = cabeza();
        T maxVal = actual->dato;
        for (int i = 1; i < tam; i++) {
            actual = actual->sig;
            if (actual->dato > maxVal) maxVal = actual->dato;
        }
        return maxVal;
    }

    T obtenerMinimo() const {
        if (tam == 0) throw out_of_range("Lista vacia");
        NodoCS<T>* actual = cabeza();
        T minVal = actual->dato;
        for (int i = 1; i < tam; i++) {
            actual = actual->sig;
            if (actual->dato < minVal) minVal = actual->dato;
        }
        return minVal;
    }

    void ordenar() {
        if (tam < 2) return;
        bool huboSwap = true;
        while (huboSwap) {
            huboSwap = false;
            NodoCS<T>* actual = cabeza();
            for (int i = 0; i < tam - 1; i++) {
                if (actual->dato > actual->sig->dato) {
                    swap(actual->dato, actual->sig->dato);
                    huboSwap = true;
                }
                actual = actual->sig;
            }
        }
    }

    // recorre "vueltas" veces empezando desde la cabeza (util para
    // problemas tipo "el elemento que le sigue a Josefo", etc.)
    void imprimir() const {
        cout << "[ ";
        if (tam > 0) {
            NodoCS<T>* actual = cabeza();
            for (int i = 0; i < tam; i++) {
                cout << actual->dato << " ";
                actual = actual->sig;
            }
        }
        cout << "] (tam=" << tam << ", circular)" << endl;
    }
};

// ---------------- DEMO / PRUEBAS ----------------
int main() {
    ListaCircularSimple<int> lista;

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

    lista.invertir();
    cout << "Invertida: ";
    lista.imprimir();

    cout << "Maximo: " << lista.obtenerMaximo() << " | Minimo: " << lista.obtenerMinimo() << endl;

    lista.ordenar();
    cout << "Ordenada: ";
    lista.imprimir();

    lista.eliminarValor(20);
    cout << "Tras eliminar valor 20: ";
    lista.imprimir();

    lista.vaciar();
    cout << "Vacia? " << (lista.estaVacia() ? "Si" : "No") << endl;

    return 0;
}
