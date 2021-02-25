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

const int MAXN=1e5+5;
const int MAXM=1e5+5;
const int MAXS=2e5+5;

struct Edge{
	int u,v,w;
	inline Edge(reg int u=0,reg int v=0,reg int w=0):u(u),v(v),w(w){
		return;
	}
	inline bool operator<(const Edge& a)const{
		return w>a.w;
	}
};

namespace UnionFind{
	int fa[MAXN+MAXM];
	inline void Init(reg int n){
		for(reg int i=1;i<=n;++i)
			fa[i]=i;
		return;
	}
	inline int find(reg int x){
		if(x==fa[x])
			return x;
		else
			return fa[x]=find(fa[x]);
	}
	inline void merge(reg int a,reg int b){
		reg int ra=find(a),rb=find(b);
		fa[rb]=ra;
		return;
	}
	inline bool search(reg int a,reg int b){
		return find(a)==find(b);
	}
}

int n,m;
int a[MAXM],b[MAXN];
Edge E[MAXS];

int main(void){
	m=read(),n=read();
	for(reg int i=1;i<=m;++i)
		a[i]=read();
	for(reg int i=1;i<=n;++i)
		b[i]=read();
	reg int tot=0;
	reg ll ans=0;
	for(reg int i=1;i<=m;++i){
		reg int s=read();
		while(s--){
			reg int x=read();
			E[++tot]=Edge(i+n,x,a[i]+b[x]);
			ans+=a[i]+b[x];
		}
	}
	sort(E+1,E+tot+1);
	reg int cnt=n+m;
	UnionFind::Init(n+m);
	for(reg int i=1;i<=tot&&cnt>1;++i)
		if(!UnionFind::search(E[i].u,E[i].v)){
			--cnt;
			ans-=E[i].w;
			UnionFind::merge(E[i].u,E[i].v);
		}
	printf("%lld\n",ans);
	return 0;
}