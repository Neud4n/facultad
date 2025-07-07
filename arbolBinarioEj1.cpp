#include <iostream>
#define MESES 3

struct Venta{
    int mes;
    char nombreMes[10];
    float monto;
};

struct NodoArbol{
    Venta dato;
    NodoArbol *izq;
    NodoArbol *der;
};

typedef NodoArbol * PuntA;

void crearArbol(PuntA &, Venta []);
void insertarNodo(PuntA &, Venta);
void mostrarDatosVenta(Venta);
void cargarDatosVenta(Venta &);
void inOrder(PuntA);
void cargarVentas(Venta []);

int main(){
    Venta ventas[MESES];
    PuntA raiz = NULL;
    cargarVentas(ventas);
    crearArbol(raiz, ventas);
    inOrder(raiz);
    return 0;
}

void cargarVentas(Venta ventas[]){
    for(int i = 0; i < MESES; i++){
        cargarDatosVenta(ventas[i]);
    }
}

void cargarDatosVenta(Venta &venta){
    printf("Ingrese el mes de la venta\n");
    scanf("%i", &venta.mes);
    printf("Ingrese el nombre del mes\n");
    scanf("%s", venta.nombreMes);
    printf("Ingrese el monto de la venta\n");
    scanf("%f", &venta.monto);
}

void crearArbol(PuntA &raiz, Venta ventas[]){
    for(int i = 0; i < MESES; i++){
        insertarNodo(raiz, ventas[i]);
    }
}

void insertarNodo(PuntA &raiz, Venta venta){
    if(raiz == NULL){
        PuntA nuevo = new NodoArbol{venta, NULL, NULL};
        raiz = nuevo;
    }else{
        if(raiz->dato.mes > venta.mes){
            insertarNodo(raiz->izq, venta);
        }else{
            insertarNodo(raiz->der, venta);
        }
    }
}

void inOrder(PuntA raiz){
    if(raiz != NULL){
        inOrder(raiz->izq);
        mostrarDatosVenta(raiz->dato);
        inOrder(raiz->der);
    }
}

void mostrarDatosVenta(Venta venta){
    printf("Mes: %i - %s\n", venta.mes, venta.nombreMes);
    printf("Recaudado: %.2f\n", venta.monto);
    printf("===================\n");
}