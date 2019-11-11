#include<iostream>
#include<cstring>
using namespace std;
long n,Min,Mina,l,s,a[20001],d[20001];
int main(){
    freopen("input.txt", "r", stdin);
	cin>>n;
	Min=200000000;
	for(int i=1;i<=n;i++){
		char c;
		cin>>c;
		if(c=='B')d[i]=1;
		else d[i]=2;
	}
	for(int i=1;i<=n;i++){
		l=0;s=0;
	//	cout<<i<<endl;
		memset(a,0,sizeof(a));
		for(int j=1;j<=n-i+1;j++){
			l+=a[j];
			if((l%2==0&&d[j]==1)||(l%2!=0&&d[j]==2)){
				l++;a[j+i]=1;s++;
			}
	//		cout<<l<<' '<<d[j]<<endl;
		}
		bool p=0;
		for(int j=n-i+2;j<=n;j++){
//			cout<<d[j]<<endl;
			l+=a[j];
			if(((d[j]==1)&&(l%2==0))||((d[j]==2)&&(l%2!=0))){
				p=1;break;
			}
		}
//		cout<<s<<endl;
		if(Min>s&&p==0){
			Min=s;Mina=i;
		}
	}
	cout<<Mina<<' '<<Min<<endl;
}