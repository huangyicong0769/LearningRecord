#include <iostream>
#include <cstdio>
#include <algorithm>
#define ll long long
using namespace std;
int lowbit(int x){	return x & (-x);}
int n,m;
ll tree[300001];
void add(int pos){	//单点修改（每次只用加1） 
	while(pos<=n)	
		tree[pos]++,pos+=lowbit(pos);
}
int Query(int num){
	ll sum=0;
	while(num>0)
		sum+=tree[num],num-=lowbit(num);
	return sum;
}
//以上为树状数组的单点修改区间查询 
struct Num{	
	ll num;	int pos;	//原数组 
}a[300001];
bool cmp(Num a1,Num a2){return a1.num<a2.num;}	//结构体排序 
struct Pair{
	int l,r;			//好对 
}pairr[600002];
int paircnt=0;		//记录好对个数 
void add_pair(Num a1,Num a2){
	int l=min(a1.pos,a2.pos) , r=max(a1.pos,a2.pos);
		//为了方便查询，统一把好对中出现位置较小的那个放在前面 
	pairr[++paircnt].l=l;
	pairr[paircnt].r=r;
	return ;
}
bool cmpPair(Pair a1,Pair a2){		//对所有的好对按右端点从小到大排序 
	if(a1.r!=a2.r)	return a1.r<a2.r;
	else return a1.l<a2.l;
}
struct Questions{
	int l,r,pos;		//询问 
}question[300001];
bool cmpQestions(Questions a1,Questions a2){	//对所有的询问按右端点从小到大排序 
	if(a1.r!=a2.r)	return a1.r<a2.r;
	else return a1.l<a2.l;
}
int main(){
	scanf("%d %d",&n,&m);
    	if(n==1){puts("0");return 0;}//新增的hack
	for(int i=1 ; i<=n ; i++){
		scanf("%lld",&a[i].num);
		a[i].pos=i;			//记录下该数在原先序列里的位置，排完序后方便添加配对 
	}
	sort(a+1,a+1+n,cmp);	//排序 
	add_pair(a[1],a[2]);	//首位特殊处理
	add_pair(a[n],a[n-1]);	//末尾特殊处理
	for(int i=2 ; i<n ; i++){
		int ldif = a[i].num-a[i-1].num , rdif = a[i+1].num-a[i].num;	//左边的差 和 右边的差 
		if(ldif<rdif)		add_pair(a[i],a[i-1]);		//左边差更小，只有左边的一对 
		else if(ldif==rdif)	add_pair(a[i],a[i-1]),add_pair(a[i],a[i+1]);
														//两边差更小，有两对 
		else				add_pair(a[i],a[i+1]);		//右边差更小，只有右边的一对 
	}
	sort(pairr+1 , pairr+1+paircnt , cmpPair);	//对所有的好对按右端点从小到大排序
	for(int i=1;i<=m;i++){
		scanf("%d %d", &question[i].l ,&question[i].r);
		question[i].pos=i;
	}
	sort(question+1 , question+1+m , cmpQestions);//对所有的询问按右端点从小到大排序
	ll ans=0;		//ans为最终答案
	for(int i=1,j=1 ; i<=m ; i++){	//i为当前询问，j为当前待入树状数组的好对 
		while(pairr[j].r<=question[i].r && j<=paircnt){
			add(pairr[j].l);		//如果当前好对的右端点在当前询问的右端点内，就加入树状数组 
			j++;
		}
		ans+=1ll * question[i].pos * (j-1- Query(question[i].l-1) );	//计算答案 
	}
	printf("%lld\n",ans);	//输出 
	return 0;
}