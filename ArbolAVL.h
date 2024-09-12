#ifndef __ARBOLAVL__H__
#define __ARBOLAVL__H__

#include "NodoAVL.h"

template <class T> 
class ArbolAVL {
  protected:
    NodoAVL<T> *raiz;
  public:
    ArbolBinarioOrd();
    ~ArbolBinarioOrd();
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
};

#include "ArbolAVL.hxx"

#endif