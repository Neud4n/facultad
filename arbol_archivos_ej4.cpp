/*
Se pide hacer un programa que ingrese por teclado los datos de las personas que se
inscribieron para el plan de vacunación. Por cada persona inscripta se ingresa:
Número de documento
Apellido y nombre
Código postal de la localidad donde reside
Se pide generar el archivo “RegistroVacunas.dat” con un registro por persona ordenado por
número de documento, verificar no guardar registros repetidos en el archivo. Utilizar un
árbol binario como estructura auxiliar
*/

/* PUNTO 4
Dado el archivo “RegistroVacunas.dat”, generado en el punto 1 y el archivo
“Localidades.dat” con un registro por cada localidad de la provincia, donde cada registro
tiene:
Código postal de la localidad
Nombre de la localidad
Cantidad de personas registradas para vacunar
Este archivo es de acceso directo, con clave código postal, usando área de rebalse para la
resolución de colisiones.
El programa deberá actualizar el archivo “Localidades.dat”, accediendo una única vez por
localidad, con los datos del archivo secuencial “RegistroVacunas.dat”.
Utilizar un árbol binario como estructura auxiliar.
*/

#include <iostream>
#include <stdio.h>

#define HASH_SIZE 5

struct Persona{
    int dni;
    char nombre[25];
    char apellido[25];
    int codPostal;
};

struct NodoArbol{
    Persona dato;
    NodoArbol *izq;
    NodoArbol *der;
};

typedef NodoArbol * PuntA;

struct Localidad{
    int codPostal;
    char localidad[50];
    int cantVacunados = 0;
};

struct NodoArbolLocalidad{
    Localidad dato;
    NodoArbolLocalidad *izq;
    NodoArbolLocalidad *der;
};

typedef NodoArbolLocalidad * PuntAL;

// Funciones Punto 3

void cargarDatosPersona(Persona &);
void mostrarDatosPersona(Persona);
void crearArchivo();
void insertarNodo(PuntA &, Persona);
bool validarExistencia(PuntA, int);
bool salir();
void imprimirArchivo();
void cargarOrdenado(PuntA, FILE * &);

// Funciones Punto 4
int getHash(int);
void crearArchivoAccDir();
PuntAL validarExistencia(PuntAL, int);
void insertarNodo(PuntAL &, Localidad);
PuntAL crearArbolLocalidad();
void mostrarDatosLocalidad(Localidad);
void cargarArchivo(PuntAL);
void escribirRegistros(PuntAL, FILE *);
void imprimirLocalidad();

int main(){
    crearArchivo();
    imprimirArchivo();
    crearArchivoAccDir();
    cargarArchivo(crearArbolLocalidad());
    printf("============\n");
    printf("LOCALIDADES:\n");
    printf("============\n");
    imprimirLocalidad();
    return 0;
}

void insertarNodo(PuntA &raiz, Persona dato){
    if(raiz==NULL){
        PuntA nuevo = new NodoArbol;
        nuevo->dato = dato;
        nuevo->izq = NULL;
        nuevo->der = NULL;
        raiz = nuevo;
    }else{
        if(raiz->dato.dni > dato.dni){
            insertarNodo(raiz->izq, dato);
        }else if (raiz->dato.dni < dato.dni){
            insertarNodo(raiz->der, dato);
        }
    }
}

bool validarExistencia(PuntA raiz, int dni){
    while(raiz && raiz->dato.dni != dni){
        if(raiz->dato.dni > dni){
            raiz = raiz->izq;
        }else{
            raiz = raiz->der;
        }
    }
    if(raiz!=NULL){
        return true;
    }
    return false;
}

void cargarDatosPersona(Persona &persona){
    printf("Ingrese el DNI de la persona\n");
    scanf("%i", &persona.dni);
    printf("Ingrese el nombre de la persona\n");
    scanf("%s", persona.nombre);
    printf("Ingrese el apellido de la persona\n");
    scanf("%s", persona.apellido);
    printf("Ingrese el codigo postal de la persona\n");
    scanf("%i", &persona.codPostal);
}

void crearArchivo(){
    FILE * fptr = fopen("RegistroVacunas.dat", "wb");
    if(fptr == NULL){
        printf("No se pudo generar el archivo\n");
        exit(EXIT_FAILURE);
    }
    Persona persona;
    PuntA aux = NULL;
    while(salir()){
        bool existe;
        do{
            cargarDatosPersona(persona);
            existe = validarExistencia(aux, persona.dni);
            if(existe){
                printf("La persona ingresada ya existe.\n");
            }
        }while(existe);
        insertarNodo(aux, persona);
    }
    cargarOrdenado(aux, fptr);
    fclose(fptr);
}

void cargarOrdenado(PuntA raiz, FILE * &file){
    if(raiz!=NULL){
        cargarOrdenado(raiz->izq, file);
        Persona persona = raiz->dato;
        fwrite(&persona, sizeof(Persona), 1, file);
        cargarOrdenado(raiz->der, file);
    }
}

bool salir(){
    int resp;
    do{
        printf("Hay datos para cargar?\n");
        scanf("%i", &resp);
        if(resp!=1 && resp!=0){
            printf("ERROR: Ingresó una respuesta invalida\n");
        }
    }while(resp!=1 && resp!=0);
    return resp == 1;
}

void mostrarDatosPersona(Persona p){
    printf("DNI: %i\n", p.dni);
    printf("Nombre: %s\n", p.nombre);
    printf("Apellido: %s\n", p.apellido);
    printf("Cod. Postal: %i\n", p.codPostal);
}

void imprimirArchivo(){
    FILE * fptr = fopen("RegistroVacunas.dat", "rb");
    if(!fptr){
        printf("No se pudo abrir el archivo en modo lectura.\n");
        exit(EXIT_FAILURE);
    }
    Persona aux;
    while(fread(&aux, sizeof(Persona), 1, fptr)){
        mostrarDatosPersona(aux);
    }
    fclose(fptr);
}

// Punto 4

int getHash(int codPostal){
    return codPostal % HASH_SIZE;
}

void crearArchivoAccDir(){
    FILE * fptr = fopen("Localidades.dat", "wb");
    if(!fptr){
        printf("No se pudo abrir el archivo en modo escritura\n");
        exit(EXIT_FAILURE);
    }
    Localidad aux;
    aux.cantVacunados = 0;
    aux.codPostal = 0;
    for(int i = 0; i < HASH_SIZE; i++){
        fwrite(&aux, sizeof(Localidad), 1, fptr);
    }
    fclose(fptr);
}

PuntAL validarExistencia(PuntAL raiz, int codPostal){
    if(raiz && raiz->dato.codPostal == codPostal){
        return raiz;
    }else if(raiz && raiz->dato.codPostal > codPostal){
        return validarExistencia(raiz->izq, codPostal);
    }else if(raiz && raiz->dato.codPostal < codPostal){
        return validarExistencia(raiz->der, codPostal);
    }
    return NULL;
}

void insertarNodo(PuntAL &raiz, Localidad dato){
    if(raiz==NULL){
        PuntAL nuevo = new NodoArbolLocalidad;
        nuevo->dato = dato;
        nuevo->izq = NULL;
        nuevo->der = NULL;
        raiz = nuevo;
    }else{
        if(raiz->dato.codPostal > dato.codPostal){
            insertarNodo(raiz->izq, dato);
        }else if(raiz->dato.codPostal < dato.codPostal){
            insertarNodo(raiz->der, dato);
        }
    }
}

PuntAL crearArbolLocalidad(){
    PuntAL raiz = NULL;
    FILE * fptr = fopen("RegistroVacunas.dat", "rb");
    if(!fptr){
        printf("No se pudo abrir el archivo en modo lectura\n");
        exit(EXIT_FAILURE);
    }
    Persona p;
    Localidad l;
    PuntAL nodoEncontrado = NULL;
    while(fread(&p, sizeof(Persona),1,fptr)){
        nodoEncontrado = validarExistencia(raiz, p.codPostal);
        if(nodoEncontrado){
            nodoEncontrado->dato.cantVacunados++;
        }else{
            l.codPostal = p.codPostal;
            printf("Ingrese la localidad para el codigo postal %i\n", l.codPostal);
            scanf("%s", l.localidad);
            l.cantVacunados = 1;
            insertarNodo(raiz, l);
        }
    }
    fclose(fptr);
    printf("Entregué la raíz ok\n");
    return raiz;
}

void mostrarDatosLocalidad(Localidad l){
    printf("Codigo Postal: %i\n", l.codPostal);
    printf("Localidad: %s\n", l.localidad);
    printf("Cantidad registrados: %i\n", l.cantVacunados);
}

void cargarArchivo(PuntAL raiz){
    FILE * fptr = fopen("Localidades.dat", "rb+");
    if(!fptr){
        printf("No se pudo abrir el archivo en modo escritura/lectura.\n");
        exit(EXIT_FAILURE);
    }
    escribirRegistros(raiz, fptr);
    fclose(fptr);
}

void escribirRegistros(PuntAL raiz, FILE *file){
    if(raiz!=NULL){
        escribirRegistros(raiz->izq, file);
        int pos = getHash(raiz->dato.codPostal);
        Localidad aux, dato;
        fseek(file, sizeof(Localidad)*pos, SEEK_SET);
        fread(&aux, sizeof(Localidad),1, file);
        if(aux.codPostal == 0){
            fseek(file, -sizeof(Localidad), SEEK_CUR);
            fwrite(&raiz->dato, sizeof(Localidad), 1, file);
            // No valido que aux.codPostal == raiz->dato.codPostal
            // Porque en el árbol no hay duplicados.
        }else{
            fseek(file, 0, SEEK_END);
            // No valido "borrados logicos", porque no hay.
            // También no valido duplicidad, por lo mismo de arriba.
            fwrite(&raiz->dato, sizeof(Localidad), 1, file);
        }
        escribirRegistros(raiz->der, file);
    }
}

void imprimirLocalidad(){
    FILE * fptr = fopen("Localidades.dat", "rb");
    if(!fptr){
        printf("La funcion imprimirLocalidad no pudo abrir el archivo Localidades.dat\n");
    }
    Localidad aux;
    while(fread(&aux, sizeof(Localidad), 1, fptr)){
        if(aux.codPostal != 0){
            mostrarDatosLocalidad(aux);
        }
    }
    fclose(fptr);
}