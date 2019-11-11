#include<iostream>
#include<cstdio>
#include<cstring>
#include<cmath>
#include<algorithm>
#include<queue>
#include<vector>
using namespace std;
priority_queue<int > q1;
struct Node{
	long va,ti;
}p[20000];
long n;
long q[20000],h[20000];
int main(){
    freopen("input.txt", "r", stdin);
    //freopen("ans.txt", "w", stdout);
	scanf("%ld",&n);
	long t1;
	for(int i=1;i<=n;i++){
		scanf("%ld%ld",&p[i].va,&p[i].ti);
		if(q[p[i].ti]!=0)	h[i]=q[p[i].ti];
		q[p[i].ti]=i;
		t1=max(t1,p[i].ti);
	}
	long sum=0;
	while(t1>0){
		if(q[t1]!=0){
			q1.push(p[q[t1]].va);
			long t=q[t1];
			while(h[t]!=0){
				t=h[t]; 
				q1.push(p[t].va);
			} 
		}
		if(!q1.empty()){
			sum=sum+q1.top() ;
			q1.pop() ;
		}
		t1--;
	}
	printf("%ld\n",sum);
}