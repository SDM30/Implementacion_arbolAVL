#ifndef __NODOAVL__H__
#define __NODOAVL__H__

#include <list>

template <class T> 
class NodoAVL {
  protected:
    T dato;
    NodoAVL<T> *hijoIzq;
    NodoAVL<T> *hijoDer;

  public:
    NodoAVL(T &val);
    T& obtenerDato();
    void fijarDato(T &val);
    NodoAVL<T> *obtenerHijoIzq();
    NodoAVL<T> *obtenerHijoDer();
    void fijarHijoIzq(NodoAVL<T> *izq);
    void fijarHijoDer(NodoAVL<T> *der);
    bool esHoja();
    int altura();
    unsigned int tamano();
    void preOrden();
    void posOrden();
    void inOrden();
    NodoAVL<T> *obtenerMaximo();
};

#include "NodoAVL.hxx"

#endif