#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;

const int MAXN=200+5;
const int MAXK=200+5;

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

int n,k;
Edge E[MAXK];

int main(void){
	scanf("%d%d",&n,&k);
	reg ll ans=0;
	for(reg int i=1;i<=k;++i){
		static int u,v,w;
		scanf("%d%d%d",&u,&v,&w);
		E[i]=Edge(u,v,w);
		ans+=w;
	}
	sort(E+1,E+k+1);
	UnionFind::Init(n);
	reg int cnt=n;
	for(reg int i=1;i<=k&&cnt>1;++i)
		if(!UnionFind::search(E[i].u,E[i].v)){
			--cnt;
			ans-=E[i].w;
			UnionFind::merge(E[i].u,E[i].v);
		}
	printf("%lld\n",ans);
	return 0;
}