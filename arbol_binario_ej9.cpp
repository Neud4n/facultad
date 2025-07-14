/*
Se tiene un árbol binario de los hospitales de la ciudad. De cada hospital se conoce código,
nombre e importe total recaudado en concepto de donaciones. El árbol está ordenado
simétricamente por código de hospital. Se tiene otro árbol binario con las donaciones de la última
campaña. De cada donación se conoce dni de la persona que hizo la donación, código del
hospital al que se hizo la donación e importe donado. El árbol está ordenado simétricamente por
dni del donante. Se pide hacer una función que actualice el árbol de hospitales con los datos de
las donaciones.
*/

#include <iostream>

struct Hospital{
    int cod;
    int importeTotal;
};

struct Donante{
    int dni;
    int codHospital;
    int importeDonado;
};

struct ArbolHospital{
    Hospital dato;
    ArbolHospital *izq;
    ArbolHospital *der;
};

struct ArbolDonante{
    Donante dato;
    ArbolDonante *izq;
    ArbolDonante *der;
};

typedef ArbolHospital * PuntAH;
typedef ArbolDonante * PuntAD;

struct PilaHospital{
    Hospital dato;
    PilaHospital *sig;
};

struct PilaDonante{
    Donante dato;
    PilaDonante *sig;
};

typedef PilaHospital * PuntPH;
typedef PilaDonante * PuntPD;

struct PilaArbolHospital{
    PuntAH nodo;
    PilaArbolHospital *sig;
};

struct PilaArbolDonante{
    PuntAD nodo;
    PilaArbolDonante *sig;
};

typedef PilaArbolHospital * PuntPAH;
typedef PilaArbolDonante * PuntPAD;

// Funciones pilas
void pushHospital(PuntPH &, Hospital);
Hospital popHospital(PuntPH &);
void pushDonante(PuntPD &, Donante);
Donante popDonante(PuntPD &);
PuntPH crearPilaHospital();
PuntPD crearPilaDonante();
void pushNodoArbolHospital(PuntPAH &, PuntAH);
void pushNodoArbolDonante(PuntPAD &, PuntAD);
PuntAH popNodoArbolHospital(PuntPAH &);
PuntAD popNodoArbolHospital(PuntPAD &);

// Funciones para struct
void cargarDatosHospital(Hospital &);
void cargarDatosDonante(Donante &);
void mostrarDatosHospital(Hospital);
void mostrarDatosDonante(Donante);

// Funciones generales
bool salir();

// Funciones arboles
void insertNodoHosp(PuntAH &, Hospital);
void insertNodoDon(PuntAD &, Donante);
PuntAH crearArbolHosp(PuntPH &);
PuntAD crearArbolDon(PuntPD &);
void inOrderHospital(PuntAH);
void inOrderDonante(PuntAD);
void actualizarImpTotal(PuntAH &, PuntAD);

int main(){
    printf("================\n");
    printf("CARGA HOSPITALES\n");
    printf("================\n");
    PuntPH pilaHospital = crearPilaHospital();
    printf("==============\n");
    printf("CARGA DONANTES\n");
    printf("==============\n");
    PuntPD pilaDonante = crearPilaDonante();
    PuntAD arbolDonante = crearArbolDon(pilaDonante);
    PuntAH arbolHospital = crearArbolHosp(pilaHospital);
    printf("==================\n");
    printf("MOSTRAR HOSPITALES\n");
    printf("==================\n");
    inOrderHospital(arbolHospital);
    printf("================\n");
    printf("MOSTRAR DONANTES\n");
    printf("================\n");
    inOrderDonante(arbolDonante);
    actualizarImpTotal(arbolHospital, arbolDonante);
    printf("==================\n");
    printf("MOSTRAR HOSPITALES\n");
    printf("==================\n");
    inOrderHospital(arbolHospital);
    return 0;
}

// Funciones pilas
void pushHospital(PuntPH &pila, Hospital dato){
    PuntPH nuevo = new PilaHospital;
    nuevo->dato = dato;
    nuevo->sig = pila;
    pila = nuevo;
}

Hospital popHospital(PuntPH &pila){
    if(pila!=NULL){
        Hospital aux = pila->dato;
        PuntPH bor = pila;
        pila = pila->sig;
        delete bor;
        return aux;
    }
    return {};
}

void pushDonante(PuntPD &pila, Donante dato){
    PuntPD nuevo = new PilaDonante;
    nuevo->dato = dato;
    nuevo->sig = pila;
    pila = nuevo;
}

Donante popDonante(PuntPD &pila){
    if(pila!=NULL){
        Donante aux = pila->dato;
        PuntPD bor = pila;
        pila = pila->sig;
        delete bor;
        return aux;
    }
    return {};
}

// Funciones para struct
void cargarDatosHospital(Hospital &aux){
    printf("Ingrese el codigo de hospital\n");
    scanf("%i", &aux.cod);
    printf("Ingrese el importe total\n");
    scanf("%i", &aux.importeTotal);
}

void cargarDatosDonante(Donante &aux){
    printf("Ingrese el dni del donante\n");
    scanf("%i", &aux.dni);
    printf("Ingrese el codigo de hospital\n");
    scanf("%i", &aux.codHospital);
    printf("Ingrese el importe donado\n");
    scanf("%i", &aux.importeDonado);
}

PuntPH crearPilaHospital(){
    PuntPH pila = NULL;
    Hospital dato;
    while(salir()){
        cargarDatosHospital(dato);
        pushHospital(pila, dato);
    }
    return pila;
}

PuntPD crearPilaDonante(){
    PuntPD pila = NULL;
    Donante dato;
    while(salir()){
        cargarDatosDonante(dato);
        pushDonante(pila, dato);
    }
    return pila;
}

bool salir(){
    int resp;
    do{
        printf("Hay mas datos para cargar? Si - 1 | No - 0\n");
        scanf("%i", &resp);
        if(resp != 1 && resp != 0){
            printf("Respuesta invalida.\n");
        }
    }while(resp != 1 && resp != 0);
    return resp == 1;
}

void insertNodoHosp(PuntAH &raiz, Hospital dato){
    if(raiz==NULL){
        PuntAH nuevo = new ArbolHospital;
        nuevo->dato = dato;
        nuevo->izq = NULL;
        nuevo->der = NULL;
        raiz = nuevo;
    }else{
        if(raiz->dato.cod > dato.cod){
            insertNodoHosp(raiz->izq, dato);
        }else{
            insertNodoHosp(raiz->der, dato);
        }
    }
}

void insertNodoDon(PuntAD &raiz, Donante dato){
    if(raiz==NULL){
        PuntAD nuevo = new ArbolDonante;
        nuevo->dato = dato;
        nuevo->izq = NULL;
        nuevo->der = NULL;
        raiz = nuevo;
    }else{
        if(raiz->dato.dni > dato.dni){
            insertNodoDon(raiz->izq, dato);
        }else{
            insertNodoDon(raiz->der, dato);
        }
    }
}

PuntAH crearArbolHosp(PuntPH &pila){
    PuntAH arbol = NULL;
    Hospital aux;
    while(pila!=NULL){
        aux = popHospital(pila);
        insertNodoHosp(arbol, aux);
    }
    return arbol;
}

PuntAD crearArbolDon(PuntPD &pila){
    PuntAD arbol = NULL;
    Donante aux;
    while(pila!=NULL){
        aux = popDonante(pila);
        insertNodoDon(arbol, aux);
    }
    return arbol;
}

void mostrarDatosHospital(Hospital dato){
    printf("Codigo del hospital: %i\n", dato.cod);
    printf("Importe total del hospital: %i\n", dato.importeTotal);
}

void mostrarDatosDonante(Donante dato){
    printf("DNI del donante: %i\n", dato.dni);
    printf("Dono al hospital: %i\n", dato.codHospital);
    printf("Dono la cantidad de: %i\n", dato.importeDonado);
}

void inOrderHospital(PuntAH raiz){
    if(raiz!=NULL){
        inOrderHospital(raiz->izq);
        mostrarDatosHospital(raiz->dato);
        inOrderHospital(raiz->der);
    }
}

void inOrderDonante(PuntAD raiz){
    if(raiz!=NULL){
        inOrderDonante(raiz->izq);
        mostrarDatosDonante(raiz->dato);
        inOrderDonante(raiz->der);
    }
}

void pushNodoArbolHospital(PuntPAH &pila, PuntAH nodo){
    PuntPAH nuevo = new PilaArbolHospital;
    nuevo->nodo = nodo;
    nuevo->sig = pila;
    pila = nuevo;
}

void pushNodoArbolDonante(PuntPAD &pila, PuntAD nodo){
    PuntPAD nuevo = new PilaArbolDonante;
    nuevo->nodo = nodo;
    nuevo->sig = pila;
    pila = nuevo;
}

PuntAH popNodoArbolHospital(PuntPAH &pila){
    if(pila){
        PuntAH nodo = pila->nodo;
        PuntPAH bor = pila;
        pila = pila->sig;
        delete bor;
        return nodo;
    }
    return NULL;
}

PuntAD popNodoArbolDonante(PuntPAD &pila){
    if(pila){
        PuntAD nodo = pila->nodo;
        PuntPAD bor = pila;
        pila = pila->sig;
        delete bor;
        return nodo;
    }
    return NULL;
}

void actualizarImpTotal(PuntAH &raizHospital, PuntAD raizDonante){
    if(raizHospital && raizDonante){
        PuntPAD pilaDonantes = NULL;
        while(raizDonante || pilaDonantes){
            if(raizDonante){
                pushNodoArbolDonante(pilaDonantes, raizDonante);
                raizDonante = raizDonante->izq;
            }else{
                raizDonante = popNodoArbolDonante(pilaDonantes);
                PuntAH rHospital = raizHospital; // Vuelvo a la raíz del árbol.
                while(rHospital){
                    if(rHospital->dato.cod == raizDonante->dato.codHospital){
                        rHospital->dato.importeTotal+=raizDonante->dato.importeDonado;
                        rHospital = NULL;
                    }else if(rHospital->dato.cod > raizDonante->dato.codHospital){
                        rHospital = rHospital->izq;
                    }else{
                        rHospital = rHospital->der;
                    }
                }
                raizDonante = raizDonante->der;
            }
        }
    }
}

/*
PRUEBA DE EJECUCIÓN:

================
CARGA HOSPITALES
================
Hay mas datos para cargar? Si - 1 | No - 0
1
Ingrese el codigo de hospital
10
Ingrese el importe total
1000
Hay mas datos para cargar? Si - 1 | No - 0
1
Ingrese el codigo de hospital
20
Ingrese el importe total
2000
Hay mas datos para cargar? Si - 1 | No - 0
1
Ingrese el codigo de hospital
30
Ingrese el importe total
3000
Hay mas datos para cargar? Si - 1 | No - 0
1
Ingrese el codigo de hospital
5
Ingrese el importe total
500
Hay mas datos para cargar? Si - 1 | No - 0
0
==============
CARGA DONANTES
==============
Hay mas datos para cargar? Si - 1 | No - 0
1
Ingrese el dni del donante
1
Ingrese el codigo de hospital
5
Ingrese el importe donado
5000
Hay mas datos para cargar? Si - 1 | No - 0
1
Ingrese el dni del donante
2
Ingrese el codigo de hospital
30
Ingrese el importe donado
1000
Hay mas datos para cargar? Si - 1 | No - 0
1
Ingrese el dni del donante
3
Ingrese el codigo de hospital
10
Ingrese el importe donado
1000
Hay mas datos para cargar? Si - 1 | No - 0
0
==================
MOSTRAR HOSPITALES
==================
Codigo del hospital: 5
Importe total del hospital: 500
Codigo del hospital: 10
Importe total del hospital: 1000
Codigo del hospital: 20
Importe total del hospital: 2000
Codigo del hospital: 30
Importe total del hospital: 3000
================
MOSTRAR DONANTES
================
DNI del donante: 1
Dono al hospital: 5
Dono la cantidad de: 5000
DNI del donante: 2
Dono al hospital: 30
Dono la cantidad de: 1000
DNI del donante: 3
Dono al hospital: 10
Dono la cantidad de: 1000
==================
MOSTRAR HOSPITALES
==================
Codigo del hospital: 5
Importe total del hospital: 5500
Codigo del hospital: 10
Importe total del hospital: 2000
Codigo del hospital: 20
Importe total del hospital: 2000
Codigo del hospital: 30
Importe total del hospital: 4000
*/




// Recorrido in-order del árbol de donantes
void actualizarImpTotal(PuntAH &raizHospital, PuntAD raizDonante) {
    if (raizDonante != NULL) {
        // Recorre izquierda
        actualizarImpTotal(raizHospital, raizDonante->izq);

        // Actualiza hospital con este donante
        actualizarHospital(raizHospital, raizDonante->dato.codHospital, raizDonante->dato.importeDonado);

        // Recorre derecha
        actualizarImpTotal(raizHospital, raizDonante->der);
    }
}

// Busca el hospital por código y suma importe
void actualizarHospital(PuntAH &raizHospital, int codHospital, int importeDonado) {
    if (raizHospital != NULL) {
        if (raizHospital->dato.cod == codHospital) {
            raizHospital->dato.importeTotal += importeDonado;
        } else if (raizHospital->dato.cod > codHospital) {
            actualizarHospital(raizHospital->izq, codHospital, importeDonado);
        } else {
            actualizarHospital(raizHospital->der, codHospital, importeDonado);
        }
    }
}