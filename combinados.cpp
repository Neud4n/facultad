// Ejercicios - Archivos - Pilas - Colas
#include <iostream>
#include <stdio.h>

struct Producto{
    int codigo;
    char des[50];
    int precio;
    int stock;
};

struct NodoPila{
    Producto inf;
    NodoPila * sig;
};

struct NodoCola{
    Producto inf;
    NodoCola * sig;
};

struct Cola{
    NodoCola * head;
    NodoCola * tail;
};

#define HASH_SIZE 50

typedef NodoPila * PuntP;

void inicializarPila(PuntP &);
void inicializarCola(Cola &);
bool isEmptyCola(Cola);
bool isEmptyPila(PuntP);
void recibirProductos();
void cargarDatosProducto(Producto &);
bool salir();
void pushProducto(PuntP &, Producto);
void popProducto(PuntP &, Producto &);
void queueProducto(Cola &, Producto);
void unqueueProducto(Cola &, Producto &);
void procesarProductos();
Cola crearColaProductos(); 
int getHash(int); // Punto 4
void guardarProductos(Cola &); // Punto 4
void newFileProductosOrdenados(); // Punto 4
void mostrarArchivoRecibidos(); // Punto 5
void mostrarArchivoProductos(); // Punto 6
void mostrarArchivoOrdenados(); // Punto 7
void mostrarProductoPorCodigo(int); // Punto 8
void mostrarDatosProducto(Producto);
void eliminarProducto(int);  // Punto 9
void mostrarStockBajo(int); // Punto 10
void menu();
void mostrarMenu();

int main()
{
    menu();
    return 0;
}

void inicializarPila(PuntP &head){
    head = nullptr;
}

void inicializarCola(Cola &c){
    c.head = nullptr;
    c.tail = nullptr;
}

bool isEmptyCola(Cola c){
    return c.head == nullptr;
}

bool isEmptyPila(PuntP head){
    return head == nullptr;
}

void recibirProductos(){
    FILE * fptr = fopen("productos_recibidos.dat", "wb");
    Producto aux;
    if(fptr == nullptr){
        printf("No se pudo crear el archivo productos_recibidos.dat\n");
        exit(10);
    }
    do{
        cargarDatosProducto(aux);
        fwrite(&aux, sizeof(Producto), 1, fptr);
    }while(salir());
    aux = {-1,"",0,0};
    fwrite(&aux, sizeof(Producto), 1, fptr); // El ejercicio pide que se agregue al final un -1
    fclose(fptr);
}

bool salir(){
    int resp;
    do{
        printf("Hay mas datos para cargar? 1 - Si | 0 - No\n");
         scanf("%i", &resp);
    }while(resp != 0 && resp != 1);
    return resp == 1;
}

void cargarDatosProducto(Producto &p){
    printf("Ingrese el código del producto\n"); 
    scanf("%i", &p.codigo);
    printf("Ingrese la descripción del producto\n");
    scanf("%49s", p.des);
    printf("Ingrese el precio del producto\n");
    scanf("%i", &p.precio);
    printf("Ingrese el stock del producto\n");
    scanf("%i", &p.stock);
}

void pushProducto(PuntP &head, Producto p){
    PuntP newNode = new NodoPila;
    newNode->inf = p;
    newNode->sig = head;
    head = newNode;
}

void popProducto(PuntP &head, Producto &p){
    if(!isEmptyPila(head)){
        PuntP bor = head;
        p = head->inf;
        head = head->sig;
        delete bor;
    }
}

void procesarProductos(){
    PuntP pilaProductos;
    Producto aux;
    inicializarPila(pilaProductos);
    FILE * fp = fopen("productos_recibidos.dat", "rb");
    FILE * fpProductos = fopen("productos.dat", "wb");

    if(fp == nullptr){
        printf("No se pudo abrir el archivo productos_recibidos.dat\n");
        exit(11);
    }

    if(fpProductos == nullptr){
        printf("No se pudo crear el archivo productos.dat\n");
        exit(12);
    }
    
    while(fread(&aux, sizeof(Producto), 1, fp) == 1 && aux.codigo != -1){
        pushProducto(pilaProductos, aux);
    }
    fclose(fp);

    while(!isEmptyPila(pilaProductos)){
        popProducto(pilaProductos, aux);
        fwrite(&aux, sizeof(Producto), 1, fpProductos);
    }

    fclose(fpProductos);
}

void queueProducto(Cola &c, Producto p){
    NodoCola * newNode = new NodoCola{p, nullptr};
    if(isEmptyCola(c)){
        c.head = newNode;
    }else{
        c.tail->sig = newNode;
    }
    c.tail = newNode;
}

void unqueueProducto(Cola &c, Producto &p){
    if(!isEmptyCola(c)){
        NodoCola * bor = c.head;
        p = c.head->inf;
        c.head = c.head->sig;
        if(c.head == nullptr){
            c.tail = nullptr;
        }
        delete bor;
    }
}

Cola crearColaProductos(){
    Cola c;
    Producto aux;
    inicializarCola(c);
    FILE * fp = fopen("productos.dat", "rb");
    if(fp == nullptr){
        printf("No se pudo abrir el archivo productos.dat\n");
        exit(13);
    }
    while(fread(&aux, sizeof(Producto), 1, fp) == 1){
        queueProducto(c, aux);
    }
    fclose(fp);
    return c;
}

int getHash(int num){
    return num % HASH_SIZE;
}

void newFileProductosOrdenados(){
    Producto aux = {-1, "", 0, 0};
    FILE * fp = fopen("productos_ordenados.dat", "wb");
    if(fp == nullptr){
        printf("No se pudo crear el archivo productos_ordenados.dat\n");
        exit(14);
    }
    for(int i = 0; i<HASH_SIZE; i++){
        fwrite(&aux, sizeof(Producto), 1, fp);
    }
    fclose(fp);
}

void guardarProductos(Cola &c){
    Producto p, aux;
    int pos;
    newFileProductosOrdenados();
    FILE * fpOrdenados = fopen("productos_ordenados.dat", "rb+");
    if(fpOrdenados == nullptr){
        printf("No se pudo abrrir el archivo productos_ordenados.dat\n");
        exit(15);
    }
    while(!isEmptyCola(c)){
        unqueueProducto(c, p);
        pos = getHash(p.codigo);
        fseek(fpOrdenados, 0, SEEK_SET); // Arranco siempre desde el principio del archivo
        fseek(fpOrdenados, sizeof(Producto)*pos, SEEK_CUR); // Me muevo hasta la posicion de hash
        fread(&aux, sizeof(Producto), 1, fpOrdenados); // Leo que hay en esa posicion.
        if(aux.codigo == -1){ // Si es -1 escribo en el archivo los datos del nodo de la cola
            fseek(fpOrdenados, -sizeof(Producto), SEEK_CUR);
            fwrite(&p, sizeof(Producto), 1, fpOrdenados);
        }else if(aux.codigo == p.codigo){ // Si el codigo es igual, piso los datos y actualizo stock.
            fseek(fpOrdenados, -sizeof(Producto), SEEK_CUR);
            p.stock+=aux.stock;
            fwrite(&p, sizeof(Producto), 1, fpOrdenados);
        }else{
            fseek(fpOrdenados, sizeof(Producto)*HASH_SIZE, SEEK_SET); // Voy al principio del area de rebalse.
            bool encontrado = false;
            while(!encontrado && fread(&aux, sizeof(Producto), 1, fpOrdenados) == 1){
                if(aux.codigo == p.codigo){ // Busco si ya existe en el area de rebalse.
                    fseek(fpOrdenados, -sizeof(Producto), SEEK_CUR);
                    p.stock+=aux.stock;
                    fwrite(&p, sizeof(Producto), 1, fpOrdenados);
                    encontrado = true;
                }
            }
            if(!encontrado){
                fwrite(&p, sizeof(Producto), 1, fpOrdenados); // Si no existe lo agrego al final del rebalse.
            }
        }
    }
    fclose(fpOrdenados);
}

void mostrarDatosProducto(Producto p){
    printf("Codigo: %i\n", p.codigo);
    printf("Descripcion: %s\n", p.des);
    printf("Precio: %i\n", p.precio);
    printf("Stock: %i\n", p.stock);
    printf("-----\n");
}

void mostrarArchivoRecibidos(){
    FILE * fp = fopen("productos_recibidos.dat", "rb");
    Producto aux;
    if(fp == nullptr){
        printf("No se pudo abrrir el archivo productos_recibidos.dat\n");
        exit(16);
    }
    printf("=======================\n");
    printf("productos_recibidos.dat\n");
    printf("=======================\n");
    while(fread(&aux, sizeof(Producto), 1, fp) == 1 && aux.codigo != -1){
        mostrarDatosProducto(aux);
    }
    fclose(fp);
}

void mostrarArchivoProductos(){
    FILE * fp = fopen("productos.dat", "rb");
    Producto aux;
    if(fp == nullptr){
        printf("No se pudo abrir el archivo productos.dat\n");
        exit(17);
    }
    printf("=============\n");
    printf("productos.dat\n");
    printf("=============\n");
    while(fread(&aux, sizeof(Producto), 1, fp) == 1){
        mostrarDatosProducto(aux);
    }
    fclose(fp);
}

void mostrarArchivoOrdenados(){
    FILE * fp = fopen("productos_ordenados.dat", "rb");
    Producto aux;
    if(fp == nullptr){
        printf("No se pudo abrir el archivo productos_ordenados.dat\n");
        exit(17);
    }
    printf("=======================\n");
    printf("productos_ordenados.dat\n");
    printf("=======================\n");
    while(fread(&aux, sizeof(Producto), 1, fp) == 1){
        if(aux.codigo != -1){
            mostrarDatosProducto(aux);
        }
    }
    fclose(fp);
}

void mostrarProductoPorCodigo(int codigo){
    printf("===================\n");
    printf("Busqueda por codigo\n");
    printf("===================\n");
    FILE * fp = fopen("productos_ordenados.dat", "rb");
    Producto aux;
    if(fp == nullptr){
        printf("No se pudo abrir el archivo productos_ordenados.dat\n");
        exit(18);
    }
    int pos = getHash(codigo);
    fseek(fp, sizeof(Producto)*pos, SEEK_SET);
    fread(&aux, sizeof(Producto), 1, fp);
    if(aux.codigo == codigo){
        mostrarDatosProducto(aux);
    }else{
        fseek(fp, sizeof(Producto)*HASH_SIZE, SEEK_SET);
        bool encontrado = false;
        while(!encontrado && fread(&aux, sizeof(Producto), 1, fp) == 1){
            if(aux.codigo == codigo){
                encontrado = true;
            }
        }
        if(encontrado){
            mostrarDatosProducto(aux);
        }else{
            printf("El codigo solicitado no existe.\n");
        }
    }
    fclose(fp);
}

void eliminarProducto(int codigo){
    printf("Eliminando...\n");
    Producto aux;
    FILE * fptr = fopen("productos_ordenados.dat", "rb+");
    if(fptr == nullptr){
        printf("No se pudo abrir el archivo productos_ordenados.dat\n");
        exit(18);
    }
    int pos = getHash(codigo);
    fseek(fptr, sizeof(Producto)*pos, SEEK_SET);
    fread(&aux, sizeof(Producto), 1, fptr);
    if(aux.codigo == codigo){
        fseek(fptr, -sizeof(Producto), SEEK_CUR);
        aux = {-1,"",0,0};
        fwrite(&aux, sizeof(Producto), 1, fptr);
    }else{
        fseek(fptr, sizeof(Producto)*HASH_SIZE, SEEK_SET);
        bool encontrado = false;
        while(!encontrado && fread(&aux, sizeof(Producto), 1, fptr) == 1){
            if(aux.codigo == codigo){
                fseek(fptr, -sizeof(Producto), SEEK_CUR);
                aux = {-1,"",0,0};
                fwrite(&aux, sizeof(Producto), 1, fptr);
                encontrado = true;
            }
        }
        if(!encontrado){
            printf("El codigo ingresado no existe\n");
        }
    }
    fclose(fptr);
}

void mostrarStockBajo(int stockMin){
    Producto aux;
    FILE * fp = fopen("productos_ordenados.dat", "rb");
    if(fp == nullptr){
        printf("No se pudo abrir el archivo productos_ordenados.dat\n");
        exit(18);
    }
    while(fread(&aux, sizeof(Producto), 1, fp) == 1){
        if(aux.codigo != -1 && aux.stock < stockMin){
            mostrarDatosProducto(aux);
        }
    }
    fclose(fp);
}

void mostrarMenu(){
    printf("==============\n");
    printf("Menu Principal\n");
    printf("==============\n");
    printf("1.- Generar archivo de productos_recibidos.dat\n");
    printf("2.- Generar archivo productos.dat\n");
    printf("3.- Generar archivo productos_ordenados.dat\n");
    printf("4.- Mostrar datos de productos_recibidos.dat\n");
    printf("5.- Mostrar datos de producto.dat\n");
    printf("6.- Mostrar datos de productos_ordenados.dat\n");
    printf("7.- Buscar producto por codigo (productos_ordenados.dat)\n");
    printf("8.- Elimar producto por codigo (productos_ordenados.dat)\n");
    printf("9.- Mostrar stock menor a x (productos_ordneados.dat)\n");
    printf("0.- Para salir\n");
}

void menu(){
    int op, num;
    Cola c;
    do{
        mostrarMenu();
        printf("Ingrese la opcion: ");
        scanf("%i", &op);
        switch(op){
            case 1:
                recibirProductos();
                break;
            case 2:
                procesarProductos();
                break;
            case 3:
                c = crearColaProductos();
                guardarProductos(c);
                break;
            case 4:
                mostrarArchivoRecibidos();
                break;
            case 5:
                mostrarArchivoProductos();
                break;
            case 6:
                mostrarArchivoOrdenados();
                break;
            case 7:
                printf("Ingrese el codigo de un producto a buscar\n");
                scanf("%i", &num);
                mostrarProductoPorCodigo(num);
                break;
            case 8:
                printf("Ingrese el codigo de un producto a eliminar\n");
                scanf("%i", &num);
                eliminarProducto(num);
                break;
            case 9:
                printf("Ingrese el stock minimo de los productos a mostrar\n");
                scanf("%i", &num);
                mostrarStockBajo(num);
                break;
            case 0:
                printf("Saliendo...\n");
                break;
            default:
                printf("Ingresaste una opción erronea.\n");
                break;
        }
    }while(op != 0);
}