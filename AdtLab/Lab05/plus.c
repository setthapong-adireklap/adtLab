#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void reverse(char *pArr){

    char temp;
    int n = strlen(pArr);
    for(int i=0 ; i<(n/2) ;i++){
        temp = pArr[i];
        pArr[i] = pArr[n-1-i];
        pArr[n-1-i] = temp;
    }
    
}

void getInputs(char **pArr){

    int c;
    *pArr = (char*)malloc(sizeof(char));

    int i = 0;
    while((c = getchar()) != '\n'){
        *pArr = (char*)realloc(*pArr,strlen(*pArr)+1);
        (*pArr)[i] = (char)c;
        i++;
    }
    (*pArr)[i] = '\0';

    reverse(*pArr);

}

void plusTwoNum(char **pArr,char *x,char *y){ // assume x >= y

    if(strlen(x)<=strlen(y)){
        char *temp = NULL;
        temp = x;
        x = y;
        y = temp;
    }

    int max_size = strlen(x);
    *pArr = (char*)malloc(sizeof(char));

    int i = 0;
    int result;
    char carry = '0';
    for(i=0; i<max_size ;i++){
        
        *pArr = (char*)realloc(*pArr,strlen(*pArr)+1);
        
        if(strlen(y)-1<i){
            result = (x[i]+carry-2*'0')%10;
            if(x[i]+carry-2*'0' >= 10){
                carry = '1';
            }
            else{
                carry = '0';
            }
        }
        else{
            result = (x[i]+y[i]+carry-3*'0')%10;

            if(x[i]+y[i]+carry-3*'0' >= 10){
                carry = '1';
            }
            else{
                carry = '0';
            }
        }
        (*pArr)[i] = (char)(result+48);
    }

    if(carry=='1'){
        *pArr = (char*)realloc(*pArr,strlen(*pArr)+1);
        (*pArr)[i] = '1';
        i++;
    }
    (*pArr)[i] = '\0';

    reverse(*pArr);
    free(x);
    free(y);
}

int main(){
    
    char *x = NULL;
    char *y = NULL;
    char *result = NULL;

    //get 2 inputs
    getInputs(&x);
    getInputs(&y);

    //plus and print it out 
    plusTwoNum(&result, x, y);
    printf("%s", result);
    free(result);

    return 0;
}