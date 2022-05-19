#include <iostream>
#include <cstdio>
using namespace std;

long long solve(const long long &a, const long long &b, const long long &c, long long S){
    long long ans = 0;
    if (c > a * b){
        ans += c * (S/b);
        S %= b;
    } else {
        ans += a * (S - 1);
        S = 1;
    }
    if (S)
        ans += a*(S - 1) + (c > a ? c : a);
    return ans;
}

int main(){
    long long T;
    scanf("%lld", &T);
    for (int i = 0; i < T; i++){
        long long a, b, c, S;
        scanf("%lld%lld%lld%lld", &a, &b, &c, &S);
        printf("%lld\n", solve(a, b, c, S));
    }
}