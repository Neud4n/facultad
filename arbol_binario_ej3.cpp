/*
Hacer una función, que, dado un árbol binario de números ordenado simétricamente de menor a
mayor de izquierda a derecha, y un valor que puede estar o no en el árbol, imprima todos los
descendientes del elemento dado.
*/

#include <iostream>

struct NodoArbol{
    int dato;
    NodoArbol *izq;
    NodoArbol *der;
};

typedef NodoArbol * PuntA;

void insertarNodo(PuntA &, int);
void imprimirDescendientes(PuntA, int);
void inOrder(PuntA);
PuntA encontrarNodo(PuntA, int);

int main(){
    PuntA raiz = NULL;
    insertarNodo(raiz, 57);
    insertarNodo(raiz, 22);
    insertarNodo(raiz, 83);
    insertarNodo(raiz, 15);
    insertarNodo(raiz, 39);
    insertarNodo(raiz, 68);
    insertarNodo(raiz, 90);
    insertarNodo(raiz, 47);
    insertarNodo(raiz, 74);
    insertarNodo(raiz, 5);
    insertarNodo(raiz, 29);
    insertarNodo(raiz, 60);
    insertarNodo(raiz, 95);
    imprimirDescendientes(raiz, 83);
}

void insertarNodo(PuntA &raiz, int num){
    if(raiz == NULL){
        PuntA nuevo = new NodoArbol;
        nuevo->dato = num;
        nuevo->izq  = NULL;
        nuevo->der  = NULL;
        raiz = nuevo;
    }else{
        if(raiz->dato > num){
            insertarNodo(raiz->izq, num);
        }else{
            insertarNodo(raiz->der, num);
        }
    }
}

PuntA encontrarNodo(PuntA raiz, int num){
    if(raiz!=NULL){
        if(raiz->dato == num){
            return raiz;
        }else{
            if(raiz->dato > num){
                return encontrarNodo(raiz->izq, num);
            }else{
                return encontrarNodo(raiz->der, num);
            }
        }
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

void imprimirDescendientes(PuntA raiz, int num){
    if(raiz!=NULL){
        raiz = encontrarNodo(raiz, num);
        inOrder(raiz);
    }
}