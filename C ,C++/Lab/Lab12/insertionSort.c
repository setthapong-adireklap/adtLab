#include <stdio.h>
#include <stdlib.h>

void display(int *arrInt, int size){
    for(int i = 0 ; i<size ; i++){
        printf("%d ", arrInt[i]);
    }
    printf("\n");
}

void insertionSort(int *arrInt, int size){
    int check;
    for(int i = 1 ; i<size ; i++){
        check = arrInt[i];
        for(int j = i ; j>0 ; j--){
            if(check < arrInt[j-1]){
                arrInt[j] = arrInt[j-1];
                arrInt[j-1] = check;
            }
            else{
                break;
            }
        }
        display(arrInt,size);
    }
}

int main(){
    int size, temp;
    scanf("%d", &size);
    
    int *arrInt = calloc(size,sizeof(int));
    for(int i = 0 ; i<size ; i++){
        scanf("%d", &temp);
        arrInt[i] = temp;
    }
    insertionSort(arrInt, size);
    free(arrInt);

    return 0;
}