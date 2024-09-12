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
    if (this->esVacio()){
        return -1;
    } else {  
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

//Recurrente o Iterativa
template < class T >
bool ArbolAVL<T>::insertar(T &val){
    NodoAVL<T>* padre = this->raiz;
    NodoAVL<T>* nodo = this->raiz;
    bool insertado = false;
    bool duplicado = false;
    bool arbolVacio = false;

    if (this->esVacio()) {
        this->raiz = new NodoBinario<T>(val);
        arbolVacio = true;
    }

    while (nodo != NULL){
        padre = nodo;
        if (val < nodo->obtenerDato()) {
            nodo = nodo->obtenerHijoIzq();
        } else if (val > nodo->obtenerDato()) {
            nodo = nodo->obtenerHijoDer();
        } else {
            duplicado = true;
            break;
        }
    }

    if (!duplicado && !arbolVacio) {
        NodoAVL<T>* nodoIns = new NodoBinario<T>(val);
        //Verificar si hay algun fallo en la asignacion de mem
        if (nodoIns != NULL) {
            if (nodoIns->obtenerDato() > padre->obtenerDato()){
                padre->fijarHijoDer(nodoIns);
            } else {
                padre->fijarHijoIzq(nodoIns);
            }
        }
        insertado = true;
    }

    return insertado;
}

//Recurrente o Iterativa
template < class T >
bool ArbolAVL<T>::eliminar(T &val){

    NodoAVL<T>* padre = this->raiz;
    NodoAVL<T>* nodo = this->raiz;
    bool encontrado = false;
    bool eliminado = false;
    //Comparar con dato en nodo para bajar por izq o der
    //y para saber si val esta en el arbol
    while (nodo != NULL && !encontrado){
        if (val < nodo->obtenerDato()) {
            padre = nodo;
            nodo = nodo->obtenerHijoIzq();
        } else if (val > nodo->obtenerDato()) {
            padre = nodo;
            nodo = nodo->obtenerHijoDer();
        } else if (val == nodo->obtenerDato()) {
            encontrado = true;
        }
    }
    //Si val esta en el arbol
    if(encontrado) {
        //Verificar caso de eliminacion
        if (nodo->obtenerHijoIzq() == NULL && nodo->obtenerHijoDer() == NULL){
            //1. Nodo hoja (borrar)
            if (nodo->obtenerDato() == (this->raiz)->obtenerDato()){
                this->raiz = NULL;
            } else {
                // Verificar si es el hijo derecho del padre (y que no sea NULL)
                if (padre->obtenerHijoDer() == nodo) {
                    padre->fijarHijoDer(NULL);
                } 
                // Verificar si es el hijo izquierdo del padre (y que no sea NULL)
                else if (padre->obtenerHijoIzq() == nodo) {
                    padre->fijarHijoIzq(NULL);
                }
            }
            
            eliminado = true;
        }
        //2. Nodo con un solo hijo
        else if (nodo->obtenerHijoIzq() == NULL && nodo->obtenerHijoDer() != NULL){
            //Usar hijo para remplazar nodo
            if(nodo == this->raiz){
                this->raiz = nodo->obtenerHijoDer();
            } else {
                if (padre->obtenerHijoDer() == nodo){
                    padre->fijarHijoDer(nodo->obtenerHijoDer());
                } else {
                    padre->fijarHijoIzq(nodo->obtenerHijoDer()); 
                }
            }

            eliminado = true;
        }
        else if (nodo->obtenerHijoIzq() != NULL && nodo->obtenerHijoDer() == NULL){
            //Usar hijo para remplazar nodo
            if(nodo == this->raiz){
                this->raiz = nodo->obtenerHijoIzq();
            }else{
                if (padre->obtenerHijoIzq() == nodo){
                    padre->fijarHijoIzq(nodo->obtenerHijoIzq());
                } else {
                    padre->fijarHijoDer(nodo->obtenerHijoIzq());
                }
            }

            eliminado = true;
        }  
        //3. Nodo con dos hijos
        else if (nodo->obtenerHijoIzq() != NULL && nodo->obtenerHijoDer() != NULL){
            //Usar maximo de sub arbol izq para remplazar nodo
            NodoAVL<T>* nodoMaxIzq = (nodo->obtenerHijoIzq())->obtenerMaximo();

            if (nodoMaxIzq == padre->obtenerHijoDer()){
                padre->fijarHijoDer(nodoMaxIzq);
            } else {
                padre->fijarHijoIzq(nodoMaxIzq);
            }

            delete nodoMaxIzq;
            eliminado = true;
        }
    }

    if (eliminado)
        delete nodo;

    return eliminado;
}

//Recurrente o Iterativa
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