#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++)
static char buf[100000],*p1=buf,*p2=buf;
inline int read(void){
	reg char ch=getchar();
	reg int res=0;
	while(!isdigit(ch))ch=getchar();
	while(isdigit(ch))res=10*res+(ch^'0'),ch=getchar();
	return res;
}

const int MAXN=2e5+5;
const int MAXM=2e5+5;

struct Edge{
	int u,v,w;
	inline bool operator<(const Edge& a)const{
		return w>a.w;
	}
};

int n,m;
int fa[MAXN],d[MAXN];
Edge e[MAXM];

inline int find(reg int x){
	if(x==fa[x])
		return x;
	else
		return fa[x]=find(fa[x]);
}

int main(void){
	n=read(),m=read();
	for(reg int i=1;i<=n;++i)
		fa[i]=i,d[i]=1;
	for(reg int i=1;i<=m;++i)
		e[i].u=read(),e[i].v=read(),e[i].w=read();
	sort(e+1,e+m+1);
	reg int sum=0;
	for(reg int i=1;i<=m;++i){
		reg int x=find(e[i].u),y=find(e[i].v);
		if(x!=y&&(d[x]||d[y]))
			fa[x]=y,sum+=e[i].w,d[y]=d[x]&&d[y];
		else if(x==y&&d[x])
			d[x]=0,sum+=e[i].w;
	}
	printf("%d\n",sum);
	return 0;
}