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
    NodoAVL<T>* insertar(NodoAVL<T>* nodo,T& val, bool& insertado);
    bool eliminar(T &val);
    NodoAVL<T>* eliminar(NodoAVL<T>* nodo, T& val, bool& eliminado);
    bool buscar(T &val);
    void preOrden();
    void posOrden();
    void inOrden();
    void nivelOrden();
    NodoAVL<T>* balancear(NodoAVL<T> *nodo);
};

#include "ArbolAVL.hxx"

#endif