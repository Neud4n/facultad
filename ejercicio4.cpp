// Let's see what comes from this.
#include <iostream>
using namespace std;

int main(){
    int numeros[10] = {0}, posMaxNum[10];
    int i = 0, n, maxNum, j = 0, k = 0;
    for(i;i<10;i++){
        do{
            cout<<"Ingrese un número"<<endl;
            cin>>numeros[i];
            if(numeros[i]<1){
                cout<<"ERROR: Debe ser un número positivo."<<endl;
            }
        }while(numeros[i] < 1);
        if(i == 0){
            maxNum = numeros[i];
            posMaxNum[j] = i;
            j++;
        } else if(maxNum < numeros[i]){
            j = 0;
            posMaxNum[j] = i;
            maxNum = numeros[i];
            j++;
        } else if(maxNum == numeros[i]){
            posMaxNum[j] = i;
            j++;
        }
    }
    k = 0;
    cout<<"El número máximo "<<maxNum<<" está en las posiciones: ";
    for(k; k < j; k++){
        cout<<posMaxNum[k]<<" ";
    }
    cout<<endl;
    return(0);
}