#include "ArbolAVL.h"
#include <queue>


template < class T >
ArbolAVL<T>::ArbolAVL(){
    this->raiz = NULL;
}

template < class T >
ArbolAVL<T>::~ArbolAVL(){
    if (this->raiz != NULL) {
        delete this->raiz;
        this->raiz = NULL;
    }
}

template < class T >
bool ArbolAVL<T>::esVacio(){
    return this->raiz == NULL;
}
template < class T >
T& ArbolAVL<T>::datoRaiz(){
    return (this->raiz)->obtenerDato();
}

//Recursiva
template < class T >
int ArbolAVL<T>::altura(){
    if(this->esVacio()){
        return -1;
    }
    else{
        return (this->raiz)->altura();
    }
}

//Recursiva
template < class T >
unsigned int ArbolAVL<T>::tamano(){
  // si esta vacio, retornar 0
    if (this->esVacio())
        return 0;
    
    int tam = 0;

    tam += (this->raiz)->tamano();

    return tam;
}

//Recurrente
template < class T >
bool ArbolAVL<T>::insertar(T &val){
    bool insertado = false;
    this->raiz = insertar(this->raiz, val, insertado);
    return insertado;
}

//Recurrente
template < class T >
NodoAVL<T>* ArbolAVL<T>::insertar(NodoAVL<T>* nodo,T& val, bool& insertado){
    //Caso base
    if (nodo == NULL) {
        insertado = true;
        NodoAVL<T>* nodoIns = new NodoAVL<T>(val);
        return nodoIns;
    }

    if (val < nodo->obtenerDato()) {
        nodo->fijarHijoIzq(insertar(nodo->obtenerHijoIzq(), val, insertado));
    } else if (val > nodo->obtenerDato()) {
        nodo->fijarHijoDer(insertar(nodo->obtenerHijoDer(), val, insertado));
    } else {
        insertado = false;
        return nodo;
    }
    return balancear(nodo);   
}

//Recurrente
template < class T >
bool ArbolAVL<T>::eliminar(T &val){
  bool eliminado = false;
  this->raiz = eliminar(this->raiz, val, eliminado);
  return eliminado;
}

template <class T>
NodoAVL<T>* ArbolAVL<T>::eliminar(NodoAVL<T>* nodo, T& val, bool& eliminado) {
    //Caso base
    if (nodo == NULL) {
        eliminado = false;
        return nodo;
    }

    //Ir por el lado Izquierdo
    if (val < nodo->obtenerDato()) {
        nodo->fijarHijoIzq(eliminar(nodo->obtenerHijoIzq(), val, eliminado));
    } else if (val > nodo->obtenerDato()) { //Ir por el lado derecho
        nodo->fijarHijoDer(eliminar(nodo->obtenerHijoDer(), val, eliminado));
    } else {
        //Encontro al nodo
        eliminado = true;
        NodoAVL<T>* aux;
        //Caso I: Nodo Hoja
        if(nodo->esHoja()){
        delete nodo;
        return NULL;
        } //Caso II: Nodo con un hijo
        else if (nodo->obtenerHijoDer() == NULL) {
            aux = nodo->obtenerHijoIzq();
            delete nodo;
            return aux;    
        } else if (nodo->obtenerHijoIzq() == NULL){
            aux = nodo->obtenerHijoDer();
            delete nodo;
            return aux;
        } //Caso III: Nodo con dos hijos
        else {
            aux = (nodo->obtenerHijoIzq())->obtenerMaximo();
            nodo->fijarDato(aux->obtenerDato());
            nodo->fijarHijoIzq(eliminar(nodo->obtenerHijoIzq(), aux->obtenerDato(), eliminado));
        }
    }
    //Balancear a mediad que avanza
    return balancear(nodo);
}

//Iterativa
template < class T >
bool ArbolAVL<T>::buscar(T &val){
    NodoAVL<T>* nodo = this->raiz;
    bool encontrado = false;

    while (nodo != NULL && !encontrado){
        if (val < nodo->obtenerDato()) {
            nodo = nodo->obtenerHijoIzq();
        } else if (val > nodo->obtenerDato()) {
            nodo = nodo->obtenerHijoDer();
        } else {
            encontrado = true;
        }
    }

    return encontrado;
}

//Recurrente
template < class T >
void ArbolAVL<T>::preOrden(){
    if (!this->esVacio()) {
        (this->raiz)->preOrden();
    }
}

//Recurrente
template < class T >
void ArbolAVL<T>::posOrden(){
    if (!this->esVacio()) {
        (this->raiz)->posOrden();
    }
}

//Recurrente
template < class T >
void ArbolAVL<T>::inOrden(){
    if (!this->esVacio()) {
        (this->raiz)->inOrden();
    }
}

//Iterativa
template < class T >
void ArbolAVL<T>::nivelOrden(){
    if (!this->esVacio()) {
        std::queue<NodoAVL<T>*> cola;
        cola.push(this->raiz);
        NodoAVL<T>* nodo;
        // hacer un ciclo mientar haya algo en la cola
        while (!cola.empty()) {
            nodo = cola.front();
            cola.pop();
            std::cout<<nodo->obtenerDato()<<" ";
            if (nodo->obtenerHijoIzq() != NULL) {
                cola.push(nodo->obtenerHijoIzq());
            }
            if (nodo->obtenerHijoDer() != NULL) {
                cola.push(nodo->obtenerHijoDer());
            }
        }
    }
}

template <class T>
NodoAVL<T>* ArbolAVL<T>::balancear(NodoAVL<T> *nodo) {
    int dif = nodo->difAlturas();
    
    // Si el subárbol está desbalanceado (|dif| > 1)
    if (dif == 2) {
        NodoAVL<T>* n1 = nodo->obtenerHijoIzq();
        //std::cout<<std::endl<<"Subárbol izquierdo más alto= "<< dif <<std::endl;
        // Subárbol izquierdo más alto (rotaciones hacia la derecha)
        if (n1->difAlturas() < 0) {
            // Caso de rotación Izquierda-Derecha
            //std::cout<<std::endl<<"rotación Izquierda-Derecha= "<< n1->difAlturas() <<std::endl;
            return nodo->rotacionIzqDer();
        } else if (n1->difAlturas() > 0) {
            // Caso de rotación Derecha
            //std::cout<<std::endl<<"rotación Derecha= "<< n1->difAlturas() <<std::endl;
            return nodo->rotacionDer();
        }

    } else if (dif == -2) {
        //std::cout<<std::endl<<"Subárbol derecho más alto= "<< dif <<std::endl;
        NodoAVL<T>* n2 = nodo->obtenerHijoDer();
        // Subárbol derecho más alto (rotaciones hacia la izquierda)
        if (n2->difAlturas() > 0) {
            // Caso de rotación Derecha-Izquierda
            //std::cout<<std::endl<<"rotación Derecha-Izquierda= "<< n2->difAlturas() <<std::endl;
            return nodo->rotacionDerIzq();
        } else if (n2->difAlturas() < 0) {
            //std::cout<<std::endl<<"rotación Izquierda= "<< n2->difAlturas() <<std::endl;
            // Caso de rotación Izquierda
            return nodo->rotacionIzq();
        }
    }
    return nodo;
}
