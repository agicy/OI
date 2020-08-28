#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;

const int MAXN=1e5+5;
const int MAXM=5e5+5;
const int MAXQ=5e5+5;
const int MAXV=MAXN*2;

unsigned int SA,SB,SC; int n,m,q,LIM;
unsigned int rng61(){
	SA ^= SA << 16;
	SA ^= SA >> 5;
	SA ^= SA << 1;
	unsigned int t=SA;
	SA=SB;
	SB=SC;
	SC ^= t ^ SA;
	return SC;
}

int L[MAXQ];

struct Edge{
	int u,v,w;
	inline Edge(reg int u=0,reg int v=0,reg int w=0):u(u),v(v),w(w){
		return;
	}
	inline bool operator<(const Edge& a)const{
		return w<a.w;
	}
};

Edge E[MAXM];
vector<int> V;

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

ll ans[MAXQ];

const int inf=0x3f3f3f3f;

int main(void){
	scanf("%d%d%d%u%u%u%d",&n,&m,&q,&SA,&SB,&SC,&LIM);
	for(reg int i=1;i<=m;++i){
		static int u,v,w;
		u=rng61()%n+1,v=rng61()%n+1,w=rng61()%LIM;
		E[i]=Edge(u,v,w);
	}
	for(reg int i=1;i<=q;++i){
		L[i]=rng61()%LIM;
		V.push_back(L[i]);
	}
	V.push_back(inf);
	sort(V.begin(),V.end());
	V.erase(unique(V.begin(),V.end()),V.end());
	for(reg int i=1;i<=q;++i)
		L[i]=lower_bound(V.begin(),V.end(),L[i])-V.begin();
	sort(E+1,E+m+1);
	UnionFind::Init(n);
	reg int ptr=0;
	reg int siz=V.size();
	for(reg int i=1;i<=m;++i)
		if(!UnionFind::search(E[i].u,E[i].v)){
			while(ptr<siz&&V[ptr]<E[i].w)
				++ptr;
			reg int fu=UnionFind::find(E[i].u),fv=UnionFind::find(E[i].v);
			ans[ptr]+=1ll*UnionFind::siz[fu]*UnionFind::siz[fv];
			UnionFind::merge(fu,fv);
		}
	for(reg int i=1,size=V.size();i<size;++i)
		ans[i]+=ans[i-1];
	reg ll Ans=0;
	for(reg int i=1;i<=q;++i)
		Ans^=ans[L[i]];
	printf("%lld\n",Ans);
	return 0;
}