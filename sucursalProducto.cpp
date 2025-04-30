#include <stdio.h>
using namespace std;

#define CANT_SUC 2
#define CANT_PRO 2

struct sucursal{
	int id;
};

struct producto{
	int cod;
	int stock;
	int price;
};

void inicializarMatriz(int [][CANT_PRO], int);
int getIndexSucursal(sucursal [], int, int);
int getIndexProducto(producto [], int, int);
void setData(sucursal []);
void setData(producto []);
bool validarRango(int, int, int);
bool hayDatos();
void setDatosMatriz(int [][CANT_PRO], sucursal [], producto []);
void informe(int [][CANT_PRO], sucursal [], producto []);
void mayorVenta(int [], int [][CANT_PRO]); // Devuelve un vector con los indices del producto que mas se vendio x sucursal.

int main()
{
	sucursal vecSuc[CANT_SUC];
	producto vecPro[CANT_PRO];
	int ventas[CANT_SUC][CANT_PRO];
	inicializarMatriz(ventas, 0);
	setData(vecSuc);
	setData(vecPro);
	setDatosMatriz(ventas, vecSuc, vecPro);
	informe(ventas, vecSuc, vecPro);
}

void inicializarMatriz(int mat[][CANT_PRO], int num){
	for(int i = 0; i < CANT_SUC; i++){
		for(int j = 0; j < CANT_PRO; j++){
			mat[i][j] = num;
		}
	}
}

int getIndexSucursal(sucursal vec[], int dim, int target){
	int i = 0;
	while(i < dim && vec[i].id != target){
		i++;
	}
	if(i == dim){
		return(-999);
	}
	return(i);
}

void setData(sucursal vec[]){
	int index;
	for(int i = 0; i < CANT_SUC; i++){
		do{
			printf("Ingrese el ID de la sucursal\n");
			scanf("%i", &vec[i].id);
			index = getIndexSucursal(vec, i, vec[i].id);
			if(index != -999){
				printf("ERROR: El ID %i ya existe\n", vec[i].id);
			}
		}while(index != -999);
	}	
}

bool validarRango(int num, int desde, int hasta){
	return((num >= desde) && (num <= hasta));
}

int getIndexProducto(producto vec[], int dim, int target){
	int i = 0;
	while(i < dim && vec[i].cod != target){
		i++;
	}
	if(i == dim){
		return(-999);
	}
	return(i);
}

void setData(producto vec[]){
	int index;
	bool rango;
	for(int i = 0; i < CANT_PRO; i++){
		do{
			do{
				printf("Ingrese el codigo del producto\n");
				scanf("%i", &vec[i].cod);
				rango = validarRango(vec[i].cod, 1000, 10000);
				if(!rango){
					printf("ERROR: El codigo debe estar entre [1000 - 10000]\n");
				}
			}while(!rango);
			index = getIndexProducto(vec, i, vec[i].cod);
			if(index != -999){
				printf("ERROR: El codigo %i ya existe\n", vec[i].cod);
			}
		}while(index != -999);
		do{
			printf("Ingrese el stock del producto\n");
			scanf("%i", &vec[i].stock);
			if(vec[i].stock <= 0){
				printf("ERROR: El stock debe ser mayor a cero.\n");
			}
		}while(vec[i].stock <= 0);
		do{
			printf("Ingrese el precio unitario del producto\n");
			scanf("%i", &vec[i].price);
			if(vec[i].price <= 0){
				printf("ERROR: El precio unitario debe ser superior a cero.\n");
			}
		}while(vec[i].price <= 0);
	}
}

bool hayDatos(){
	int resp;
	bool rango;
	do{
		printf("Hay datos para ingresar? SI [1] | NO [0]\n");
		scanf("%i",&resp);
		rango = validarRango(resp, 0, 1);
		if(!rango){
			printf("ERROR: Respuesta invalida\n");
		}
	}while(!rango);
	if(resp == 1){
		return(true);
	}
	return(false);
}

void setDatosMatriz(int mat[][CANT_PRO], sucursal vecSuc[], producto vecPro[]){
	int indexSuc, indexPro, codSuc, codPro, venta;
	bool rango;
	while(hayDatos()){
		do{
			printf("Ingrese el id de la sucursal\n");
			scanf("%i", &codSuc);
			indexSuc = getIndexSucursal(vecSuc, CANT_SUC, codSuc);
			if(indexSuc == -999){
				printf("ERROR: La sucursal no existe\n");
			}
		}while(indexSuc == -999);
		do{
			do{
				printf("Ingrese el codigo del producto\n");
				scanf("%i", &codPro);	
				rango = validarRango(codPro, 1000, 10000);
				if(!rango){
					printf("ERROR: El codigo debe estar entre [1000 - 10000]\n");
				}
			}while(!rango);
			indexPro = getIndexProducto(vecPro, CANT_PRO, codPro);
		}while(indexPro == -999);
		do{
			printf("Ingrese la cantidad vendida\n");
			scanf("%i", &venta);
			if(venta <= 0){
				printf("ERROR: La cantidad vendida debe ser mayora  0\n");
			}
		}while(venta <= 0);
		mat[indexSuc][indexPro]+= venta;
	}
}

void mayorVenta(int vec[], int mat[][CANT_PRO]){
	int maxVenta; bool flag;
	for(int i = 0; i < CANT_SUC; i++){
		flag = false;
		for(int j = 0; j < CANT_PRO; j++){
			/*
				Hago esta validacion con un flag porque se puede dar el caso
				en el que una sucursal no venda ningun producto.
			*/
			if(flag == false && mat[i][j] != 0){
				flag = true;
				vec[i] = j;
				maxVenta = mat[i][j];
			} else if(flag && maxVenta < mat[i][j]){
				maxVenta = mat[i][j];
				vec[i] = j;
			} else if(flag == false && j == CANT_PRO-1){ 
				vec[i] = -999; // Si es -999 significa que la sucursal no tuvo ventas.
			}
		}
	}
}

void informe(int mat[][CANT_PRO], sucursal vecSuc[], producto vecPro[]){
	int productoMayorVenta[CANT_SUC];
	/*
		El vector productoMayorVenta tiene una doble asociacion.
		Los indices del vector estan directamente relacionados con cada sucursal.
		El entero dentro del vector esta relacionado al indice del vector de productos.
	*/
	// PUNTO 1
	printf("=========================================\n");
	printf("INFORME - Producto mas vendido x sucursal\n");
	printf("=========================================\n");
	mayorVenta(productoMayorVenta, mat);
	for(int i = 0; i < CANT_SUC; i++){
		if(productoMayorVenta[i] != -999){
			printf("Sucursal %i - Producto mas vendido: %i\n", vecSuc[i].id, vecPro[productoMayorVenta[i]].cod);
		} else {
			printf("Sucursal %i - No tuvo ventas\n", vecSuc[i].id);
		}
	}
	// PUNTO 2
	printf("====================================================\n");
	printf("INFORME - Promedio de importe recaudado por producto\n");
	printf("====================================================\n");
	int sum;
	for(int i = 0; i < CANT_PRO; i++){
		sum = 0;
		for(int j = 0; j < CANT_SUC; j++){
			sum+=mat[j][i];
		}
		printf("El producto %i - Promedio recaudado: %i\n", vecPro[i].cod, (sum/CANT_SUC));
	}
	// PUNTO 3
	printf("====================================================\n");
	printf("INFORME - Promedio de importe recaudado por producto\n");
	printf("====================================================\n");
	int ganancia;
	for(int i = 0; i < CANT_SUC; i++){
		ganancia = 0;
		for(int j = 0; j < CANT_PRO; j++){
			ganancia += (mat[i][j]*vecPro[j].price)*0.25;
		}
		printf("Sucursal %i - Ganancia total: %i\n", vecSuc[i].id, ganancia);
	}
}