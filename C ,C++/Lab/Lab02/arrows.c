#include <stdio.h>

void arrow(char direction,int size);

int main(){

    char direction;
    int size;
    scanf("%c %d", &direction, &size);
    arrow(direction,size);

    return 0;
}

void arrow(char direction,int size){
    
    int i, j ,k;
    switch (direction)
    {
    case 'N':
        //Head
        for(i=0 ; i<size+1 ; i++){
            for(j=0 ; j<size-i ; j++){
                printf(" ");
            }
            for(k=0; k<2*i+1 ;k++){
                printf("#");
            }
            printf("\n");
        }
        //tail
        for(i=0 ; i<=size ; i++){
            printf(" ");
            for(k=0 ; k<2*size-1 ; k++){
                printf("#");
            }
            printf("\n");
        }
        break;
    case 'S':
        //tail
        for(i=0 ; i<=size ; i++){
            printf(" ");
            for(k=0 ; k<2*size-1 ; k++){
                printf("#");
            }
            printf("\n");
        }
        //Head
        for(i=0 ; i<size+1 ; i++){
            if(i!=0){
                for(j=0 ; j<i ; j++){
                    printf(" ");
                }
            }
            for(k=2*(size-i); k>=0 ;k--){
                printf("#");
            }
            printf("\n");
        }
        break;
    case 'E':
        //Half top
        for(i=0 ; i<size+1 ; i++){
            if(i==0){
                for(j=0; j<size+1 ;j++){
                    printf(" ");
                }
                printf("#\n");
            }
            else{
                for(k=0; k<2+size+i ;k++){
                    printf("#");
                }
                printf("\n");
            }
        }
        //Half below
        for(i=size ; i>0 ; i--){
            if(i==1){
                for(j=0; j<size+1 ;j++){
                    printf(" ");
                }
                printf("#\n");
            }
            else{
                for(k=0; k<1+size+i ;k++){
                    printf("#");
                }
                printf("\n");
            }
        }
        break;
    case 'W':
        //Half top
        for(i=0 ; i<size+1 ; i++){
            if(i==0){
                for(j=0; j<size ;j++){
                    printf(" ");
                }
                printf("#\n");
            }
            else{
                for(j=0 ; j<size-i ;j++){
                    printf(" ");
                }
                for(k=0 ; k<2+size+i ;k++){
                    printf("#");
                }
                printf("\n");
            }
        }
        //Half below
        for(i=size ; i>0 ; i--){
            if(i==1){
                for(j=0; j<size ;j++){
                    printf(" ");
                }
                printf("#\n");
            }
            else{
                for(j=0 ; j<size-i+1 ;j++){
                    printf(" ");
                }
                for(k=0; k<1+size+i ;k++){
                    printf("#");
                }
                printf("\n");
            }
        }
        break;
    default:
        break;
    }
}