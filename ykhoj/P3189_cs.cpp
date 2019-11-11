#include<cstdio>
#include<cstdlib>
#include<climits>
using namespace std;
int n,k,Min=INT_MAX;
char s[20001],st[20001],ans[20001];
int main()
{
    freopen("input.txt", "r", stdin);
	scanf("%d%d",&n,&k);
	scanf("%c",&s[1]);
	for (int i=1;i<=n;i++) scanf("%c",&s[i]);
	for (int t=0;t<10;t++)
	{
		int cnt=0,cost=0;
		for (int i=1;i<=n;i++) st[i]=s[i];
		for (int i=1;i<=n;i++) 
			if ((int)s[i]==t+48) cnt++;
		for (int i=1;t+i<10||t-i>=0;i++)
		{
			if (t+i<10)
				for (int j=1;j<=n;j++)
					if ((int)s[j]==t+i+48)
					{
						st[j]=(char)(t+48);
						cnt++;
						cost+=i;
						if (cnt==k) break;
					}
			if (cnt==k) break;
			if (t-i>=0)
				for (int j=1;j<=n;j++)
					if ((int)s[j]==t-i+48)
					{
						st[j]=(char)(t+48);
						cnt++;
						cost+=i;
						if (cnt==k) break;
					}
			if (cnt==k) break;
		}
		if (cost<Min)
		{
			Min=cost;
			for (int i=1;i<=n;i++) ans[i]=st[i];
		}
	}
	printf("%d\n",Min);
	for (int i=1;i<=n;i++) printf("%c",ans[i]);
	printf("\n"); 
}