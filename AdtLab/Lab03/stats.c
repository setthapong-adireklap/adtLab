#include <stdio.h>
#include <stdlib.h>

void findStats(int *nums, int *maxi, int *mini, double *avg, int n){

    int i;
    int max=-100, min=100; 
    double total=0;

    for(i=0; i<n ;i++){
        
        total+=*(nums+i);

        if(*(nums+i)>=max){
            max = *(nums+i);
        }
        if(*(nums+i)<=min){
            min = *(nums+i);
        }
    }

    *maxi = max;
    *mini = min;
    *avg = total/n;

}

int main(){
    int n, i, maxi, mini;
    double avg;
    int *nums;
    scanf("%d", &n);
    nums = (int *)malloc(sizeof (int) *n);
    for (i=0; i<n; i++)
        scanf("%d", nums+i);
    findStats(nums, &maxi, &mini, &avg, n);
    printf("%.2f %d %d", avg, maxi, mini);
    return 0;
}