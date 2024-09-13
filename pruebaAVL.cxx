#include <iostream>
#include "ArbolAVL.h"

using namespace std;

void pruebaEliminaciones(ArbolAVL<int>& arbol) {
    // Probar inserciones
    cout << "Insertando elementos en el árbol AVL:" << endl;
    int elementosInsertar[] = {30, 20, 40, 10, 25, 35, 50};
    for (int i = 0; i < 7; i++) {
        cout << "Insertando " << elementosInsertar[i] << ": ";
        arbol.insertar(elementosInsertar[i]);
        arbol.nivelOrden();
        cout << endl;
    }

    // Probar recorridos del árbol
    cout << "\nRecorrido en preorden: ";
    arbol.preOrden();
    cout << "\nRecorrido en inorden: ";
    arbol.inOrden();
    cout << "\nRecorrido en posorden: ";
    arbol.posOrden();
    cout << "\nRecorrido en nivel-orden: ";
    arbol.nivelOrden();
    cout << endl;

    // Probar eliminación
    cout << "\nEliminando elementos del árbol AVL:" << endl;

    int elementosEliminar[] = {10, 30, 50, 20}; // casos de eliminación
    for (int i = 0; i < 4; i++) {
        cout << "Eliminando " << elementosEliminar[i] << ": ";
        arbol.eliminar(elementosEliminar[i]);
        arbol.nivelOrden();
        cout << endl;
    }

    // Volver a insertar los elementos
    cout << "\nReinsertando elementos en el árbol AVL:" << endl;
    for (int i = 0; i < 7; i++) {
        cout << "Insertando " << elementosInsertar[i] << ": ";
        arbol.insertar(elementosInsertar[i]);
        arbol.nivelOrden();
        cout << endl;
    }

    // Dibujar el árbol en nivel-orden final
    cout << "\nÁrbol AVL después de las reinserciones en nivel-orden: ";
    arbol.nivelOrden();
    cout << endl;
}

int main() {
    // Crear un árbol AVL de enteros
    ArbolAVL<int> arbol;

    pruebaEliminaciones(arbol);

    return 0;
}