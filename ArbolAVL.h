#ifndef __ARBOLAVL__H__
#define __ARBOLAVL__H__

#include "NodoAVL.h"
#include <stack>

template <class T> 
class ArbolAVL {
  protected:
    NodoAVL<T> *raiz;
  public:
    ArbolAVL();
    ~ArbolAVL();
    bool esVacio();
    T &datoRaiz();
    int altura();
    unsigned int tamano();
    bool insertar(T &val);
    bool eliminar(T &val);
    bool buscar(T &val);
    void preOrden();
    void posOrden();
    void inOrden();
    void nivelOrden();
    void rotacionIzq(NodoAVL<T> *nodoPadre, NodoAVL<T> *nodoHijo);
    void rotacionDer(NodoAVL<T> *nodoPadre, NodoAVL<T> *nodoHijo);
    void rotacionIzqDer(NodoAVL<T> *nodoPadre, NodoAVL<T> *nodoHijo);
    void rotacionDerIzq(NodoAVL<T> *nodoPadre, NodoAVL<T> *nodoHijo);
    bool balanceo(NodoAVL<T> *nodoPadre);
    void balancearArbol(std::stack<NodoAVL<T>*> &camino);
};

#include "ArbolAVL.hxx"

#endif