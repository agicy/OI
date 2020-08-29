#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;

const int MAXN=500+5;

struct Node{
	int x,y;
	inline void read(void){
		scanf("%d%d",&x,&y);
		return;
	}
};

struct Edge{
	int u,v;
	double w;
	inline Edge(reg int u=0,reg int v=0,reg double w=0):u(u),v(v),w(w){
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

inline double sqr(reg double x){
	return x*x;
}

inline double getDis(const Node& a,const Node& b){
	return sqrt(sqr(a.x-b.x)+sqr(a.y-b.y));
}

int n,k;
Node p[MAXN];
Edge E[MAXN*MAXN/2];
double ans[MAXN];

int main(void){
	scanf("%d%d",&n,&k);
	for(reg int i=1;i<=n;++i)
		p[i].read();
	reg int tot=0;
	for(reg int i=1;i<=n;++i)
		for(reg int j=i+1;j<=n;++j)
			E[++tot]=Edge(i,j,getDis(p[i],p[j]));
	sort(E+1,E+tot+1);
	reg int cnt=0;
	UnionFind::Init(n);
	for(reg int i=1;i<=tot&&cnt<n-1;++i)
		if(!UnionFind::search(E[i].u,E[i].v)){
			ans[++cnt]=E[i].w;
			UnionFind::merge(E[i].u,E[i].v);
		}
	printf("%.2lf\n",ans[cnt-k+1]);
	return 0;
}