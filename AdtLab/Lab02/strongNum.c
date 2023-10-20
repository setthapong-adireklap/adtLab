#include <stdio.h>

int findStrong(int m);
int factorial(int num);

int main(){

    int n;
    scanf("%d", &n);
    
    int i, m;
    for(i=0 ; i<n ;i++){
        scanf("%d", &m);
        printf("%d\n",findStrong(m));
    }
    return 0;
}

int factorial(int num){
    int result=1;
    if(num==0 || num==1){
        return 1;
    }
    else{
        return num*factorial(num-1);
    }
}

int findStrong(int m){
    
    int i, result = 0;
    for(i=0 ; i<m ;i++){
        int temp = i;
        int total = 0;
        while(temp > 0){
            total+=factorial(temp%10);
            temp/=10;
        }
        if(total == i && total < m && total > result){
                result = total;
        }
        
    }

    return result;
}