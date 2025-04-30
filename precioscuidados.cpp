// Punto 9 - Archivos secuenciales
#include <iostream>
#include <stdio.h>

#define CANT_P 10
#define CANT_C 7

struct Producto{
    int codigo;
    char descripcion[21];
    float precioComercio;
};

struct ProdPreciosCuid{
    int codigo;
    float precioCuidado;
};

void newFileProducto();
void newFilePreciosCuidao();
void listadoPreciosCuidados();
int noComercializa(); // Una funcion que retorna para variar y no hacer todo void :p

int main()
{
    newFileProducto();
    newFilePreciosCuidao();
    listadoPreciosCuidados();
    printf("Hay %i productos que estan en el plan de precios cuidados y no son comercializados.\n", noComercializa());
    return(0);
}

void newFileProducto(){
    FILE * fptr = fopen("Productos.dat", "wb");
    if(fptr == nullptr){
        printf("No se pudo abrir el archivo");
        exit(1);
    }
    Producto p[CANT_P] = {
        {101, "Leche", 150.75},
        {102, "Pan", 200.50},
        {103, "Azucar", 180.30},
        {104, "Arroz", 220.99},
        {105, "Aceite", 500.00},
        {106, "Harina", 140.25},
        {107, "Yerba", 750.80},
        {108, "Dulce de Leche", 450.60},
        {109, "Fideos", 190.90},
        {110, "Galletitas", 250.45}
    };
    fwrite(p, sizeof(Producto), CANT_P, fptr);
    fclose(fptr);
}

void newFilePreciosCuidao(){
    FILE * fptr = fopen("PreciosCuidados.dat", "wb");
    if(fptr == nullptr){
        printf("No se pudo abrir el archivo");
        exit(1);
    }
    ProdPreciosCuid p[CANT_C] = {
        {101, 140.00}, 
        {103, 170.00}, 
        {106, 130.00}, 
        {109, 180.00}, 
        {110, 120.00},
        {111, 150.00},
        {112, 500.00}  
    };
    fwrite(p, sizeof(ProdPreciosCuid), CANT_C, fptr);
    fclose(fptr);
}

void listadoPreciosCuidados(){
    Producto p;
    ProdPreciosCuid c;
    FILE * fileProductos = fopen("Productos.dat", "rb");
    FILE * filePrecios = fopen("PreciosCuidados.dat", "rb");
    if(fileProductos == nullptr || filePrecios == nullptr){
        printf("No se pudo abrir el archivo\n");
        exit(1);
    }
    printf("Productos que están en precios cuidados:\n");
    while(fread(&p, sizeof(Producto), 1, fileProductos) == 1){ // 110
        rewind(filePrecios);
        //fseek(filePrecios, 0, SEEK_SET); Hace lo mismo que la linea de arriba
        while(fread(&c, sizeof(ProdPreciosCuid), 1, filePrecios) == 1){
            if(p.codigo == c.codigo){
                printf("=====================\n");
                printf("Codigo: %i\nDescripcion: %s\nDiferencia: %.2f\n", p.codigo, p.descripcion, (p.precioComercio - c.precioCuidado));
            }
        } 
    }
    printf("=====================\n");
    fclose(filePrecios);
    fclose(fileProductos);
}

int noComercializa(){
    int count = 0;
    Producto p;
    ProdPreciosCuid c;
    FILE * fileProductos = fopen("Productos.dat", "rb");
    FILE * filePrecios = fopen("PreciosCuidados.dat", "rb");
    if(fileProductos == nullptr || filePrecios == nullptr){
        printf("No se pudo abrir el archivo\n");
        exit(1);
    }
    while(fread(&c, sizeof(ProdPreciosCuid), 1, filePrecios) == 1){
        bool encontrado = false;
        rewind(fileProductos);
        while(fread(&p, sizeof(Producto), 1, fileProductos) == 1){
            if(p.codigo == c.codigo){
                encontrado = true;
            }
        }
        if(!encontrado){
            count++;
        }
    }
    fclose(fileProductos);
    fclose(filePrecios);
    return(count);
}