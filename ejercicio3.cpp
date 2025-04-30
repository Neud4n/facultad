// I'm not proud about this shitty code.
#include <iostream>
using namespace std;

int main(){
    int numbers[20] = {0}, posNumbers[20];
    int i ,n, j, k;
    n = 0; j = 0; k = 0;
    while(n != -1 && j < 20){
        do{
            cout<<"Ingrese un número positivo"<<endl;
            cin>>n;
            if((n != -1) && ((n < 1))){
                cout<<"ERROR: Debe ingresar un valor valido."<<endl;
            }
        }while((n != -1) && (n < 1));
        if(n != -1){
            k = 0;
            i = rand() % 20;
            do{ // Evito que se repitan indices.
                if(i != posNumbers[k]){
                    k++;
                } else { // Si el indice ya existe en el array, crea uno nuevo y verifica otra vez.
                    k = 0;
                    i = rand() % 20;
                }
            }while(k < j);
            numbers[i] = n;
            posNumbers[j] = i;
            j++;
        }
    }
    if(j>0){
        k = 0;
        do{
            cout<<"Se ingresó el dato "<<numbers[posNumbers[k]]<<" en la posición: "<<posNumbers[k]<<endl;
            k++;
        }while(k < j);
        k = 0;
        do{
            if(numbers[k] == 0){
                cout<<"No se ingresó ningún valor en la posición: "<<k<<endl;
            }
            k++;
        }while(k < 20);
    } 
    return(0);
}