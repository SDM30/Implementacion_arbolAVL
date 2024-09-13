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
    } else if ((this->raiz)->esHoja()){
        return 0;
    } else {  
        return (this->raiz)->altura() + 1;
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
    NodoAVL<T>* padre = NULL;
    NodoAVL<T>* nodo = this->raiz;
    bool insertado = false;
    bool duplicado = false;
    bool arbolVacio = false;
    //Nodos por los que se han pasado para insrt
    std::stack<NodoAVL<T>*> camino;

    if (this->esVacio()) {
        this->raiz = new NodoAVL<T>(val);
        arbolVacio = true;
    }

    while (nodo != NULL){
        camino.push(nodo);
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
        NodoAVL<T>* nodoIns = new NodoAVL<T>(val);
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

    if (insertado)
        balancearArbol(camino);

    return insertado;
}

//Recurrente o Iterativa
template < class T >
bool ArbolAVL<T>::eliminar(T &val){
    NodoAVL<T>* padre = NULL;
    NodoAVL<T>* nodo = this->raiz;
    bool encontrado = false;
    bool eliminado = false;
    //Nodos por los que se han pasado para elim
    std::stack<NodoAVL<T>*> camino;
    //Comparar con dato en nodo para bajar por izq o der
    //y para saber si val esta en el arbol
    while (nodo != NULL && !encontrado) {
        camino.push(nodo);
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
            // Usar el máximo del subárbol izquierdo para reemplazar el nodo
            NodoAVL<T>* nodoMaxIzq = (nodo->obtenerHijoIzq())->obtenerMaximo();
            T valorMaximo = nodoMaxIzq->obtenerDato(); // Almacenar el valor del máximo
            eliminar(valorMaximo);  // Eliminar el nodo máximo
            nodo->fijarDato(valorMaximo);  // Reemplazar el valor del nodo a eliminar con el valor del máximo
        }
    }

    balancearArbol(camino);

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

template < class T >
void ArbolAVL<T>::rotacionIzq(NodoAVL<T> *nodoPadre, NodoAVL<T> *nodoHijo){
    //realizar rotacion hacia la izquierda del hijo
    NodoAVL<T>* nodoTemp = nodoHijo->rotacionIzq();
    if (nodoPadre == NULL) {
        // Si no hay padre, es la raíz
        this->raiz = nodoTemp;
    } else if (nodoPadre->obtenerHijoDer() == nodoHijo) {
        //revisar de que lado es el hijo
        nodoPadre->fijarHijoDer(nodoTemp);
    } else {
        nodoPadre->fijarHijoIzq(nodoTemp);
    }
}

template < class T >
void ArbolAVL<T>::rotacionDer(NodoAVL<T> *nodoPadre, NodoAVL<T> *nodoHijo){
    //realizar rotacion hacia la izquierda del hijo
    NodoAVL<T>* nodoTemp = nodoHijo->rotacionDer();
    
    if (nodoPadre == NULL) {
        // Si no hay padre, es la raíz
        this->raiz = nodoTemp;
    } else if (nodoPadre->obtenerHijoDer() == nodoHijo) {
        //revisar de que lado es el hijo
        nodoPadre->fijarHijoDer(nodoTemp);
    } else {
        nodoPadre->fijarHijoIzq(nodoTemp);
    }
}

template < class T >
void ArbolAVL<T>::rotacionIzqDer(NodoAVL<T> *nodoPadre, NodoAVL<T> *nodoHijo){
    //realizar rotacion izquierda - derecha
    NodoAVL<T>* nodoTemp = nodoHijo->rotacionIzqDer();
    //revisar de que lado es el hijo
    if (nodoPadre == NULL) {
        // Si no hay padre, es la raíz
        this->raiz = nodoTemp;
    } else if (nodoPadre->obtenerHijoDer() == nodoHijo) {
        //revisar de que lado es el hijo
        nodoPadre->fijarHijoDer(nodoTemp);
    } else {
        nodoPadre->fijarHijoIzq(nodoTemp);
    }
}

template < class T >
void ArbolAVL<T>::rotacionDerIzq(NodoAVL<T> *nodoPadre, NodoAVL<T> *nodoHijo){
    //realizar rotacion derecha - izquierda
    NodoAVL<T>* nodoTemp = nodoHijo->rotacionDerIzq();
    if (nodoPadre == NULL) {
        // Si no hay padre, es la raíz
        this->raiz = nodoTemp;
    } else if (nodoPadre->obtenerHijoDer() == nodoHijo) {
        //revisar de que lado es el hijo
        nodoPadre->fijarHijoDer(nodoTemp);
    } else {
        nodoPadre->fijarHijoIzq(nodoTemp);
    }
}

template <class T>
bool ArbolAVL<T>::balanceo(NodoAVL<T> *nodoPadre) {
    int dif = nodoPadre->difAlturas();
    
    // Si el subárbol está desbalanceado (|dif| > 1)
    if (dif == 2) {
        NodoAVL<T>* n1 = nodoPadre->obtenerHijoIzq();
        // Subárbol izquierdo más alto (rotaciones hacia la derecha)
        if (n1->difAlturas() < 0) {
            // Caso de rotación Izquierda-Derecha
            this->rotacionIzqDer(nodoPadre, n1);
        } else {
            // Caso de rotación Derecha
            this->rotacionDer(nodoPadre, n1);
        }
        return true;
    } else if (dif == -2) {
        NodoAVL<T>* n2 = nodoPadre->obtenerHijoDer();
        // Subárbol derecho más alto (rotaciones hacia la izquierda)
        if (n2->difAlturas() > 0) {
            // Caso de rotación Derecha-Izquierda
            this->rotacionDerIzq(nodoPadre, n2);
        } else {
            // Caso de rotación Izquierda
            this->rotacionIzq(nodoPadre, n2);
        }
        return true;
    }
    return false;
}

template <class T>
void ArbolAVL<T>::balancearArbol(std::stack<NodoAVL<T>*> &camino) {
    //Balancear Arbol
    while (!camino.empty()) {
        NodoAVL<T>* nodoActual = camino.top();
        camino.pop();

        // Recalcular alturas y verificar balanceo
        if (this->balanceo(nodoActual)) {
            break; //Balanceado
        }
    }
}