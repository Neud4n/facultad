//  Dado un árbol binario de números enteros ordenado simétricamente de menor a mayor hacer
// una función que elimine el menor de sus elementos, si existiera.

#include <iostream>

struct NodoArbol{
    int dato;
    NodoArbol *izq;
    NodoArbol *der;
};

typedef NodoArbol * PuntA;

void insertarNodo(PuntA &, int);
void inOrder(PuntA);
void eliminarMenorNodo(PuntA &);

int main(){
    PuntA raiz = NULL;
    insertarNodo(raiz, 5);
    insertarNodo(raiz, 10);
    insertarNodo(raiz, 15);
    insertarNodo(raiz, 25);
    insertarNodo(raiz, 4);
    insertarNodo(raiz, 3);
    inOrder(raiz);
    printf("\n");
    eliminarMenorNodo(raiz);
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

void inOrder(PuntA raiz){
    if(raiz!=NULL){
        inOrder(raiz->izq);
        printf("%i ", raiz->dato);
        inOrder(raiz->der);
    }
}

void eliminarMenorNodo(PuntA &raiz){
    if(raiz!=NULL){
        PuntA nodoPadre = NULL;
        PuntA nodoEncontrado = raiz;
        while(nodoEncontrado->izq){
            nodoPadre = nodoEncontrado;
            nodoEncontrado = nodoEncontrado->izq;
        }
        if(nodoEncontrado->der){
            if(nodoPadre){
                nodoPadre->izq = nodoEncontrado->der;
            }else{
                raiz = nodoEncontrado->der;
            }
            delete nodoEncontrado;
        }else{
            if(nodoPadre){
                nodoPadre->izq = NULL;
            }else{
                raiz = nodoEncontrado->der;
            }
            delete nodoEncontrado;
        }
    }
}