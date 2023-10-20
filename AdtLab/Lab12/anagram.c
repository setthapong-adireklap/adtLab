#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TEXTSIZE 51

char *sortWord(char *text){
    char *result = (char*)malloc(sizeof(char)*strlen(text));
    strcpy(result,text);

    char check;
    for(int i = 1 ; i<strlen(text) ; i++){
        check = result[i];
        for(int j = i ; j>0 ; j--){
            if(check < result[j-1]){
                result[j] = result[j-1];
                result[j-1] = check;
            }
            else{
                break;
            }
        }
    }
    return result;
}

int checkAnagram(char *text1,char *text2){
    if(strlen(text1) == strlen(text2)){
        char *temp1 = sortWord(text1);
        char *temp2 = sortWord(text2);
        if(!strcmp(temp1,temp2)){
            free(temp1);
            free(temp2);
            return 1;
        }
    }
    return 0;
}

int main(){

    int m, n;
    scanf("%d %d", &m, &n);

    //part of m
    char **wordList = calloc(m,sizeof(char*));
    for(int i = 0; i < m; i++){
        wordList[i] = malloc(TEXTSIZE*sizeof(char));
        scanf("%50s", wordList[i]);
    }

    //part of n
    char *text = NULL;
    for(int i = 0; i < n; i++){
        text = malloc(TEXTSIZE*sizeof(char));
        scanf("%50s", text);
        for(int j = 0 ; j<m ; j++){
            if(checkAnagram(text,wordList[j])){
                printf("%s ",wordList[j]);
            }
        }
        printf("\n");
    }

    //free
    for(int i = 0; i < m; i++){
        free(wordList[i]);
    }
    free(wordList);
    free(text);

    return 0;
}