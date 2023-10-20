#include <stdio.h>
#include <stdlib.h>

typedef struct countGame{

    int limit;
    int number;
    struct countGame *next;

}player_t;

player_t *append(player_t *startNode ,int limitval ,int i ,int n){
    
    player_t *pnode = (player_t*)malloc(sizeof(player_t));
    player_t *last = startNode;

    pnode->limit = limitval;
    pnode->number = i+1;
    pnode->next = NULL;

    if(startNode == NULL){
        return pnode;
    }

    while (last->next != NULL){
        last = last->next;
    }
    last->next = pnode;

    if(i==n-1){
        pnode->next = startNode;
    }

    return startNode;
}

int main(){

    int n,k;
    scanf("%d %d", &n, &k);
    
    int temp;
    player_t *pGame = NULL;

    //prepare for cut if total = limit
    player_t *pCut = NULL;

    //get input circle linked list
    for(size_t i = 0 ; i<n ;i++){
        scanf("%d", &temp);
        pGame = append(pGame,temp,i,n);
    }
    player_t *pPrevious = pGame;

    int count = 1, out = 0;
    int drinkCondition = 0;
    while(out != n-1){

        temp=count;
        while(temp>0){
            if(temp%10==k){
                drinkCondition=1;
            }
            temp = temp/10;
        }

        if(count%k==0 || drinkCondition == 1){
            pGame->limit-=1;
        }

        if(pGame->limit == -1){
            pCut = pGame->next;
            free(pGame);
            pPrevious->next = pCut; 
            pGame = pCut;
            out++;
        }
        else{
            pPrevious = pGame;
            pGame = pGame->next;
        }
        drinkCondition=0;
        count++;
    }

    printf("%d\n",pGame->number);
    free(pGame);

    return 0;
}