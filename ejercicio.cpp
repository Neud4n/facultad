# Booring asf
#include <iostream>
using namespace std;

int main(){
    int n[5], sum, sumPosPar, sumPosImpar, sumContPosPar, target, conTarget;
    sum = 0;
    sumPosPar = 0;
    sumPosImpar = 0;
    sumContPosPar = 0;
    conTarget = 0;
    float prom;
    printf("Ingrese el target\n");
    cin>>target;
    for(int i = 0; i<5; i++){
        printf("Ingrese un valor\n");
	cin>>n[i];
	sum+=n[i];
	if(i % 2 == 0){
	    sumPosPar+=n[i];
	    if(n[i] > 0){
	        sumContPosPar+= n[i];
	    }
	} else {
	    sumPosImpar+=n[i];
	}
	if(n[i] == target){
	    conTarget++;
	}
    }
    printf("La suma de todos los valores es: %i\n", sum);
    prom = (float) sum / 5;
    printf("El promedio es: %.2f\n", prom);
    printf("La suma de los elementos en posicion par es: %i\n", sumPosPar);
    printf("La suma de los elementos en posicion impar es: %i\n", sumPosImpar);
    printf("La suma de los elementos positivos en posicion par es: %i\n", sumContPosPar);
    for(int i = 4; i >= 0; i--){
	printf("Valor en la posición %i es %i\n", i, n[i]);
    }
    printf("Las veces que aparece el target %i es: %i\n",target, conTarget);
    return(0);
}
