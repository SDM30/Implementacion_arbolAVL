#ifndef __NODOAVL__H__
#define __NODOAVL__H__

#include <list>

template <class T> 
class NodoAVL {
  protected:
    T dato;
    NodoBinario<T> *hijoIzq;
    NodoBinario<T> *hijoDer;

  public:
    NodoBinario(T &val);
    T& obtenerDato();
    void fijarDato(T &val);
    NodoBinario<T> *obtenerHijoIzq();
    NodoBinario<T> *obtenerHijoDer();
    void fijarHijoIzq(NodoBinario<T> *izq);
    void fijarHijoDer(NodoBinario<T> *der);
    bool esHoja();
    int altura();
    unsigned int tamano();
    void preOrden();
    void posOrden();
    void inOrden();
    NodoBinario<T> *obtenerMaximo();
};

#include "NodoAVL.hxx"

#endif