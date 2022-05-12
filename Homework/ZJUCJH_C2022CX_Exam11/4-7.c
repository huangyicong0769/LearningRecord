#include<stdio.h>

char *day_name(char *name[], int n);

int main(){
    static char *name[] = { "NOT DEFINE","Monday","Tuesday","Wednesday", "Thursday","Friday","Saturday","Sunday"};
    char *ps;
    for(register int i = 0; i < 8; i++){
        ps = day_name(name,i);
        printf("Day No:%2d-->%s\n",i,ps);
    }
    return 0; 
}

char *day_name(char **name, int n){
    char *pp1,*pp2;
    pp1 = *name;
    pp2 = *(name + n);
    return ((n < 1 || n > 7) ? pp1 : pp2);
}