// Ejercicio.
// Este programa valida que los parentesís, llaves y corchetes estén cerrados.
// INPUT de prueba (2+[3-12]*{8/3})
// INPUT de prueba }(2+[3-12]*{8/3})
// {[2+4}]

#include <iostream>
#include <stdlib.h>
using namespace std;

struct nodo{
    char inf;
    struct nodo *sig;
};

void setFormula(char **, int &);
void obtenerDelimitadores(char, nodo **);
void borrarNodo(nodo **);
bool validoBalanceo(char *, int, nodo **);

int main()
{   
    char *cadena;
    int longitudFormula = 0;
    struct nodo *pila = NULL;
    setFormula(&cadena, longitudFormula);
    if(validoBalanceo(cadena, longitudFormula, &pila)){
        printf("La formula esta balanceada.\n");
    }else{
        printf("La formula no está balanceada.\n");
    }
    free(cadena);
    return(0);
}

void setFormula(char **cadena, int &longitudFormula){
    printf("Ingrese la longitud de la formula: ");
    scanf("%i", &longitudFormula);
    *cadena = (char*)malloc(longitudFormula + 1);
    printf("Ingrese la formula: ");
    scanf("%s", *cadena);
}

void obtenerDelimitadores(char delimitador, nodo **pila) {
    struct nodo *nuevo;
    if (delimitador == '(' || delimitador == '{' || delimitador == '[') {
        nuevo = (nodo*)malloc(sizeof(struct nodo)); 
        if (nuevo == NULL) {
            printf("Error al asignar memoria.\n");
            exit(1);
        }
        nuevo->inf = delimitador;
        nuevo->sig = *pila;
        *pila = nuevo;
    }
}

void borrarNodo(nodo **pila){
    struct nodo *bor = *pila;
    if(bor != NULL){
        (*pila) = (*pila)->sig;
        free(bor);
    }
}

// FORMULA: {[2+4}]
// PILA: [ {
// ORDEN: } ]

// (2+[3-12]*{8/3}

bool validoBalanceo(char *cadena, int longitud, nodo **pila){
    for(int i = 0; i < longitud; i++){
        obtenerDelimitadores(cadena[i], pila); //  (
        if(cadena[i] == ')' || cadena[i] == '}' || cadena[i] == ']'){
            // Valido que el primer caracter de la formula no sea un delimitador de cierre.
            if (*pila == NULL) { 
                return(false);
            } else {
                // Valido si está balanceado el delimitador.
                if((cadena[i] == ')' && (*pila)->inf != '(') ||
                   (cadena[i] == '}' && (*pila)->inf != '{') ||
                   (cadena[i] == ']' && (*pila)->inf != '[')){
                    return(false);
                } else {
                    borrarNodo(pila); 
                }
            }
        }
    }
    // Valido que no hayan quedado delimitadores de apertura.
    return(*pila == NULL);
}
