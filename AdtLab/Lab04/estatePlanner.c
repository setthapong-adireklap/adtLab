#include <stdio.h>
#include <math.h>

int findTotalsquare(int m ,int n){
    
    //base case
    if(m == 0 || n == 0){
        return 0;
    }
    else if(m == 1 || n==1){
        return m*n;
    }
    
    //swap m n if m>n
    if(m>n){
        int temp = m;
        m = n;
        n = temp;
    }
    int k = log2(m);

    return findTotalsquare(m-pow(2,k),n) + findTotalsquare(n-pow(2,k),pow(2,k)) + 1;
}

int main(){
    
    int m, n;
    scanf("%d %d", &m, &n);
    printf("%d",findTotalsquare(m,n));

    //O(log(min(m,n)))
    
    return 0;
}