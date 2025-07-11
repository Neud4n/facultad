// Punto 5 - Hacer una función que devuelva el valor de la rama más larga o altura del árbol
// Punto 6 - Utilizando la función del punto 5, hacer una función que determinen la altura del subárbol
// izquierdo y la del subárbol derecho de un árbol dado y devuelva la diferencia entre ambos.
#include <iostream>

struct NodoArbol{
    int dato;
    NodoArbol *izq;
    NodoArbol *der;
};

typedef NodoArbol * PuntA;

void insertarNodo(PuntA &, int);
int calculoAltura(PuntA);
int compararAlturas(PuntA raiz);

int main(){
    PuntA raiz = NULL;
    insertarNodo(raiz, 5);
    insertarNodo(raiz, 10);
    insertarNodo(raiz, 15);
    insertarNodo(raiz, 25);
    insertarNodo(raiz, 4);
    insertarNodo(raiz, 3);
    printf("La altura del arbol es: %i",calculoAltura(raiz));
    printf("La diferencia de alturas es de: %i\n", compararAlturas(raiz));
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

int calculoAltura(PuntA raiz){
    if(raiz == NULL){
        return -1;
    }else if(!raiz->izq && !raiz->der){
        return 0;
    }else{
        int maxSubArbolIzq = calculoAltura(raiz->izq);
        int maxSubArbolDer = calculoAltura(raiz->der);
        if(maxSubArbolIzq > maxSubArbolDer){
            return 1 + maxSubArbolIzq;
        }else{
            return 1 + maxSubArbolDer;
        }
    }
}

int compararAlturas(PuntA raiz){
    if(raiz){
        return abs(calculoAltura(raiz->izq) - calculoAltura(raiz->der));    
    }
    return 0;
}