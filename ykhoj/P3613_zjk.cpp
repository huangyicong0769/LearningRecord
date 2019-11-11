#include<iostream>
#include<queue>
#include<vector>
#include<cstdio>
using namespace std;
priority_queue<int,vector<int>,greater<int> > s1,s2;
long T,n,ans=0;
long yz (long k){
	s1=s2;
	long sum=0;long l=0;
	long l1=(n-1)%(k-1)+1;
	while(!s1.empty()){
		if(l!=0)s1.push(l);l=0;
		if(l1!=0){
			for(int i=1;i<=l1;i++){
			l+=s1.top();
			s1.pop();
			if(s1.empty())break;
			}
			l1=0;
		}
		else {
			for(int i=1;i<=k;i++){
				l+=s1.top();
				s1.pop();
				if(s1.empty())break;
			}
		}
		sum+=l;
	}
	if(sum<=T)return 1;
	else return 0;
}
int main(){
    //freopen("input.txt", "r", stdin);
	scanf("%d%d",&n,&T);
	long x;
	for(int i=1;i<=n;i++){
		scanf("%d",&x);
		s2.push(x);
	}
	long  le = 2, ri = n;
	while(le<=ri){
		long mid=(le+ri)/2;
		if(yz(mid)==1) 
		{
			ri = mid-1;
			ans=mid;
		}
		else le = mid+1;
	}
	printf("%d\n",ans);
}