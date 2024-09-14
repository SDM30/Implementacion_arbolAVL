#include <iostream>
#include "ArbolAVL.h"

void pruebaEliminaciones();
void pruebaCaso1Eliminacion();
void pruebaCaso2Eliminacion();
void pruebaCaso3Eliminacion();
void probarBusquedaPostEliminacion(ArbolAVL<int>& arbol, int valor);
void pruebaAlturaTamano();

int main() {

    std::cout << "----Caso 1----" << std::endl;
    pruebaCaso1Eliminacion();
    std::cout << std::endl;

    std::cout << "----Caso 2----" << std::endl;
    pruebaCaso2Eliminacion();
    std::cout << std::endl;

    std::cout << "----Caso 3----" << std::endl;
    pruebaCaso3Eliminacion();
    std::cout << std::endl;

    pruebaEliminaciones();
    std::cout << std::endl;
    std::cout << std::endl;

    std::cout << "----Prueba de Altura y Tamaño----" << std::endl;
    pruebaAlturaTamano();

    return 0;
}

void pruebaEliminaciones() {
    ArbolAVL<int> arbol;
    std::cout << "Insertando elementos en el árbol AVL:" << std::endl;
    int elementosInsertar[] = {7, 3, 20, 15, 25, 30, 5, 4, 6, 0, -3, 1};
    for (int i = 0; i < 12; i++) {
        std::cout << "Insertando " << elementosInsertar[i] << ": ";
        arbol.insertar(elementosInsertar[i]);
        arbol.nivelOrden();
        std::cout << std::endl;
    }

    // Recorridos
    std::cout << "\nRecorrido en preorden: ";
    arbol.preOrden();
    std::cout << "\nRecorrido en inorden: ";
    arbol.inOrden();
    std::cout << "\nRecorrido en posorden: ";
    arbol.posOrden();
    std::cout << "\nRecorrido en nivel-orden: ";
    arbol.nivelOrden();
    std::cout << std::endl;

    // Probar eliminación
    std::cout << "\nEliminando elementos del árbol AVL:" << std::endl;

    int elementosEliminar[] = {15, 25, 3};  // casos de eliminación
    for (int i = 0; i < 3; i++) {
        std::cout << "Eliminando " << elementosEliminar[i] << ": ";
        arbol.eliminar(elementosEliminar[i]);
        arbol.nivelOrden();
        std::cout << std::endl;
        probarBusquedaPostEliminacion(arbol, elementosEliminar[i]);
    }

    // Reinserciones
    std::cout << "\nReinsertando elementos en el árbol AVL:" << std::endl;
    for (int i = 0; i < 12; i++) {
        std::cout << "Insertando " << elementosInsertar[i] << ": ";
        arbol.insertar(elementosInsertar[i]);
        arbol.nivelOrden();
        std::cout << std::endl;
    }

    // Recorrido final
    std::cout << "\nÁrbol AVL después de las reinserciones en nivel-orden: ";
    arbol.nivelOrden();
    std::cout << std::endl;
}

void pruebaCaso1Eliminacion() {
    ArbolAVL<int> arbol;
    std::cout << "Insertando elementos en el árbol AVL:" << std::endl;
    int elementosInsertar[] = {7, 3, 20, 15, 25, 30, 5, 4, 6, 0, -3, 1};
    for (int i = 0; i < 12; i++) {
        arbol.insertar(elementosInsertar[i]);
    }

    arbol.nivelOrden();
    std::cout << std::endl;

    int valorCaso = 15;
    std::cout << "\nEliminando " << valorCaso << ": ";
    arbol.eliminar(valorCaso);
    arbol.nivelOrden();
    std::cout << std::endl;


    probarBusquedaPostEliminacion(arbol, valorCaso);
}

void pruebaCaso2Eliminacion() {
    ArbolAVL<int> arbol;
    std::cout << "Insertando elementos en el árbol AVL:" << std::endl;
    int elementosInsertar[] = {7, 3, 20, 15, 25, 30, 5, 4, 6, 0, -3, 1};
    for (int i = 0; i < 12; i++) {
        arbol.insertar(elementosInsertar[i]);
    }
    arbol.nivelOrden();
    std::cout << std::endl;

    int valorCaso = 25;
    std::cout << "\nEliminando " << valorCaso << ": ";
    arbol.eliminar(valorCaso);
    arbol.nivelOrden();
    std::cout << std::endl;

    probarBusquedaPostEliminacion(arbol, valorCaso);
}

void pruebaCaso3Eliminacion() {
    ArbolAVL<int> arbol;
    std::cout << "Insertando elementos en el árbol AVL:" << std::endl;
    int elementosInsertar[] = {7, 3, 20, 15, 25, 30, 5, 4, 6, 0, -3, 1};
    for (int i = 0; i < 12; i++) {
        arbol.insertar(elementosInsertar[i]);
    }
    arbol.nivelOrden();
    std::cout << std::endl;

    int valorCaso = 3;
    std::cout << "\nEliminando " << valorCaso << ": ";
    arbol.eliminar(valorCaso);
    arbol.nivelOrden();
    std::cout << std::endl;

    probarBusquedaPostEliminacion(arbol, valorCaso);
}

void probarBusquedaPostEliminacion(ArbolAVL<int>& arbol, int valor) {
    std::cout << "Verificando si el valor " << valor << " fue eliminado: ";
    if (arbol.buscar(valor)) {
        std::cout << "Fallo, el valor aún está presente.";
    } else {
        std::cout << "Éxito, el valor no está presente.";
    }
    std::cout << std::endl;
}

void pruebaAlturaTamano() {
    // Árbol grande
    ArbolAVL<int> arbolGrande;
    std::cout << "Insertando elementos en el árbol grande:" << std::endl;
    int elementosGrande[] = {7, 3, 20, 15, 25, 30, 5, 4, 6, 0, -3, 1};
    for (int i = 0; i < 12; i++) {
        std::cout << "Insertando " << elementosGrande[i] << ": ";
        arbolGrande.insertar(elementosGrande[i]);
        arbolGrande.nivelOrden();
        std::cout << std::endl;
    }
    int alturaEsperadaGrande = 3;  // Según la inserción esperada
    std::cout << "Altura del árbol grande: " << arbolGrande.altura() << std::endl;
    std::cout << "¿Altura correcta?: " << (arbolGrande.altura() == alturaEsperadaGrande ? "Sí" : "No") << std::endl;

    // Árbol hoja
    ArbolAVL<int> arbolHoja;
    std::cout << "Insertando un único elemento en el árbol hoja:" << std::endl;
    int elementoHoja = 10;
    arbolHoja.insertar(elementoHoja);
    std::cout << "Altura del árbol hoja: " << arbolHoja.altura() << std::endl;
    std::cout << "¿Altura correcta?: " << (arbolHoja.altura() == 0 ? "Sí" : "No") << std::endl;

    // Árbol vacío
    ArbolAVL<int> arbolVacio;
    std::cout << "Altura del árbol vacío: " << arbolVacio.altura() << std::endl;
    std::cout << "¿Altura correcta?: " << (arbolVacio.altura() == -1 ? "Sí" : "No") << std::endl;

    // Árbol mediano
    ArbolAVL<int> arbolMediano;
    std::cout << "Insertando elementos en el árbol mediano:" << std::endl;
    int elementosMediano[] = {10, 5, 15, 3, 7, 12};
    for (int i = 0; i < 6; i++) {
        std::cout << "Insertando " << elementosMediano[i] << ": ";
        arbolMediano.insertar(elementosMediano[i]);
        arbolMediano.nivelOrden();
        std::cout << std::endl;
    }
    int alturaEsperadaMediano = 2;  // Según la inserción esperada
    std::cout << "Altura del árbol mediano: " << arbolMediano.altura() << std::endl;
    std::cout << "¿Altura correcta?: " << (arbolMediano.altura() == alturaEsperadaMediano ? "Sí" : "No") << std::endl;

    // Verificar el tamaño esperado
    unsigned int tamanoEsperado = 12;  // Ya que se insertaron 12 elementos
    bool tamanoCorrecto = arbolGrande.tamano() == tamanoEsperado;
    std::cout << "Tamaño esperado: " << tamanoEsperado << std::endl;
    std::cout << "Tamaño actual: " << arbolGrande.tamano() << std::endl;
    std::cout << "¿Tamaño correcto?: " << (tamanoCorrecto ? "Sí" : "No") << std::endl;
}
