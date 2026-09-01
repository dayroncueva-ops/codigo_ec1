#include <iostream>
using namespace std;

template <typename T>
struct NodoCD {
    T dato;
    NodoCD<T>* sig;
    NodoCD<T>* ant;
    NodoCD(T val) : dato(val), sig(nullptr), ant(nullptr) {}
};

// "cabeza" apunta al primer nodo. cabeza->ant es la cola,
// y cola->sig es la cabeza (doble circularidad).
template <typename T>
class ListaCircularDoble {
private:
    NodoCD<T>* cabeza;
    int tam;

    NodoCD<T>* cola() const { return (tam == 0) ? nullptr : cabeza->ant; }

public:
    ListaCircularDoble() : cabeza(nullptr), tam(0) {}
    ~ListaCircularDoble() { vaciar(); }

    bool estaVacia() const { return tam == 0; }
    int tamanio() const { return tam; }

    // ---------- INSERCIONES ----------
    void insertarInicio(T val) {
        NodoCD<T>* nuevo = new NodoCD<T>(val);
        if (tam == 0) {
            nuevo->sig = nuevo;
            nuevo->ant = nuevo;
            cabeza = nuevo;
        } else {
            NodoCD<T>* ultimo = cola();
            nuevo->sig = cabeza;
            nuevo->ant = ultimo;
            ultimo->sig = nuevo;
            cabeza->ant = nuevo;
            cabeza = nuevo;
        }
        tam++;
    }

    void insertarFinal(T val) {
        if (tam == 0) { insertarInicio(val); return; }
        NodoCD<T>* nuevo = new NodoCD<T>(val);
        NodoCD<T>* ultimo = cola();
        nuevo->ant = ultimo;
        nuevo->sig = cabeza;
        ultimo->sig = nuevo;
        cabeza->ant = nuevo;
        tam++;
    }

    bool insertarEnPosicion(int pos, T val) {
        if (pos < 0 || pos > tam) return false;
        if (pos == 0) { insertarInicio(val); return true; }
        if (pos == tam) { insertarFinal(val); return true; }

        NodoCD<T>* actual = obtenerNodo(pos);
        NodoCD<T>* previo = actual->ant;
        NodoCD<T>* nuevo = new NodoCD<T>(val);

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
        if (tam == 1) {
            delete cabeza;
            cabeza = nullptr;
            tam = 0;
            return true;
        }
        NodoCD<T>* viejaCabeza = cabeza;
        NodoCD<T>* ultimo = cola();
        cabeza = cabeza->sig;
        cabeza->ant = ultimo;
        ultimo->sig = cabeza;
        delete viejaCabeza;
        tam--;
        return true;
    }

    bool eliminarFinal() {
        if (tam == 0) return false;
        if (tam == 1) return eliminarInicio();

        NodoCD<T>* ultimo = cola();
        NodoCD<T>* nuevoUltimo = ultimo->ant;
        nuevoUltimo->sig = cabeza;
        cabeza->ant = nuevoUltimo;
        delete ultimo;
        tam--;
        return true;
    }

    bool eliminarEnPosicion(int pos) {
        if (pos < 0 || pos >= tam) return false;
        if (pos == 0) return eliminarInicio();
        if (pos == tam - 1) return eliminarFinal();

        NodoCD<T>* actual = obtenerNodo(pos);
        actual->ant->sig = actual->sig;
        actual->sig->ant = actual->ant;
        delete actual;
        tam--;
        return true;
    }

    bool eliminarValor(T val) {
        if (tam == 0) return false;
        NodoCD<T>* actual = cabeza;
        for (int i = 0; i < tam; i++) {
            if (actual->dato == val) {
                if (actual == cabeza) return eliminarInicio();
                if (actual == cola()) return eliminarFinal();
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

    void vaciar() {
        while (!estaVacia()) eliminarInicio();
    }

    // ---------- BUSQUEDA / ACCESO ----------
    NodoCD<T>* obtenerNodo(int pos) const {
        if (pos < 0 || pos >= tam) return nullptr;
        NodoCD<T>* actual;
        if (pos <= tam / 2) {
            actual = cabeza;
            for (int i = 0; i < pos; i++) actual = actual->sig;
        } else {
            actual = cola();
            for (int i = tam - 1; i > pos; i--) actual = actual->ant;
        }
        return actual;
    }

    T& obtener(int pos) const {
        NodoCD<T>* n = obtenerNodo(pos);
        if (n == nullptr) throw out_of_range("Posicion invalida");
        return n->dato;
    }

    int buscar(T val) const {
        if (tam == 0) return -1;
        NodoCD<T>* actual = cabeza;
        for (int i = 0; i < tam; i++) {
            if (actual->dato == val) return i;
            actual = actual->sig;
        }
        return -1;
    }

    bool contiene(T val) const { return buscar(val) != -1; }

    // ---------- UTILIDADES ----------
    void invertir() {
        if (tam < 2) return;
        NodoCD<T>* actual = cabeza;
        for (int i = 0; i < tam; i++) {
            NodoCD<T>* temp = actual->sig;
            actual->sig = actual->ant;
            actual->ant = temp;
            actual = temp;
        }
        cabeza = cabeza->sig; // la cabeza pasa a ser el antiguo ultimo
    }

    T obtenerMaximo() const {
        if (tam == 0) throw out_of_range("Lista vacia");
        NodoCD<T>* actual = cabeza;
        T maxVal = actual->dato;
        for (int i = 1; i < tam; i++) {
            actual = actual->sig;
            if (actual->dato > maxVal) maxVal = actual->dato;
        }
        return maxVal;
    }

    T obtenerMinimo() const {
        if (tam == 0) throw out_of_range("Lista vacia");
        NodoCD<T>* actual = cabeza;
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
            NodoCD<T>* actual = cabeza;
            for (int i = 0; i < tam - 1; i++) {
                if (actual->dato > actual->sig->dato) {
                    swap(actual->dato, actual->sig->dato);
                    huboSwap = true;
                }
                actual = actual->sig;
            }
        }
    }

    void imprimirAdelante() const {
        cout << "[ ";
        if (tam > 0) {
            NodoCD<T>* actual = cabeza;
            for (int i = 0; i < tam; i++) {
                cout << actual->dato << " ";
                actual = actual->sig;
            }
        }
        cout << "] (tam=" << tam << ", circular)" << endl;
    }

    void imprimirAtras() const {
        cout << "[ ";
        if (tam > 0) {
            NodoCD<T>* actual = cola();
            for (int i = 0; i < tam; i++) {
                cout << actual->dato << " ";
                actual = actual->ant;
            }
        }
        cout << "] (tam=" << tam << ", circular)" << endl;
    }
};

// ---------------- DEMO / PRUEBAS ----------------
int main() {
    ListaCircularDoble<int> lista;

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
