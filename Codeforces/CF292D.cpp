#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++)
static char buf[100000],*p1=buf,*p2=buf;
inline short read(void){
	reg char ch=getchar();
	reg short res=0;
	while(!isdigit(ch))ch=getchar();
	while(isdigit(ch))res=10*res+(ch^'0'),ch=getchar();
	return res;
}

const int MAXN=500+5;
const int MAXM=1e4+5;

short n,m;
short u[MAXM],v[MAXM];

struct UnionFind{
	short cnt,fa[MAXN];
	inline void Init(reg short n){
		cnt=n;
		for(reg short i=1;i<=n;++i)
			fa[i]=i;
		return;
	}
	inline short find(reg short x){
		if(x==fa[x])
			return x;
		else
			return fa[x]=find(fa[x]);
	}
	inline void merge(reg short a,reg short b){
		reg short ra=find(a),rb=find(b);
		if(ra!=rb)
			--cnt,fa[rb]=ra;
		return;
	}
};

UnionFind pre[MAXM],suf[MAXM];
UnionFind U;

int main(void){
	n=read(),m=read();
	for(reg short i=1;i<=m;++i)
		u[i]=read(),v[i]=read();
	pre[0].Init(n),suf[m+1].Init(n);
	for(reg short i=1;i<=m;++i){
		pre[i]=pre[i-1];
		pre[i].merge(u[i],v[i]);
	}
	for(reg short i=m;i>=1;--i){
		suf[i]=suf[i+1];
		suf[i].merge(u[i],v[i]);
	}
	reg short k=read(),l,r;
	while(k--){
		l=read(),r=read();
		U=pre[l-1];
		for(reg short i=1;i<=n;++i)
			U.merge(i,suf[r+1].find(i));
		printf("%hd\n",U.cnt);
	}
	return 0;
}