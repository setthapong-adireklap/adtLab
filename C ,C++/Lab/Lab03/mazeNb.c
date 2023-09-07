#include <stdio.h>
#include <stdlib.h>

void pattern1(int n, int **numArray);
void pattern2(int n, int **numArray);
void pattern3(int n, int **numArray);
void pattern4(int n, int **numArray);

int main(){
    
    int size, pattern;
    scanf("%d %d", &size, &pattern);


    //create array n*n with pointer
    int **pNumArray = NULL;
    int i, j;

    pNumArray = (int **)malloc(sizeof(int *) *size);
    for(i=0 ; i<size ;i++){
        pNumArray[i] = (int *)malloc(sizeof(int) *size);
        for(j=0 ; j<size ; j++){
            pNumArray[i][j] = 0;
        }
    }

    switch (pattern){
    case 1:
        pattern1(size, pNumArray);
        break;
    case 2:
        pattern2(size, pNumArray);
        break;
    case 3:
        pattern3(size, pNumArray);
        break;
    case 4:
        pattern4(size, pNumArray);
        break;
    }

    for(i=0; i<size ;i++){
        free(pNumArray[i]);
    }
    free(pNumArray);

    return 0;
}

void printArray(int **pNumArray, int n){
    int i,j;
    for(i=0 ; i<n ;i++){
        for(j=0 ; j<n ; j++){
            printf("%d ", pNumArray[i][j]);
        }
        printf("\n");
    }
}

void pattern1(int n, int **pNumArray){

    int temp=1;
    int i, j;
    for(i=0 ; i<n ;i++){
        for(j=0 ; j<n ;j++){
            pNumArray[j][i] = temp;
            temp++;
        }
   }
   printArray(pNumArray, n);

}

void pattern2(int n, int **pNumArray){

    int temp=1;
    int i, j;
    for(i=0 ; i<n ;i++){
        for(j=0 ; j<n ;j++){
            if(i%2==0){
                pNumArray[j][i] = temp;
            }
            else{
                pNumArray[n-j-1][i] = temp;
            }
            temp++;
        }
   }
   printArray(pNumArray, n);
}

void pattern3(int n, int **pNumArray){
    
    int temp=1;
    int row=n-1, col=0;

    int i, j;

    //สามเหลี่ยมล่าง
    for(i=0 ; i<n ;i++){
        for(j=0; j<1+i ;j++){
            
            pNumArray[row][col] = temp;

            if(i==n-1 && j==i){
                temp++;
                break;
            }
            if(j==i){
                if(col==0 || i==0){
                    row--;
                }
                else if(row==n-1){
                    col++;
                }
            }
            else{
                if(i%2==1){
                    row++;
                    col++;
                }
                else{
                    row--;
                    col--;
                }
            }
            temp++;
        }
    }

    temp=n*n;
    row=0;
    col=n-1;

    //สามเหลี่ยมบน

    for(i=0 ; i<n-1 ;i++){
        for(j=0; j<1+i ;j++){

            pNumArray[row][col] = temp;

            if(j==i){
                if(col==n-1 || i==0){
                    row++;
                }
                else if(row==0){
                    col--;
                }
            }
            else{
                if(i%2==1){
                    row--;
                    col--;
                }
                else{
                    row++;
                    col++;
                }
            }
            temp--;
        }
    }
   printArray(pNumArray, n);
}

void pattern4(int n, int **pNumArray){

    int temp=1, direction=1;
    int row=-1, col=0, check=0;

    int i, j;
    for(i=0 ; i<2*n-1 ;i++){
        
        if( i != 0 && i%2==1){
            check++;
        }

        for(j=0 ; j<(n-check) ;j++){
            switch (direction){
            case 1:
                row++;
                pNumArray[row][col] = temp;
                break;
            case 2:
                col++;
                pNumArray[row][col] = temp;
                break;
            case 3:
                row--;
                pNumArray[row][col] = temp;
                break;
            case 4:
                col--;
                pNumArray[row][col] = temp;
                break;
            }
            temp++;
        }
        direction++;
        if(direction==5){
            direction=1;
        }
   }
   printArray(pNumArray, n);
}