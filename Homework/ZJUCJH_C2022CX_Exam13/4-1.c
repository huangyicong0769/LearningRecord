#include <stdio.h>
#include <string.h>

struct Person{
    char str[23];
    int birth;
};

typedef struct Person Person;

int birthday(char s[]){
    int ret = 0;
    for (register int i = 13, p10 = 1; i >= 6; i--, p10 *= 10)
        ret += (s[i] - '0')*p10;
    return ret;
}

void sort(Person* head, Person* endl){
    for (Person* i = head; i < endl; i++)
        for (Person* j = i + 1; j < endl; j++)
            if (i->birth > j->birth){
                Person tmp = *i;
                *i = *j;
                *j = tmp;
            }
}

int main(){
    int n;
    scanf("%d", &n);
    Person a[n];
    for (register int i = 0; i < n; i++){
        scanf("%s", a[i].str);
        a[i].birth = birthday(a[i].str);
    }
    sort(a, a + n);
    for (register int i = 0; i < n; i++)
        printf("%s\n", a[i].str);
}