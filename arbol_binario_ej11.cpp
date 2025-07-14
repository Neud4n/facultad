// Dado un árbol binario de números enteros ordenado simétricamente de menor a mayor y un
// número, hacer una función que, si el número dado está en el árbol, elimine el menor de sus
// descendientes derechos, si existiera.

#include <iostream>

struct NodoArbol{
    int dato;
    NodoArbol *izq;
    NodoArbol *der;
};

typedef NodoArbol * PuntA;

void insertarNodo(PuntA &, int);
void borrarNodo(PuntA &, int);
void inOrder(PuntA);

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
    inOrder(raiz);
    printf("\n");
    borrarNodo(raiz,20);
    inOrder(raiz);
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
        if(raiz->dato > num){
            insertarNodo(raiz->izq, num);
        }else{
            insertarNodo(raiz->der, num);
        }
    }
}

void borrarNodo(PuntA &raiz, int num){
    if(raiz!=NULL){
        PuntA raizSubarbol = raiz;
        while(raizSubarbol && raizSubarbol->dato != num){
            if(raizSubarbol->dato > num){
                raizSubarbol = raizSubarbol->izq;
            }else{
                raizSubarbol = raizSubarbol->der;
            }
        }
        if(raizSubarbol && raizSubarbol->der){
            PuntA padreMenor = raizSubarbol;
            PuntA nodoMenor = raizSubarbol->der;
            while(nodoMenor->izq){
                padreMenor = nodoMenor;
                nodoMenor = nodoMenor->izq;
            }
            if(nodoMenor){
                if(padreMenor == raizSubarbol){
                    raizSubarbol->der = nodoMenor->der;
                }else{
                    padreMenor->izq = nodoMenor->der;
                }
                delete nodoMenor;
            }
        }
    }
}

void inOrder(PuntA raiz){
    if(raiz!=NULL){
        inOrder(raiz->izq);
        printf("%i ", raiz->dato);
        inOrder(raiz->der);
    }
}