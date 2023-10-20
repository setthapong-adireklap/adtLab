#include <stdio.h>

typedef struct datetime{
    int date; // 1-31
    int month; // 1-12
    int year; // 1970++
    int dayOfWeek; // 0-6
    int hour; // 0-23
    int minute; // 0-59
    int second; // 0-59
} datetime_t;

int isLeapyear(int year){
    int result = 0;

    if(year%4==0 && year%100!=0 || year%400==0){
        result = 1;
    }

    return result;
}

datetime_t createDate(int timestamp) {

    int dayTotal = 1 + (timestamp/86400);
    int day[12] = {31,28,31,30,31,30,31,31,30,31,30,31};
    int currentYear = 1970;
    int currentMonth = 1;
    int totalDayInYear = 365;

    datetime_t a;
    a.second = ((timestamp%86400)%3600)%60;
    a.minute = ((timestamp%86400)%3600)/60;
    a.hour = (timestamp%86400)/3600;
    a.dayOfWeek = (3+dayTotal)%7;

    //how many year that pass
    while(dayTotal>=totalDayInYear){

        if(isLeapyear(currentYear)){
            totalDayInYear = 366;
        }
        else{
            totalDayInYear = 365;
        }

        dayTotal -= totalDayInYear;
        currentYear++;
    }

    if(isLeapyear(currentYear)){
            day[1] = 29;
        }
        else{
            day[1] = 28;
        }
    
    //how many month that pass
    int i=0;
    while (dayTotal>=day[i]){
        dayTotal -= day[i];
        i++;
        if(i==12){
            i=0; 
        }
        currentMonth++;
    }
    
    a.year = currentYear;
    a.month = currentMonth;
    a.date = dayTotal;


    return a;
}
void printDate(datetime_t inputDate) {
    
    char *dayOfWeek;
    char *month;

    switch (inputDate.dayOfWeek)
    {   
        case 0:
            dayOfWeek = "Sun";
            break;
        case 1:
            dayOfWeek = "Mon";
            break;
        case 2:
            dayOfWeek = "Tue";
            break;
        case 3:
            dayOfWeek = "Wed";
            break;
        case 4:
            dayOfWeek = "Thu";
            break;
        case 5:
            dayOfWeek = "Fri";
            break;
        case 6:
            dayOfWeek = "Sat";
            break;
    }

    switch (inputDate.month)
    {   
        case 1:
            month = "JAN";
            break;
        case 2:
            month = "FEB";
            break;
        case 3:
            month = "MAR";
            break;
        case 4:
            month = "APR";
            break;
        case 5:
            month = "MAY";
            break;
        case 6:
            month = "JUN";
            break;
        case 7:
            month = "JUL";
            break;
        case 8:
            month = "AUG";
            break;
        case 9:
            month = "SEP";
            break;
        case 10:
            month = "OCT";
            break;
        case 11:
            month = "NOV";
            break;
        case 12:
            month = "DEC";
            break;
    }

    printf("%s %d %s %d %02d:%02d:%02d",dayOfWeek,inputDate.date,month,inputDate.year,inputDate.hour,inputDate.minute,inputDate.second);
}

int main(){
    
    datetime_t inputDate;
    int timestamp;

    scanf("%d", &timestamp);
    inputDate = createDate(timestamp);
    printDate(inputDate);

    return 0;
}