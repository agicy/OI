#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;

const int MAXN=2e3+5;
const int MAXM=1e4+5;

struct Edge{
	int u,v,w;
	inline Edge(reg int u=0,reg int v=0,reg int w=0):u(u),v(v),w(w){
		return;
	}
	inline bool operator<(const Edge& a)const{
		return w<a.w;
	}
};

namespace UnionFind{
	int fa[MAXN];
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
		if(ra!=rb)
			fa[rb]=ra;
		return;
	}
	inline bool search(reg int a,reg int b){
		return find(a)==find(b);
	}
}

int n,m;
Edge E[MAXM];

int main(void){
	scanf("%d%d",&n,&m);
	UnionFind::Init(n);
	reg int tot=0;
	reg ll ans=0;
	for(reg int i=1;i<=m;++i){
		static int p,u,v,w;
		scanf("%d%d%d%d",&p,&u,&v,&w);
		if(p==1)
			ans+=w,UnionFind::merge(u,v);
		else
			E[++tot]=Edge(u,v,w);
	}
	sort(E+1,E+tot+1);
	for(reg int i=1;i<=tot;++i)
		if(!UnionFind::search(E[i].u,E[i].v)){
			ans+=E[i].w;
			UnionFind::merge(E[i].u,E[i].v);
		}
	printf("%lld\n",ans);
	return 0;
}