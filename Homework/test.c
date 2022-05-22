#include <stdio.h>

struct student{
    int num;
    char name[10];
    int computer, english, math;
};

int main() {}

void inputStu(struct student *stu, int n){
    for (register int i = 0; i < n; i++, stu++){
        printf("Input the info of No.%d:\n", i +1);
        printf("number:");
        scanf("%d", &stu->num);
        printf("name:");
        scanf("%s", stu->name);
        printf("math score:");
        scanf("%d", &stu->math);
        printf("english score:");
        scanf("%d", &stu->english);
        printf("computer score:");
        scanf("%d", &stu->computer);
    }
}

void outputStu(struct student *stu, int n, const int POS){ 
    if (POS == -1){
        printf("Not found!\n");
        return;
    }
    stu += POS;
    printf("After update:\n");
    printf("num\t math\t english\t computer\n");
    printf("%d\t %d\t %d\t %d\n", stu->num, stu->math, stu->english, stu->computer);
}

int update_score(struct student stus[], int n, int num, int course, int score){
    int i;
    for (i = 0; i < n; i++)
        if (stus[i].num == num) break;
    if (i < n){
        switch (course){
            case 1: stus[i].math = score; break;
            case 2: stus[i].english = score; break;
            case 3: stus[i].computer = score; break;
        }
        return i;
    }else return -1;
}