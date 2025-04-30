// TP2 Archivos de Accesos directos EJ1, EJ2 y EJ3 
#include <iostream>
#include <stdlib.h>

#define HASH_SIZE 500

struct Producto{
    int cod;
    char des[25];
    float precio;
    int stock;
};

struct Compra{
    int cod;
    int cantidad;
};

struct Pedido{
    int codProducto;
    int cliente;
    int cantPedida;
};

void newFileProductos();
void agregarProducto();
void agregarCompras();
void setDatosProducto(Producto &);
void setDatosCompras(Compra &);
void setDatosPedido(Pedido &);
bool validarExistencia(int);
void getProducto();
int getHash(int);
void modificarPrecio(); 
void getAllProducts();
void menu();
void mostrarMenu();
bool seguir();
void actualizoStock();
void crearPedidos();

int main()
{
    newFileProductos();
    menu();
    return 0;
}

void newFileProductos(){
    Producto p;
    FILE * fptr = fopen("./Productos.dat", "wb");
    if(fptr == nullptr){
        printf("No se pudo abrir el archivo\n");
        exit(1);
    }
    p.cod = -1;
    for(int i = 0; i < HASH_SIZE; i++){
        fwrite(&p, sizeof(Producto), 1, fptr);
    }
    fclose(fptr);
}

int getHash(int cod){
    return cod % HASH_SIZE;
}

void agregarProducto(){
    Producto p, aux;
    setDatosProducto(p);
    int pos = getHash(p.cod);
    FILE * fptr = fopen("./Productos.dat", "rb+");
    if(fptr == nullptr){
        printf("No se pudo abrir el archivo\n");
        exit(1);
    }
    fseek(fptr, sizeof(Producto)*pos, SEEK_SET);
    fread(&aux, sizeof(Producto), 1, fptr);
    if(aux.cod == -1){
        fseek(fptr, -sizeof(Producto), SEEK_CUR);
        fwrite(&p, sizeof(Producto), 1, fptr);
    }else{
        fseek(fptr, sizeof(Producto)*HASH_SIZE, SEEK_SET);
        bool encontrado = false;
        while(!encontrado && fread(&aux, sizeof(Producto), 1, fptr) == 1){
            if(aux.cod == -1){
                encontrado = true;
                fseek(fptr, -sizeof(Producto), SEEK_CUR);
                fwrite(&p, sizeof(Producto), 1, fptr);
            }
        }
        if(!encontrado){
            fwrite(&p, sizeof(Producto), 1, fptr);
        }
    }
    fclose(fptr);
}

void setDatosProducto(Producto &p){
    bool existe;
    do{
        printf("Ingrese el codigo del producto\n");
        scanf("%i", &p.cod);
        existe = validarExistencia(p.cod);
        if(p.cod == -1){
            printf("ERROR: El codigo debe ser diferente a -1\n");
        }else if(existe){
            printf("ERROR: El código %i ya existe.\n", p.cod);
        }
    }while(existe || p.cod == -1);
    printf("Ingrese la descripcion del producto\n");
    scanf("%s", p.des);
    printf("Ingrese el precio del producto\n");
    scanf("%f", &p.precio);
    printf("Ingrese el stock del producto\n");
    scanf("%i", &p.stock);
}

// Para esta funcion tal vez convendria modificarla para pasarle por referencia
// Un bool y un int, donde el bool es para determinar si se encontro el producto
// tal cual como hace ahora. Y el INT devolvería la posición del registro.
// Así tal vez facilita un la escritura o lectura de algunos productos ahorrando lineas de codigo
// PERO, también me dio paja corregirlo. Así como esta funciona ok.

bool validarExistencia(int target){
    Producto p;
    FILE * fptr = fopen("Productos.dat", "rb");
    if(fptr == nullptr){
        printf("No se pudo abrir el archivo.\n");
        exit(1);
    }
    int pos = getHash(target);
    fseek(fptr, sizeof(Producto)*pos, SEEK_SET);
    fread(&p, sizeof(Producto), 1, fptr);
    bool encontrado = false;
    if(p.cod == target){
        encontrado = true;
    }else{
        fseek(fptr, sizeof(Producto)*HASH_SIZE, SEEK_SET);
        while(!encontrado && fread(&p, sizeof(Producto), 1, fptr) == 1){
            if(p.cod == target){
                encontrado = true;
            }
        }
    }
    fclose(fptr);
    return encontrado;
}

void getProducto(){
    Producto p, aux;
    bool existe;
    do{
       printf("Ingrese el codigo del producto\n");
       scanf("%i", &aux.cod);
       existe = validarExistencia(aux.cod);
       if(!existe){
        printf("ERROR: El codigo ingresado no existe.\n");
       }
    }while(!existe);
    int pos = getHash(aux.cod);
    FILE * fptr = fopen("Productos.dat", "rb");
    fseek(fptr, sizeof(Producto)*pos, SEEK_SET);
    fread(&p, sizeof(Producto), 1, fptr);
    if(p.cod == aux.cod){
        printf("============\n");
        printf("Codigo: %i\n", p.cod);
        printf("Descripcion: %s\n", p.des);
        printf("Precio: %.2f\n", p.precio);
        printf("Stock: %i\n", p.stock);
    }else{
        existe = false;
        fseek(fptr, sizeof(Producto)*HASH_SIZE, SEEK_SET);
        while(!existe && fread(&p, sizeof(Producto), 1, fptr) == 1){
            if(p.cod == aux.cod){
                printf("============\n");
                printf("Codigo: %i\n", p.cod);
                printf("Descripcion: %s\n", p.des);
                printf("Precio: %.2f\n", p.precio);
                printf("Stock: %i\n", p.stock);
                printf("============\n");
                existe = true;
            }
        }
    }
}

// Para revisar:
// Si aún no se creo un producto, esta funcion no debería ser ejecutada.
// Entra en un loop infinito donde no podes salir a menos que uses -1 como codigo
// PERO, termina sin convencerme.
// Una posible solucion es hacer antes de todo un count de los registros != de -1
// Y si eso encuentra al menos 1 registro que devuelva un true.
// Pero es una solucion muy peruana, y me da paja pensar en otra cosa.

void modificarPrecio(){
    Producto p, aux;
    bool existe = false;
    do{
        printf("Ingrese el codigo de producto\n");
        scanf("%i", &aux.cod);
        existe = validarExistencia(aux.cod);
        if(!existe){
            printf("ERROR: El codigo no existe.\n");
        }
    }while(!existe);
    FILE * fptr = fopen("Productos.dat", "rb+");
    if(fptr == nullptr){
        printf("No se pudo abrir el archivo.\n");
        exit(1);
    }
    int pos = getHash(aux.cod);
    fseek(fptr, sizeof(Producto)*pos, SEEK_SET);
    fread(&p, sizeof(Producto), 1, fptr);
    if(p.cod == aux.cod){
        fseek(fptr, -sizeof(Producto), SEEK_CUR);
        printf("Ingrese el nuevo precio\n");
        scanf("%f", &p.precio);
        fwrite(&p, sizeof(Producto), 1, fptr);
    }else{
        existe = false;
        fseek(fptr, sizeof(Producto)*HASH_SIZE, SEEK_SET);
        while(!existe && fread(&p, sizeof(Producto), 1, fptr) == 1){
            if(p.cod == aux.cod){
                fseek(fptr, -sizeof(Producto), SEEK_CUR);
                printf("Ingrese el nuevo precio\n");
                scanf("%f", &p.precio);
                fwrite(&p, sizeof(Producto), 1, fptr);
                existe = true;
            }
        }
    }
    fclose(fptr);
}

void getAllProducts(){
    Producto p;
    FILE * fptr = fopen("Productos.dat", "rb");
    if(fptr == nullptr){
        printf("No se pudo abrir el archivo\n");
        exit(1);
    }
    int n = 0;
    while(fread(&p, sizeof(Producto), 1, fptr) == 1){
        if(p.cod != -1){
            printf("============\n");
            printf("Codigo: %i\n", p.cod);
            printf("Descripcion: %s\n", p.des);
            printf("Precio: %.2f\n", p.precio);
            printf("Stock: %i\n", p.stock);
            printf("Posicion: %i\n", n);
            printf("============\n");           
        }
        n++;
    }
    fclose(fptr);
}

void mostrarMenu(){
    printf("===============\n");
    printf("Menu Principal\n");
    printf("===============\n");
    printf("1. Agregar producto\n");
    printf("2. Modificar precio producto\n");
    printf("3. Mostrar datos producto\n");
    printf("4. Mostrar todos los productos\n");
    printf("5. Agregar compras y actualizar stock.\n");
    printf("6. Realizar pedidos de clientes.\n");
    printf("0. Salir\n");
}

void menu(){
    int opcion;
    do{
        mostrarMenu();
        printf("Opcion: ");
        scanf("%i", &opcion);
        switch(opcion){
            case 1:
                agregarProducto();
                break;
            case 2:
                modificarPrecio();
                break;
            case 3:
                getProducto();
                break;
            case 4:
                getAllProducts();
                break;
            case 5:
                agregarCompras();
                actualizoStock();
                break;
            case 6:
                crearPedidos();
                break;
            case 0:
                printf("Saliendo...\n");
                break;
            default:
                printf("Opcion invalida. Intente de nuevo\n");
        }
    }while(opcion != 0);
}

void agregarCompras(){
    Compra c;
    FILE * fileCompras = fopen("Compras.dat", "wb");
    if(fileCompras == nullptr){
        printf("No se pudo crear el archivo\n");
        exit(1);
    }
    do{
        setDatosCompras(c);
        fwrite(&c, sizeof(Compra), 1, fileCompras);
    }while(seguir());
    fclose(fileCompras);
}

void setDatosCompras(Compra &c){
    bool existe;
    do{
        printf("Ingrese el codigo del producto.\n");
        scanf("%i", &c.cod);
        existe = validarExistencia(c.cod);
        if(c.cod == -1){
            printf("ERROR: El codigo debe ser diferente a -1\n");
        }else if(!existe){
            printf("ERROR: El código %i no existe.\n", c.cod);
        }
    }while(!existe || c.cod == -1);
    printf("Ingrese la cantidad comprada\n");
    scanf("%i", &c.cantidad);
}

bool seguir(){
    int resp;
    do{
        printf("Hay mas para cargar? 1 - [SI] | 0 - [NO]\n");
        scanf("%i", &resp);
        if(resp != 1 && resp != 0){
            printf("Opcion invalida.\n");
        }
    }while(resp != 1 && resp != 0);
    return(resp == 1);
}

void actualizoStock(){
    Compra c;
    Producto p;
    FILE * fCompras = fopen("Compras.dat", "rb");
    FILE * fProductos = fopen("Productos.dat", "rb+");
    if(fCompras == nullptr || fProductos == nullptr){
        printf("No se pudo abrir el archivo\n");
        exit(1);
    }
    while(fread(&c, sizeof(Compra), 1, fCompras) == 1){
        int pos = getHash(c.cod);
        fseek(fProductos, sizeof(Producto)*pos, SEEK_SET);
        fread(&p, sizeof(Producto), 1, fProductos);
        if(c.cod == p.cod){
            fseek(fProductos, -sizeof(Producto), SEEK_CUR);
            p.stock+= c.cantidad;
            fwrite(&p, sizeof(Producto), 1, fProductos);
        }else{
            fseek(fProductos, sizeof(Producto)*HASH_SIZE, SEEK_SET);
            bool encontrado = false;
            while(!encontrado && fread(&p, sizeof(Producto), 1, fProductos) == 1){
                if(p.cod == c.cod){
                    fseek(fProductos, -sizeof(Producto), SEEK_CUR);
                    p.stock+= c.cantidad;
                    fwrite(&p, sizeof(Producto), 1, fProductos);
                    encontrado = true;
                }
            }
        }
    }
    fclose(fCompras);
    fclose(fProductos);
}

void crearPedidos(){
    Pedido p, noSafisfecho;
    Producto prod;
    FILE * fPedido = fopen("Pedidos.dat", "wb");
    FILE * fProducto = fopen("Productos.dat", "rb+");
    FILE * fnoSafisfecho = fopen("Pedidos_no_safisfechos.dat", "wb");
    if(fPedido == nullptr || fProducto == nullptr || fnoSafisfecho == nullptr){
        printf("No se pudo abrir el archivo\n");
        exit(1);
    }
    int nroPedido = 0;
    do{
        setDatosPedido(p);
        fwrite(&p, sizeof(Pedido), 1, fPedido);
        int pos = getHash(p.codProducto);
        fseek(fProducto, sizeof(Producto)*pos, SEEK_SET);
        fread(&prod, sizeof(Producto), 1, fProducto);
        if(p.codProducto == prod.cod){
            if(prod.stock >= p.cantPedida){
                prod.stock-= p.cantPedida;
                fseek(fProducto, -sizeof(Producto), SEEK_CUR);
                fwrite(&prod, sizeof(Producto), 1, fProducto);
            }else{
                noSafisfecho = p;
                fwrite(&noSafisfecho, sizeof(Pedido), 1, fnoSafisfecho);
            }
        }else{
            bool encontrado = false;
            fseek(fProducto, sizeof(Producto)*HASH_SIZE, SEEK_SET);
            while(!encontrado & fread(&prod, sizeof(Producto), 1, fProducto) == 1){
                if(p.codProducto == prod.cod){
                    encontrado = true;
                    if(prod.stock >= p.cantPedida){
                        prod.stock-= p.cantPedida;
                        fseek(fProducto, -sizeof(Producto), SEEK_CUR);
                        fwrite(&prod, sizeof(Producto), 1, fProducto);
                    }else{
                        noSafisfecho = p;
                        fwrite(&noSafisfecho, sizeof(Pedido), 1, fnoSafisfecho);
                    }
                }
            }
        }
    }while(seguir());
    fclose(fPedido);
    fclose(fnoSafisfecho);
    fclose(fProducto);
}

void setDatosPedido(Pedido &p){
    bool existe;
    do{
        printf("Ingrese el codigo del producto\n");
        scanf("%i", &p.codProducto);
        existe = validarExistencia(p.codProducto);
        if(!existe){
            printf("ERROR: El codigo ingresado no existe.\n");
        }
    }while(!existe);
    printf("Ingrese el codigo del cliente\n");
    scanf("%i", &p.cliente);
    printf("Ingrese la cantidad pedida\n");
    scanf("%i", &p.cantPedida);
}