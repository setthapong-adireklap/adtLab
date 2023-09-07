#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

bool traverseMaze(char **pMaze, int rowS, int colS, int n, bool up, bool down, bool left, bool right);

int main(){

    int n,i,j;
    scanf("%d\n", &n);
    
    char **pMaze = NULL;
    pMaze = (char**)malloc(sizeof(char*)*n);

    //input
    int rowS=0, colS=0;
    for(i=0 ; i<n ;i++){
        pMaze[i] = (char*)malloc(sizeof(char)*n);
        for(j=0 ; j<n ;j++){
            scanf("%c", &*(*(pMaze+i)+j));
            if(*(*(pMaze+i)+j)=='S'){
                rowS=i;
                colS=j;
            }
        }
        while(getchar() != '\n'){}
    }
    traverseMaze(pMaze, rowS, colS, n, true, true, true ,true);

    for(i=0; i<n ;i++){
        for(j=0 ; j<n ;j++){
            printf("%c",pMaze[i][j]);
        }
        printf("\n");
    }

    return 0;
}

bool traverseMaze(char **pMaze, int rowS, int colS, int n, bool up, bool down, bool left, bool right){

    if(rowS+1<n){
        if(pMaze[rowS+1][colS] == 'G'){
            pMaze[rowS][colS] = '.';
            return true;
        }
    }
    if(colS-1>=0){
        if(pMaze[rowS][colS-1] == 'G'){
            pMaze[rowS][colS] = '.';
            return true;
        }
    }
    if(colS+1<n){
        if(pMaze[rowS][colS+1] == 'G'){
            pMaze[rowS][colS] = '.';
            return true;
        }
    }
    if(rowS-1>=0){
        if(pMaze[rowS-1][colS] == 'G'){
            pMaze[rowS][colS] = '.';
            return true;
        }
    }

    //go right
    if(colS+1<n && pMaze[rowS][colS+1] != '#' && right){
        
        if(traverseMaze(pMaze, rowS, colS+1, n, true, true, false ,true)){
            if(pMaze[rowS][colS] != 'S'){
                pMaze[rowS][colS] = '.';
            }
            return true;
        }
    }
    //go left
    if(colS-1>=0 && pMaze[rowS][colS-1] != '#' && left){
        if(traverseMaze(pMaze, rowS, colS-1, n, true, true, true ,false)){
            if(pMaze[rowS][colS] != 'S'){
                pMaze[rowS][colS] = '.';
            }
            return true;
        }
    }
    //go up
    if(rowS-1>=0 && pMaze[rowS-1][colS] != '#' && up){
        if(traverseMaze(pMaze, rowS-1, colS, n, true, false, true ,true)){
            if(pMaze[rowS][colS] != 'S'){
                pMaze[rowS][colS] = '.';
            }
            return true;
        }
    }
    //go down
    if(rowS+1<n && pMaze[rowS+1][colS] != '#' && down){
        if(traverseMaze(pMaze, rowS+1, colS, n, false, true, true ,true)){
            if(pMaze[rowS][colS] != 'S'){
                pMaze[rowS][colS] = '.';
            }
            return true;
        }
    }

    return false;
}