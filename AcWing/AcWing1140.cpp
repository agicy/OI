#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;

const int MAXN=100+5;

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

int n;
Edge E[MAXN*MAXN];

int main(void){
	scanf("%d",&n);
	reg int tot=0;
	for(reg int i=1;i<=n;++i)
		for(reg int j=1;j<=n;++j){
			static int x;
			scanf("%d",&x);
			if(i<j)
				E[++tot]=Edge(i,j,x);
		}
	sort(E+1,E+tot+1);
	reg int cnt=n,sum=0;
	UnionFind::Init(n);
	for(reg int i=1;i<=tot&&cnt>1;++i)
		if(!UnionFind::search(E[i].u,E[i].v)){
			--cnt;
			sum+=E[i].w;
			UnionFind::merge(E[i].u,E[i].v);
		}
	printf("%d\n",sum);
	return 0;
}