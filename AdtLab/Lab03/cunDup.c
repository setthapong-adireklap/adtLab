#include <stdio.h>

int main(){

    int i, nloop;
    scanf("%d", &nloop);

    // input
    int arrayNum[100] = {0}, temp;
    for(i=0; i<nloop ;i++){
        scanf("%d", &temp);
        arrayNum[temp-1] += 1;
    }

    // loop for find max number 
    int check = 1;
    for(i=0; i<100 ;i++){
        if(arrayNum[i]>check){
            check = arrayNum[i];
        }
    }

    // print result
    for(i=0; i<100 ;i++){
        if(arrayNum[i]>1 && arrayNum[i]==check){
            printf("%d ", i+1);
        }
    }

    return 0;
}