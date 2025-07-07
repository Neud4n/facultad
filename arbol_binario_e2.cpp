/* 
Hacer rutinas para:
a) Agregar un nodo al árbol dado el número del cine, película y cantidad de entradas
vendidas. Debe considerar el árbol vacío.
b) Eliminar del árbol un cine dado su número.
c) Dado un cine y una cantidad de entradas, incrementar la cantidad para ese cine.
d) Informar el número de todos los cines donde se hayan vendido más de 2000 entradas.
e) Contar el total de entradas vendidas en todos los cines.
*/

#include <iostream>

struct Venta{
    int numeroCine;
    char pelicula[50];
    int cantidadEntradas;
};

struct NodoVenta{
    Venta dato;
    NodoVenta * sig;
};

struct NodoArbol{
    Venta dato;
    NodoArbol *izq;
    NodoArbol *der;
};

typedef NodoArbol * PuntA;
typedef NodoVenta * PuntL;

void push(PuntL &, Venta);
Venta pop(PuntL &);
PuntL cargarVentas();
void cargarDatosVenta(Venta &);
void mostrarDatosVenta(Venta);
bool salir();
void insertarRecursivo(PuntA &, Venta);
void crearArbol(PuntA &, PuntL &);
void inOrder(PuntA);
PuntA obtengoNodo(PuntA, int);
void incrementarEntradas(PuntA &);
void masDeDosMilEntradas(PuntA);
int contarTotalEntradas(PuntA);
void obtengoNodo(PuntA, int, PuntA &, PuntA &);
void eliminarNodo(PuntA &, int); 

int main(){
    int bor;
    PuntL ventas = cargarVentas();
    PuntA raiz = NULL;
    crearArbol(raiz, ventas);
    inOrder(raiz);
    incrementarEntradas(raiz); // Punto c
    inOrder(raiz);
    printf("Cines que vendieron más de 2000 entradas:\n");
    masDeDosMilEntradas(raiz); // Punto d
    printf("La cantidad total de entradas vendidas es de: %i\n", contarTotalEntradas(raiz)); // Punto e
    printf("Ingrese el numero de un cine a borrar\n");
    scanf("%i", &bor);
    eliminarNodo(raiz, bor);
    inOrder(raiz); // Punto b
    return 0;
}

void push(PuntL &lista, Venta venta){
    PuntL nuevo = new NodoVenta;
    nuevo->dato = venta;
    nuevo->sig = lista;
    lista = nuevo;
}

Venta pop(PuntL &lista){
    if(lista != NULL){
        PuntL bor = lista;
        Venta dato = lista->dato;
        lista = lista->sig;
        delete bor;
        return dato;
    }else{
        printf("Error: La lista esta vacia.\n");
        exit(1);
    }
}

void cargarDatosVenta(Venta &venta){
    printf("Ingrese el número de cine\n");
    scanf("%i", &venta.numeroCine);
    printf("Ingrese el nombre de la película\n");
    scanf("%s", venta.pelicula);
    printf("Ingrese la cantidad de entradas vendidas\n");
    scanf("%i", &venta.cantidadEntradas);
}

void mostrarDatosVenta(Venta venta){
    printf("El número de cine es: %i\n", venta.numeroCine);
    printf("El nombre de la película es: %s\n", venta.pelicula);
    printf("La cantidad de entradas vendidas fueron: %i\n", venta.cantidadEntradas);
}

PuntL cargarVentas(){
    PuntL ventas = NULL;
    Venta aux;
    while(salir()){
        cargarDatosVenta(aux);
        push(ventas, aux);
    }
    return ventas;
}

bool salir(){
    int respuesta;
    do{
        printf("Hay más datos para cargar?\n");
        scanf("%i", &respuesta);
        if(respuesta != 1 && respuesta != 0){
            printf("Ingrese un valor valido\n");
        }
    }while(respuesta != 1 && respuesta != 0);
    return respuesta == 1;
}

void insertarRecursivo(PuntA &raiz, Venta venta){
    if(raiz == NULL){
        PuntA nuevo = new NodoArbol;
        nuevo->dato = venta;
        nuevo->izq = NULL;
        nuevo->der = NULL;
        raiz = nuevo;
    }else{
        if(raiz->dato.numeroCine > venta.numeroCine){
            insertarRecursivo(raiz->izq, venta);
        }else{
            insertarRecursivo(raiz->der, venta);
        }
    }
}

void crearArbol(PuntA &raiz, PuntL &ventas){
    while(ventas != NULL){
        Venta dato = pop(ventas);
        insertarRecursivo(raiz, dato);
    }
}

void inOrder(PuntA raiz){
    if(raiz != NULL){
        inOrder(raiz->izq);
        mostrarDatosVenta(raiz->dato);
        inOrder(raiz->der);
    }
}

PuntA obtengoNodo(PuntA raiz, int numCine){
    if(raiz != NULL){
        if(raiz->dato.numeroCine == numCine){
            return raiz;
        }else{
            if(raiz->dato.numeroCine > numCine){
                return obtengoNodo(raiz->izq, numCine);
            }else{
                return obtengoNodo(raiz->der, numCine);
            }
        }
    }
    return NULL;
}

void incrementarEntradas(PuntA &raiz){
    if(raiz == NULL){
        return;
    }
    int numCine, cantEntradas;
    PuntA nodo = NULL;
    do{
        printf("Ingrese el número de cine\n");
        scanf("%i", &numCine);
        nodo = obtengoNodo(raiz, numCine);
        if(!nodo){
            printf("El cine ingresado no existe.\n");
        }
    }while(!nodo);
    do{
        printf("Ingrese la cantidad de entradas\n");
        scanf("%i", &cantEntradas);
    }while(cantEntradas < 1);
    nodo->dato.cantidadEntradas+= cantEntradas;
}

void masDeDosMilEntradas(PuntA raiz){
    if(raiz != NULL){
        masDeDosMilEntradas(raiz->izq);
        if(raiz->dato.cantidadEntradas > 2000){
            printf("Cine %i - Cant entradas: %i\n", raiz->dato.numeroCine, raiz->dato.cantidadEntradas);
        }
        masDeDosMilEntradas(raiz->der);
    }
}

int contarTotalEntradas(PuntA raiz){
    if(raiz != NULL){
        int sum = raiz->dato.cantidadEntradas;
        sum += contarTotalEntradas(raiz->izq);
        sum += contarTotalEntradas(raiz->der);
        return sum;
    }
    return 0;
}

void obtengoNodo(PuntA raiz, int numCine, PuntA &nodo, PuntA &nodoPadre){
    if(raiz != NULL){
        if(raiz->dato.numeroCine == numCine){
            nodo = raiz;
        }else{
            if(raiz->dato.numeroCine > numCine){
                obtengoNodo(raiz->izq, numCine, nodo, raiz);
            }else{
                obtengoNodo(raiz->der, numCine, nodo, raiz);
            }
        }
    }
}

void obtenerSucesor(PuntA raiz, PuntA &nodoEncontrado, PuntA &nodoPadre){
    if(raiz->izq == NULL){
        nodoEncontrado = raiz;
    }else{
        obtenerSucesor(raiz->izq, nodoEncontrado, raiz);
    }
}

void eliminarNodo(PuntA &raiz, int numCine){
    if(raiz != NULL){
        PuntA nodoEncontrado = NULL;
        PuntA nodoPadre = NULL;
        obtengoNodo(raiz, numCine, nodoEncontrado, nodoPadre);
        if(nodoEncontrado){
            if(nodoEncontrado->izq == NULL){ // Si sólo hay subArbol derecho.
                if(nodoPadre != NULL){
                    if(nodoPadre->izq == nodoEncontrado){
                        nodoPadre->izq = nodoEncontrado->der;
                    }else{
                        nodoPadre->der = nodoEncontrado->der;
                    }
                }else{
                    raiz = nodoEncontrado->der;
                }
                delete nodoEncontrado;
            }else if(nodoEncontrado->der == NULL){ // Significa que solo hay un subArbol izq;
                if(nodoPadre != NULL){
                    if(nodoPadre->der == nodoEncontrado){
                        nodoPadre->der = nodoEncontrado->izq;
                    }else{
                        nodoPadre->izq = nodoEncontrado->izq;
                    }
                }else{
                    raiz = nodoEncontrado->izq;
                }
                delete nodoEncontrado;
            }else if(nodoEncontrado->izq != NULL && nodoEncontrado->der != NULL){
                PuntA nodoSucesor = NULL;
                PuntA nodoPadreSucesor = NULL;
                obtenerSucesor(nodoEncontrado, nodoSucesor, nodoPadreSucesor);
                nodoEncontrado->dato = nodoSucesor->dato;
                nodoPadreSucesor->izq = nodoSucesor->der;
                delete nodoSucesor;
            }
        }
    }
}