#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;

const int MAXN=6e3+5;

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
	int fa[MAXN],siz[MAXN];
	inline void Init(reg int n){
		for(reg int i=1;i<=n;++i)
			fa[i]=i,siz[i]=1;
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
		if(ra!=rb){
			fa[rb]=ra;
			siz[ra]+=siz[rb];
		}
		return;
	}
	inline bool search(reg int a,reg int b){
		return find(a)==find(b);
	}
}

int n;
Edge E[MAXN];

int main(void){
	int T;
	scanf("%d",&T);
	while(T--){
		scanf("%d",&n);
		for(reg int i=1;i<n;++i){
			static int x,y,z;
			scanf("%d%d%d",&x,&y,&z);
			E[i]=Edge(x,y,z);
		}
		sort(E+1,E+n);
		using namespace UnionFind;
		Init(n);
		reg ll ans=0;
		for(reg int i=1;i<n;++i){
			if(!search(E[i].u,E[i].v)){
				ans+=1ll*(siz[find(E[i].u)]*siz[find(E[i].v)]-1)*(E[i].w+1);
				merge(E[i].u,E[i].v);
			}
		}
		printf("%lld\n",ans);
	}
	return 0;
}
