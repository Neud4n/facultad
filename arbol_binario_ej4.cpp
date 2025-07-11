// # Hacer una función booleana que dados dos árboles determine si son idénticos.

#include <iostream>

struct NodoArbol{
    int dato;
    NodoArbol *izq;
    NodoArbol *der;
};

typedef NodoArbol * PuntA;

void insertarNodo(PuntA &, int);
bool sonIguales(PuntA, PuntA);

int main(){

    PuntA arbol_a = NULL;
    PuntA arbol_b = NULL;
    PuntA arbol_c = NULL;

    // Arbol 1 y 2 (iguales)
    insertarNodo(arbol_a, 10);
    insertarNodo(arbol_a, 5);
    insertarNodo(arbol_a, 15);

    insertarNodo(arbol_b, 10);
    insertarNodo(arbol_b, 5);
    insertarNodo(arbol_b, 15);

    // Arbol 3 diferente.
    insertarNodo(arbol_c, 10);
    insertarNodo(arbol_c, 15);
    insertarNodo(arbol_c, 20);
    
    if(sonIguales(arbol_a, arbol_b)){
        printf("Son iguales.\n");
    }else{
        printf("No son iguales.\n");
    }

    if(sonIguales(arbol_a, arbol_c)){
        printf("Son iguales.\n");
    }else{
        printf("No son iguales.\n");
    }

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

// Caso base: NULL ambos.
// Caso 1: Uno es NULL y el otro no. O sea, son diferentes.
// Caso 2: Ambos son diferentes de NULL por lo tanto va a seguir iterando mientras el dato == dato. 

bool sonIguales(PuntA arbol_a, PuntA arbol_b){
    if(arbol_a == NULL && arbol_b == NULL){
        return true;
    }else if ((arbol_a == NULL && arbol_b != NULL) || (arbol_a != NULL && arbol_b == NULL)){
        return false;
    }else if(arbol_a != NULL && arbol_b != NULL){
        if(arbol_a->dato == arbol_b->dato){
            return sonIguales(arbol_a->izq, arbol_b->izq) && sonIguales(arbol_a->der, arbol_b->der);
        }else{
            return false;
        }
    }
    return false;
}