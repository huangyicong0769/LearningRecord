#include <cstdio>
#include <cstring>
inline int read()
{
	int s = 0; char c; while((c=getchar())<'0'||c>'9');
	do{s=s*10+c-'0';}while((c=getchar())>='0'&&c<='9');
	return s;
}
int n,l,r,ql,qr;
long long ans;
int main()
{
    #ifdef DEBUG
    freopen("input.txt", "r", stdin);
    #endif // DEBUG
	for(n=read(),l=r=read();n--;)
	{
		ql = read(), qr = read();
		if(ql<=l&&r<=qr) continue;
		if(qr<l) ans += l-qr, r = l, l = qr;
		else if(r<ql) ans += ql-r, l = r, r = ql;
		else l = ql>l?ql:l, r = qr<r?qr:r;
        #ifdef DEBUG
        printf("%d %d %lld\n", l, r, ans);
        #endif // DEBUG
	}
	printf("%I64d\n",ans);
	return 0;
}