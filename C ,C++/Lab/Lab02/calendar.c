#include <stdio.h>

void calendar(int year, int month);
int isLeapyear(int year);

int main(){

    int year, nMonth;

    printf("Enter year: ");
    scanf("%d", &year);
    printf("Enter month: ");
    scanf("%d", &nMonth); 
    printf("====================\n");
    
    char *month[] = {"January","February","March","April","May","June","July","August","September","October","November","December"};
    printf("%s %d\n",month[nMonth-1],year);
    printf("Sun Mon Tue Wed Thu Fri Sat\n"); 
    
    calendar(year, nMonth);

    return 0;
}

int isLeapyear(int year){
    int result = 0;

    if(year%4==0 && year%100!=0 || year%400==0){
        result = 1;
    }

    return result;
}

void calendar(int year, int month){
    int totalDay = 0 , currentYear = 1990, n=(year-1990)*12 + month;
    int day[12] = {31,28,31,30,31,30,31,31,30,31,30,31};

    int i;
    for(i=0; i<n-1 ;i++){
        if(i!=0 && i%12==0){
            currentYear++;
        }

        if(isLeapyear(currentYear)){
            day[1] = 29;
        }
        else{
            day[1] = 28;
        }

        totalDay += day[i%12];
    }

    int start = (1+totalDay)%7;

    //print day
    int displayDay = 1;
    for(i=0; i<day[month-1]+start ;i++){
        if(i<start){
            printf("%4c", ' ');
        }
        else if(i%7==6 || displayDay==day[month-1]){
            printf("%3d\n",displayDay);
            displayDay++;
        }
        else if(i%7!=6){
            printf("%3d ",displayDay);
            displayDay++;
        }
    }
}