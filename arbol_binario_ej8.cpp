// Se tiene un árbol de números enteros ordenado simétricamente de mayor a menor. Se pide hacer
// una función que, dado el árbol y un número entero, si éste está en el árbol devuelva la cantidad
// de nodos hojas que dependen de éste.

#include <iostream>

struct NodoArbol{
    int dato;
    NodoArbol *izq;
    NodoArbol *der;
};

typedef NodoArbol * PuntA;

struct NodoPila{
    PuntA nodo;
    NodoPila *sig;
};

typedef NodoPila * PuntP;

// Funciones pila
void push(PuntP &, PuntA);
PuntA pop(PuntP &);

// Funciones Árbol
void insertarNodo(PuntA &, int);
void mostrarHojas(PuntA, int);

int main(){
    PuntA raiz = NULL;
    insertarNodo(raiz, 50);
    insertarNodo(raiz, 20);
    insertarNodo(raiz, 15);
    insertarNodo(raiz, 5);
    insertarNodo(raiz, 18);
    insertarNodo(raiz, 40);
    insertarNodo(raiz, 38);
    insertarNodo(raiz, 45);
    mostrarHojas(raiz, 50);
    return 0;
}

void insertarNodo(PuntA &raiz, int num){
    if(raiz==NULL){
        PuntA nuevo = new NodoArbol;
        nuevo->dato = num;
        nuevo->izq = NULL;
        nuevo->der = NULL;
        raiz = nuevo;
    }else{
        if(raiz->dato < num){
            insertarNodo(raiz->izq, num);
        }else{
            insertarNodo(raiz->der, num);
        }
    }
}

void mostrarHojas(PuntA raiz, int num){
    PuntA nodoEncontrado = raiz;
    while(nodoEncontrado != NULL && nodoEncontrado->dato != num){
        if(num > nodoEncontrado->dato){
            nodoEncontrado = nodoEncontrado->izq;
        }else{
            nodoEncontrado = nodoEncontrado->der;
        }
    }
    if(nodoEncontrado){
        PuntP pila = NULL;
        while(nodoEncontrado || pila){
            if(nodoEncontrado){
                push(pila, nodoEncontrado);
                nodoEncontrado = nodoEncontrado->izq;
            }else{
                nodoEncontrado = pop(pila);
                if(!nodoEncontrado->izq && !nodoEncontrado->der){
                    printf("%i ", nodoEncontrado->dato);
                }
                nodoEncontrado = nodoEncontrado->der;
            }
        }
    }else{
        printf("El numero que pasaste no esta en el arbol\n");
    }
}

void push(PuntP &pila, PuntA nodo){
    PuntP nuevo = new NodoPila;
    nuevo->nodo = nodo;
    nuevo->sig = pila;
    pila = nuevo;
}

PuntA pop(PuntP &pila){
    if(pila!=NULL){
        PuntA aux = pila->nodo;
        PuntP bor = pila;
        pila = pila->sig;
        delete bor;
        return aux;
    }
    return NULL;
}