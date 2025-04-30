// This looks harder than it is
// TP1 - ARCHIVOS SECUENCIALES - Hecho hasta el punto 5.
#include <iostream>
#include <stdio.h>
using namespace std;

typedef struct Producto{
    int cod;
    char descripcion[50];
    int stock;
    int precio;
}Producto;

void newProduct(); // Crea un nuevo registro en el archivo
bool hayDatos(); // Valida si hay mas datos para cargar
void setDatos(Producto &); // Prepara los datos para guardar en el archivo
void getProducts(char []); // Lista todos los registros del archivo
void createRepo(); // Crea un archivo con los productos que tengan Stock = 0
void modificarPrecios();


int main(){
    newProduct();
    printf("==========\n");
    printf("Productos:\n");
    printf("==========\n");
    getProducts((char*)"Producto.dat");
    createRepo();
    printf("====================\n");
    printf("Productos sin STOCK:\n");
    printf("====================\n");
    getProducts((char*)"Reposicion.dat");
    printf("=========================\n");
    printf("Quiere modificar precios?:\n");
    printf("=========================\n");
    modificarPrecios();
    printf("====================\n");
    printf("Precios modificados:\n");
    printf("====================\n");
    getProducts((char*)"Producto.dat");
    return(0);
}

bool hayDatos(){
    int resp;
    do{
        printf("Hay datos para cargar? Si - [1] | No - [0]\n");
        scanf("%i", &resp);
    }while(resp != 1 && resp != 0);
    return(resp == 1);
}

void newProduct(){
    Producto p;
    FILE *fptr = fopen("Producto.dat", "ab");
    if(fptr == nullptr){
        printf("Error: No se pudo crear el o abrir el archivo.\n");
        exit(1);
    }
    while(hayDatos()){
        setDatos(p);
        fwrite(&p, sizeof(Producto), 1, fptr);
    }
    fclose(fptr);
}

void getProducts(char filename[]){
    Producto p;
    FILE *fptr = fopen(filename, "rb");
    if(fptr == nullptr){
        printf("ERROR: El archivo no existe\n");
        exit(1);
    }else{
        while(fread(&p, sizeof(Producto), 1, fptr) == 1){
            printf("Codigo: %i\n", p.cod);
            printf("Descripcion: %s\n", p.descripcion);
            printf("Precio: %i\n", p.precio);
            printf("Stock: %i \n", p.stock);
        }
        fclose(fptr);
    }
}

void setDatos(Producto &p){
    printf("Ingrese el codigo del producto\n");
    scanf("%i", &p.cod);
    printf("Ingrese la descripcion\n");
    scanf("%49s", p.descripcion);
    printf("Ingrese el stock\n");
    scanf("%i", &p.stock);
    printf("Ingrese el precio\n");
    scanf("%i", &p.precio);
}

void createRepo(){
    Producto p;
    FILE *fptr = fopen("Producto.dat", "rb");
    if(fptr == nullptr){
        printf("ERROR: El archivo no existe\n");
        exit(1);
    }
    FILE *newFile = fopen("Reposicion.dat", "wb");
    if(newFile == nullptr){
        printf("ERROR: Hubo un problema durante la creación\n");
        exit(1);
    }
    while(fread(&p, sizeof(Producto), 1, fptr) == 1){
        if(p.stock == 0){
            fwrite(&p, sizeof(Producto), 1, newFile);
        }
    }
    fclose(fptr);
    fclose(newFile);
}

void modificarPrecios(){
    Producto p;
    int cod;
    FILE * fptr = fopen("Producto.dat", "rb+");
    if(fptr == nullptr){
        printf("El archivo no existe / No se pudo abrir\n");
        exit(1);
    }
    while(hayDatos()){
        do{
            printf("Ingese un codigo de producto\n");
            scanf("%i", &cod);
            while(fread(&p, sizeof(Producto), 1, fptr) == 1 && cod != p.cod){}
            if(cod != p.cod){
                printf("El codigo ingresado no existe.\n");
                rewind(fptr); // Hace lo mismo que la linea de abajo, pero mas clean.
                //fseek(fptr, 0, SEEK_SET);
            }
        }while(cod != p.cod);
        fseek(fptr, -sizeof(Producto), SEEK_CUR);
        printf("Ingrese el nuevo precio del Producto\n");
        scanf("%i", &p.precio);
        fwrite(&p, sizeof(Producto), 1, fptr);
    }
    fclose(fptr);
}