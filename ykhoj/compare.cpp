#include <cstdio>
#include <cstdlib>

int main(){
    for (int t=0; t<1000; t++){
        system("c:\\Users\\»ÆÜ²´Ï\\OneDrive\\WorkSpace\\ykhoj\\rand");
        system("c:\\Users\\»ÆÜ²´Ï\\OneDrive\\WorkSpace\\ykhoj\\P3662");
        system("c:\\Users\\»ÆÜ²´Ï\\OneDrive\\WorkSpace\\ykhoj\\P3662_ans");
        if (system("fc c:\\Users\\»ÆÜ²´Ï\\OneDrive\\WorkSpace\\ykhoj\\output.txt c:\\Users\\»ÆÜ²´Ï\\OneDrive\\WorkSpace\\ykhoj\\ans.txt")){
            puts("Wrong Answer");
            return 0;
        }else puts("Accepted");
    }
}