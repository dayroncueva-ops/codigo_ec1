#include <iostream>
#include <list>
#include <vector>
using namespace std;

/*
    E. Cajas

    Tenemos n cajas inicialmente ordenadas:
    1 2 3 ... n

    Hay 4 comandos:

    1 X Y -> mover X inmediatamente a la izquierda de Y
    2 X Y -> mover X inmediatamente a la derecha de Y
    3 X Y -> intercambiar X e Y
    4     -> invertir toda la linea

    Al final debemos sumar las cajas que quedan en posiciones impares.

    La idea principal es usar una lista doblemente enlazada (std::list).

    Cada caja tiene asociado un iterador. Esto permite encontrar
    directamente la posicion de una caja sin recorrer toda la lista.

    Para los comandos 1 y 2:
    - Se elimina X.
    - Se vuelve a insertar antes o despues de Y.
    - std::list::erase e insert trabajan en tiempo O(1).

    Para el comando 3:
    - Se intercambian los valores de los nodos que ocupan X e Y.
    - No es necesario recorrer la lista.

    Para el comando 4:
    - No recorremos la lista.
    - Solamente cambiamos la variable invertida.
    - Si la lista esta invertida, izquierda y derecha se interpretan
      al contrario.

    Complejidad:
    - Cada comando: O(1)
    - Cada caso: O(n + m)
    - Memoria: O(n)
*/

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    int caso = 1;

    while (cin >> n >> m) {
        list<int> cajas;
        vector<list<int>::iterator> posicion(n + 1);

        for (int i = 1; i <= n; i++) {
            cajas.push_back(i);
        }

        list<int>::iterator it = cajas.begin();

        for (int i = 1; i <= n; i++) {
            posicion[i] = it;
            ++it;
        }

        bool invertida = false;

        for (int i = 0; i < m; i++) {
            int tipo;
            cin >> tipo;

            if (tipo == 4) {
                invertida = !invertida;
                continue;
            }

            int X, Y;
            cin >> X >> Y;

            if (tipo == 1 || tipo == 2) {
                int realTipo = tipo;

                if (invertida) {
                    if (realTipo == 1) {
                        realTipo = 2;
                    } else {
                        realTipo = 1;
                    }
                }

                if (realTipo == 1) {
                    // X debe quedar inmediatamente a la izquierda de Y.
                    // En la lista fisica esto significa insertar antes de Y.
                    if (next(posicion[X]) != posicion[Y]) {
                        cajas.erase(posicion[X]);
                        posicion[X] = cajas.insert(posicion[Y], X);
                    }
                } else {
                    // X debe quedar inmediatamente a la derecha de Y.
                    // En la lista fisica esto significa insertar despues de Y.
                    list<int>::iterator siguiente = next(posicion[Y]);

                    if (siguiente != posicion[X]) {
                        cajas.erase(posicion[X]);

                        siguiente = next(posicion[Y]);
                        posicion[X] = cajas.insert(siguiente, X);
                    }
                }
            } else {
                // Intercambiar las posiciones de X e Y.
                //
                // Intercambiamos los valores de los dos nodos y tambien
                // sus iteradores. De esta forma, posicion[X] sigue
                // apuntando al nodo donde esta X.
                list<int>::iterator itX = posicion[X];
                list<int>::iterator itY = posicion[Y];

                iter_swap(itX, itY);
                posicion[X] = itY;
                posicion[Y] = itX;
            }
        }

        long long suma = 0;
        int pos = 1;

        if (!invertida) {
            for (int x : cajas) {
                if (pos % 2 == 1) {
                    suma += x;
                }
                pos++;
            }
        } else {
            for (auto it = cajas.rbegin(); it != cajas.rend(); ++it) {
                if (pos % 2 == 1) {
                    suma += *it;
                }
                pos++;
            }
        }

        cout << "Case " << caso << ": " << suma << '\n';
        caso++;
    }

    return 0;
}
