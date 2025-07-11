// Dado un árbol binario de números enteros ordenado simétricamente de menor a mayor, se pide
// hacer una función que sume el menor de los números del árbol a todos los elementos del mismo.

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

void push(PuntP &, PuntA);
PuntA pop(PuntP &);
void insertarNodo(PuntA &, int);
PuntA obtenerMenor(PuntA);
void sumarMenor(PuntA &);
void inOrder(PuntA);

int main(){
    PuntA raiz;
    insertarNodo(raiz, 5);
    insertarNodo(raiz, 10);
    insertarNodo(raiz, 15);
    insertarNodo(raiz, 25);
    insertarNodo(raiz, 4);
    insertarNodo(raiz, 3);
    return 0;
}

void insertarNodo(PuntA &raiz, int num){
    if(raiz==NULL){
        PuntA nuevo = new NodoArbol{num,NULL,NULL};
        raiz = nuevo;
    }else{
        if(raiz->dato > num){
            insertarNodo(raiz->izq, num);
        }else{
            insertarNodo(raiz->der, num);
        }
    }
}

PuntA obtenerMenor(PuntA raiz){
    if(raiz->izq!=NULL){
        return obtenerMenor(raiz->izq);
    }else{
        return raiz;
    }
}

void sumarMenor(PuntA &raiz){
    PuntA nodoMenor = obtenerMenor(raiz);
    int menor = nodoMenor->dato;
    PuntA r = raiz;
    PuntP pila = NULL;
    while(r || pila){
        if(r!=NULL){
            push(pila, r);
            r = r->izq;
        }else{
            r = pop(pila);
            r->dato+= menor;
            r = r->der;
        }
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

void inOrder(PuntA raiz){
    if(raiz!=NULL){
        inOrder(raiz->izq);
        printf("%i ", raiz->dato);
        inOrder(raiz->der);
    }
}