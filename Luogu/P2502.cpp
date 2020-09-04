#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;

const int MAXN=500+5;
const int MAXM=5e3+5;

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

const int inf=0x3f3f3f3f;

int n,m,s,t;
Edge E[MAXM];

inline int gcd(reg int a,reg int b){
	return b?gcd(b,a%b):a;
}

int main(void){
	scanf("%d%d",&n,&m);
	for(reg int i=1;i<=m;++i){
		static int x,y,z;
		scanf("%d%d%d",&x,&y,&z);
		E[i]=Edge(x,y,z);
	}
	scanf("%d%d",&s,&t);
	sort(E+1,E+m+1);
	int ans1=inf,ans2=1;
	for(reg int i=1;i<=m;++i){
		UnionFind::Init(n);
		for(reg int j=i;j>=1;--j){
			if(!UnionFind::search(E[j].u,E[j].v)){
				UnionFind::merge(E[j].u,E[j].v);
				if(UnionFind::search(s,t)){
					int up=E[i].w,dn=E[j].w;
					if(1ll*ans1*dn>1ll*ans2*up)
						ans1=up,ans2=dn;
					break;
				}
			}
		}
	}
	if(ans1==inf)
		puts("IMPOSSIBLE");
	else{
		reg int d=gcd(ans1,ans2);
		ans1/=d,ans2/=d;
		if(ans2!=1)
			printf("%d/%d\n",ans1,ans2);
		else
			printf("%d\n",ans1);
	}
	return 0;
}