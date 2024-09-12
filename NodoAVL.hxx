#include "NodoAVL.h"

template< class T >
NodoAVL<T>::NodoAVL(T &val){
    this->dato = val;
    this->hijoIzq = NULL;
    this->hijoDer = NULL;  
}

template< class T >
T& NodoAVL<T>::obtenerDato(){
    return this->dato;
}

template< class T >
void NodoAVL<T>::fijarDato(T &val){
    this->dato = val;
}

template< class T >
NodoAVL<T>* NodoAVL<T>::obtenerHijoIzq(){
    return this->hijoIzq;
}

template< class T >
NodoAVL<T>* NodoAVL<T>::obtenerHijoDer(){
    return this->hijoDer;
}

template< class T >
void NodoAVL<T>::fijarHijoIzq(NodoAVL<T> *izq){
    this->hijoIzq = izq;
}

template< class T >
void NodoAVL<T>::fijarHijoDer(NodoAVL<T> *der){
    this->hijoDer = der;
}

template< class T >
bool NodoAVL<T>::esHoja(){
    return (this->hijoIzq == NULL && this->hijoDer == NULL);
}

template< class T >
int NodoAVL<T>::altura(){

    int valAlt;
    if (this->esHoja()){
        valAlt = 0;
    } else {
        int valAlt_izq = -1;
        int valAlt_der = -1;
        if (this->hijoIzq != NULL){
            valAlt_izq = (this->hijoIzq)->altura();
        }
        if (this->hijoDer != NULL){
            valAlt_der = (this->hijoDer)->altura();
        }
        
        if (valAlt_izq > valAlt_der){
            valAlt = valAlt_izq + 1;
        } else {
            valAlt = valAlt_der + 1;
        }
    }

    return valAlt;
}

template < class T >
unsigned int NodoAVL<T>::tamano(){
    //Nodo actual
    int contador = 1;
    if (this->hijoIzq != NULL)
        contador += (this->hijoIzq)->tamano();
    if (this->hijoDer != NULL)
        contador += (this->hijoDer)->tamano();
    return contador;
}

template < class T >
void NodoAVL<T>::preOrden(){
    std::cout<<this->dato<<" ";

    if (this->hijoIzq != NULL)
        (this->hijoIzq)->preOrden();
    if (this->hijoDer != NULL)
        (this->hijoDer)->preOrden();
}

template < class T >
void NodoAVL<T>::posOrden(){
    if (this->hijoIzq != NULL)
        (this->hijoIzq)->posOrden();
    if (this->hijoDer != NULL)
        (this->hijoDer)->posOrden();

    std::cout<<this->dato<<" ";
}

template < class T >
void NodoAVL<T>::inOrden(){
    if (this->hijoIzq != NULL)
        (this->hijoIzq)->inOrden();
    std::cout<<this->dato<<" ";
    if (this->hijoDer != NULL)
        (this->hijoDer)->inOrden();
}

template < class T >
NodoAVL<T>* NodoAVL<T>::obtenerMaximo(){
    NodoAVL<T>* nodoActual = this;
    
    // Recorrer hacia la derecha hasta encontrar el nodo más grande
    while (nodoActual->hijoDer != NULL) {
        nodoActual = nodoActual->hijoDer;
    }
    
    return nodoActual;
}

template < class T >
NodoAVL<T>* NodoAVL<T>::rotacionIzq(){
    NodoAVL<T>* n2 = this->hijoDer;
    this->hijoDer = n2->hijoIzq;
    n2->hijoIzq = this;
    //El arbol resuelve el cambio entre
    //n2 y el nodo padre
    return n2;
}

template < class T >
NodoAVL<T>* NodoAVL<T>::rotacionDer(){
    NodoAVL<T>* n1 = this->hijoIzq;
    this->hijoIzq = n1->hijoDer;
    n1->hijoDer = this;
    //El arbol resuelve el cambio entre
    //n2 y el nodo padre
    return n1;
}

template < class T >
void NodoAVL<T>::rotacionIzqDer(){

}

template < class T >
void NodoAVL<T>::rotacionDerIzq(){

}

template < class T >
bool NodoAVL<T>::difAlturas(){

}