/* Punto 2
Se ingresan por teclado las ventas correspondientes al día. Por cada venta se ingresa:
Número de factura
Importe de la venta
Número de vendedor que realizó la venta
El ingreso de datos finaliza con número de factura cero.
Se pide hacer un programa que genere el archivo secuencial “VentasDia.dat” con un
registro por vendedor, con el siguiente diseño:
Número de vendedor
Cantidad total de ventas
Importe total de ventas
El archivo debe estar ordenado por vendedor y se debe utilizar un árbol binario ordenado
simétricamente por número de vendedor como estructura auxiliar.
*/

// Punto 3
// Dado el archivo “VentasDia.dat”, generado con el programa del punto 2, hacer un programa
// que genere el archivo que genere el archivo “VentasOrd.dat”, con los mismos datos,
// ordenado de mayor a menor por importe total de ventas, pero sin el vendedor que facturó el
// menor importe total. Utilizar un árbol binario como estructura auxiliar.

#include <iostream>
#include <stdio.h>

struct Venta{
    int nroFactura;
    int importeVenta;
    int nroVendedor;
};

struct Informe{
    int nroVendedor;
    int cantVentas = 0;
    int importeTotal = 0;
};

struct PilaVenta{
    Venta dato;
    PilaVenta *sig;
};

typedef PilaVenta * PuntP;

struct NodoArbol{
    PuntP ventas;
    NodoArbol *izq;
    NodoArbol *der;
};

typedef NodoArbol * PuntA;

struct NodoArbolInforme{
    Informe dato;
    NodoArbolInforme *izq;
    NodoArbolInforme *der;
};

typedef NodoArbolInforme * PuntAI;

// Funciones de la estrucutra Venta
void cargarDatosVenta(Venta &);
void mostrarDatosInforme(Informe);

// Funciones del arbol
void insertarNodo(PuntA &, Venta);
PuntA validoExistencia(PuntA, int);
PuntA crearArbol();
void generoInformes(PuntA, FILE *);

// Funciones de la pila
void pushVenta(PuntP &, Venta);
Venta popVenta(PuntP &);

// Funciones generales
bool salir();

// Funcioens de archivos
void crearArchivo(PuntA);
void imprimirArchivo();

// Funciones punto 3
PuntAI crearArbolInforme();
void insertarNodo(PuntAI &, Informe);
int obtenerMenorMonto();
void crearArchivoVentasOrd(PuntAI);
void escriboRegistros(PuntAI , FILE * &);
void imprimirArchivoInf();

int main(){
    crearArchivo(crearArbol());
    printf("=====================\n");
    printf("ORDENADO POR VENDEDOR\n");
    printf("=====================\n");
    imprimirArchivo();
    printf("=====================\n");
    printf("ORDENADO POR MONTO   \n");
    printf("=====================\n");
    crearArchivoVentasOrd(crearArbolInforme());
    imprimirArchivoInf();
    return 0;
}

void cargarDatosVenta(Venta &v){
    printf("Ingrese el numero de vendedor\n");
    scanf("%i", &v.nroVendedor);
    printf("Ingrese el numero de factura\n");
    scanf("%i", &v.nroFactura);
    printf("Ingrese el importe de la venta\n");
    scanf("%i", &v.importeVenta);
}

void pushVenta(PuntP &pila, Venta v){
    PuntP nuevo = new PilaVenta;
    nuevo->dato = v;
    nuevo->sig = pila;
    pila = nuevo;
}

Venta popVenta(PuntP &pila){
    if(pila!=NULL){
        Venta aux = pila->dato;
        PuntP bor = pila;
        pila = pila->sig;
        delete bor;
        return aux;
    }
    return {};
}

void insertarNodo(PuntA &raiz, Venta v){
    if(raiz==NULL){
        PuntA nuevo = new NodoArbol;
        nuevo->ventas = NULL; // Inicializo la pila de ventas.
        pushVenta(nuevo->ventas, v); // Cargo la primera venta.
        nuevo->izq = NULL;
        nuevo->der = NULL;
        raiz = nuevo;
    }else{
        if(raiz->ventas->dato.nroVendedor > v.nroVendedor){
            insertarNodo(raiz->izq, v);
        }else if(raiz->ventas->dato.nroVendedor < v.nroVendedor){
            insertarNodo(raiz->der, v);
        }
    }
}

PuntA validoExistencia(PuntA raiz, int nroVendedor){
    while(raiz && raiz->ventas->dato.nroVendedor != nroVendedor){
        if(raiz->ventas->dato.nroVendedor > nroVendedor){
            raiz = raiz->izq;
        }else if(raiz->ventas->dato.nroVendedor < nroVendedor){
            raiz = raiz->der;
        }
    }
    return raiz;
}

PuntA crearArbol(){
    PuntA raiz = NULL;
    PuntA nodoEncontrado = NULL;
    Venta venta;
    while(salir()){
        cargarDatosVenta(venta);
        nodoEncontrado = validoExistencia(raiz, venta.nroVendedor);
        if(nodoEncontrado!=NULL){
            pushVenta(nodoEncontrado->ventas, venta);
        }else{
            insertarNodo(raiz, venta);
        }
    }
    return raiz;
}

bool salir(){
    int resp;
    do{
        printf("Hay ventas para cargar?\n");
        scanf("%i", &resp);
    }while(resp!=0 && resp!=1);
    return resp == 1;
}

void crearArchivo(PuntA raiz){
    FILE * fptr = fopen("VentasDia.dat", "wb");
    if(!fptr){
        printf("No se pudo escribir el archivo\n");
        exit(EXIT_FAILURE);
    }
    generoInformes(raiz, fptr);
    fclose(fptr);
}

void generoInformes(PuntA raiz, FILE *file){
    if(raiz!=NULL){
        generoInformes(raiz->izq, file);
        Informe reg;
        Venta venta;
        reg.nroVendedor = raiz->ventas->dato.nroVendedor;
        while(raiz->ventas){
            venta = popVenta(raiz->ventas);
            reg.cantVentas++;
            reg.importeTotal+= venta.importeVenta;
        }
        fwrite(&reg, sizeof(Informe), 1, file);
        generoInformes(raiz->der, file);
    }
}

void imprimirArchivo(){
    FILE * fptr = fopen("VentasDia.dat", "rb");
    if(!fptr){
        printf("No se pudo abrir el archivo en modo lectura\n");
        exit(EXIT_FAILURE);
    }
    Informe reg;
    while(fread(&reg, sizeof(Informe),1, fptr)){
        mostrarDatosInforme(reg);
    }
    fclose(fptr);
}

void mostrarDatosInforme(Informe inf){
    printf("Nro de vendedor: %i\n", inf.nroVendedor);
    printf("Cantidad de ventas: %i\n", inf.cantVentas);
    printf("Importe total: %i\n", inf.importeTotal);
}

// Funciones punto 3

void insertarNodo(PuntAI &raiz, Informe dato){
    if(raiz==NULL){
        PuntAI nuevo = new NodoArbolInforme;
        nuevo->dato = dato;
        nuevo->izq = NULL;
        nuevo->der = NULL;
        raiz = nuevo;
    }else{
        if(raiz->dato.importeTotal > dato.importeTotal){
            insertarNodo(raiz->izq, dato);
        }else if(raiz->dato.importeTotal < dato.importeTotal){
            insertarNodo(raiz->der, dato);
        }
    }
}

int obtenerMenorMonto(){
    FILE * fptr = fopen("VentasDia.dat", "rb");
    if(!fptr){
        printf("No se pudo abrir el archivo en modo lecutra.\n");
        exit(EXIT_FAILURE);
    }
    Informe aux;
    fread(&aux, sizeof(Informe), 1, fptr);
    int menor = aux.importeTotal;
    while(fread(&aux, sizeof(Informe),1, fptr)){
        if(menor > aux.importeTotal){
            menor = aux.importeTotal;
        }
    }
    fclose(fptr);
    return menor;
}

PuntAI crearArbolInforme(){
    PuntAI raiz = NULL;
    int menorMonto = obtenerMenorMonto();
    FILE * fptr = fopen("VentasDia.dat", "rb");
    if(!fptr){
        printf("No se pudo abrir el archivo en modo lecutra.\n");
        exit(EXIT_FAILURE);
    }
    Informe aux;
    while(fread(&aux, sizeof(Informe), 1, fptr)){
        if(menorMonto != aux.importeTotal){
            insertarNodo(raiz, aux);
        }
    }
    fclose(fptr);
    return raiz;
}

void escriboRegistros(PuntAI raiz, FILE * &file){
    if(raiz!=NULL){
        escriboRegistros(raiz->der, file);
        Informe aux = raiz->dato;
        fwrite(&aux, sizeof(Informe), 1, file);
        escriboRegistros(raiz->izq, file);
    }
}

void crearArchivoVentasOrd(PuntAI raiz){
    FILE * fptr = fopen("VentasOrd.dat", "wb");
    if(!fptr){
        printf("No se pudo abrir el archivo en modo escritura\n");
        exit(EXIT_FAILURE);
    }
    escriboRegistros(raiz, fptr);
    fclose(fptr);
}

void imprimirArchivoInf(){
    FILE * fptr = fopen("VentasOrd.dat", "rb");
    if(!fptr){
        printf("No se pudo abrir el archivo en modo lectura\n");
        exit(EXIT_FAILURE);
    }
    Informe aux;
    while(fread(&aux, sizeof(Informe),1,fptr)){
        mostrarDatosInforme(aux);
    }
    fclose(fptr);
}