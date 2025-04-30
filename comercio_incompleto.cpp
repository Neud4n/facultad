#include <iostream>
using namespace std;

#define CANT_PRO 2
#define CANT_T_PRO 2
#define MESES 2

struct producto{
    int codPro;
    int cantPro;
    int tipoPro;
    int uniExportadas = 0;
};
    
struct exportaciones{
    int containers;
    int cantReg;
};

// ActualizacionRegistrosExportaciones --> Esta funcion no la hago porque carece de logica.
void setProductos(producto []);
int getIndexProd(producto [], int, int);
bool rangoOk(int, int, int);
void inicializarMatriz(int [][MESES], int , int, int);
void inicializarMatriz(exportaciones [][MESES], int , int, int);
void setCargarDatos(producto [], exportaciones [][MESES], int [][MESES]);
bool hayDatos();
bool validarRango(int, int, int);
void informaUnProducto(producto []);
void informaTodososProductos(producto []);
void informe(producto [], exportaciones [][MESES], int [][MESES]);

int main()
{
    producto productos[CANT_PRO]; 
    setProductos(productos);
    exportaciones productoMes[CANT_PRO][MESES];
    int tipoProdMes[CANT_T_PRO][MESES];
    inicializarMatriz(productoMes, CANT_PRO, MESES, 0);
    inicializarMatriz(tipoProdMes, CANT_T_PRO, MESES, 0);
    setCargarDatos(productos, productoMes, tipoProdMes);
    informe(productos, productoMes, tipoProdMes);
}

int getIndexProd(producto vec[], int dim, int target){
    int i = 0;
    while(i < dim && vec[i].codPro != target){
        i++;
    }
    if(i == dim){
        return(-999);
    }else{
        return(i);
    }
}

void setProductos(producto vec[]){
    int index; bool rango;
    for(int i = 0; i < CANT_PRO; i++){
        do{
            printf("Ingrese el codigo del producto\n");
            scanf("%i", &vec[i].codPro);
            index = getIndexProd(vec, i, vec[i].codPro);
            if(index != -999){
                printf("ERROR: El codigo de producto %i ya existe.\n", vec[i].codPro);
            }
        }while(index != -999);
        do{
            printf("Ingrese la cantidad de productos\n");
            scanf("%i", &vec[i].cantPro);
        }while(vec[i].cantPro <= 0);
        do{
            printf("Ingrese el tipo de producto\n");
            printf("[1] - MUEBLE [2] - TECH [3] - ELECTRO [4] - LIMPIEZA\n");
            scanf("%i", &vec[i].tipoPro);
            rango = rangoOk(vec[i].tipoPro, 1, CANT_T_PRO);
            if(!rango){
                printf("ERROR: Opcion ingresada invalida\n");
            }
        }while(!rango);
    }
}

bool rangoOk(int num, int desde, int hasta){
    return((num >= desde) && (num <= hasta));
}

void inicializarMatriz(int mat[][MESES], int f, int c, int num){
    for(int i = 0; i < f; i++){
        for(int j = 0; j < c; j++){
            mat[i][j] = num;
        }
    }
}

void inicializarMatriz(exportaciones mat[][MESES], int f, int c, int num){
    /*
        Esta funcion se podria eliminar haciendo:
        struct exportaciones{
            int containers = 0;
            int cantReg = 0;
        };
    */
    for(int i = 0; i < f; i++){
        for(int j = 0; j < c; j++){
            mat[i][j].containers = num;
            mat[i][j].cantReg = num;
        }
    }
}

bool validarRango(int num, int desde, int hasta){
    return((num >= desde) && (num <= hasta));
}

bool hayDatos(){
    int resp;
    bool rango;
    do{
        printf("Hay datos para cargar? [1] - SI | [0] - NO\n");
        scanf("%i", &resp);
        rango = validarRango(resp, 0 , 1);
        if(!rango){
            printf("La respuesta %i es invalida.\n", resp);
        }
    }while(!rango);
    if(resp == 1){
        return true;
    } else {
        return false;
    }
}

void setCargarDatos(producto vec[], exportaciones matExpo[][MESES], int matTipo[][MESES]){
    bool rango;
    int codPro, indexPro, mes, cantUni, cantCon;
    while(hayDatos()){
        do{
            printf("Ingrese el codigo del producto\n"); // cout<<"Ingrese el codigo del producto"<<endl;
            scanf("%i", &codPro); // cin>>codPro;
            indexPro = getIndexProd(vec, CANT_PRO, codPro);
            if(indexPro == -999){
                printf("ERROR: El codigo %i no existe\n", codPro);
            }
        }while(indexPro == -999);
        do{
            printf("Ingrese el mes\n");
            scanf("%i", &mes);
            rango = validarRango(mes, 1, 3);
            if(!rango){
                printf("ERROR: El mes %i es invalido.\n", mes);
            }
        }while(!rango);
        mes--; // Corrijo el mes para que este relacionado a la matriz.
        do{
            printf("Ingrese la cantidad de unidades\n");
            scanf("%i", &cantUni);
            if(cantUni <= 0){
                printf("ERROR: La cantidad debe ser mayor a 0.");
            }
        }while(cantUni <= 0);
        //matExpo[indexPro][mes].uniExportadas = matExpo[indexPro][mes].uniExportadas + cantUni; Es lo mismo.
        vec[indexPro].uniExportadas += cantUni;
        do{
            printf("Ingrese la cantidad de containers\n");
            scanf("%i", &cantCon);
            if(cantUni <= 0){
                printf("ERROR: La cantidad debe ser mayor a 0.\n");
            }
        }while(cantCon <= 0);
        matExpo[indexPro][mes].containers += cantUni;
        matExpo[indexPro][mes].cantReg++;
        matTipo[vec[indexPro].tipoPro-1][mes] += cantUni;
    }
}

void informaUnProducto(producto vecPro){
    printf("Producto %i\n", vecPro.codPro);
    printf("* Tipo de producto: %i\n", vecPro.tipoPro);
    printf("* Cantidad Producto: %i\n", vecPro.cantPro);
    printf("* Cantidad de unidades exportadas: %i\n", vecPro.uniExportadas);
}

void informaTodososProductos(producto vecPro[]){
    for(int i = 0; i < CANT_PRO; i++){
        informaUnProducto(vecPro[i]);
    }
}

void informe(producto vecPro[], exportaciones matExpo[][MESES], int matTipo[][MESES]){
    // PUNTO 1
    printf("=======================\n");
    printf("INFORME - CANT REG\n");
    printf("=======================\n");
    for(int i = 0; i<CANT_PRO; i++){
        printf("Producto %i\n", vecPro[i].codPro);
        for(int j = 0; j<MESES; j++){
            printf("* Mes %i - Cant Reg: %i\n", j+1, matExpo[i][j].cantReg);
        }
    }
    // PUNTO 2
    printf("==========================\n");
    printf("INFORME - CANT UNI X TIPO\n");
    printf("==========================\n");
    for(int i = 0; i < CANT_T_PRO; i++){
        printf("Tipo de producto %i\n", i+1);
        for(int j = 0; j < MESES; j++){
            printf("* Mes %i - Cant unidades exportadas: %i\n", j+1, matTipo[i][j]);
        }
    }
    // PUNTO 3
    printf("===============================\n");
    printf("INFORME - CANT CONTAINERS EXPO\n");
    printf("===============================\n");
    for(int i = 0; i<CANT_PRO; i++){
        printf("Producto %i\n", vecPro[i].codPro);
        for(int j = 0; j<MESES; j++){
            printf("* Mes %i - Cant Containers: %i\n", j+1, matExpo[i][j].containers);
        }
    }
    // PUNTO 4
    printf("=========================\n");
    printf("INFORME - DATOS PRODUCTOS\n");
    printf("=========================\n");
    informaTodososProductos(vecPro);
    // PUNTO 5
}