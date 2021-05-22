#include"roads.h"
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

const int MAXN=1e5+5;
const ll inf=0x3f3f3f3f3f3f3f3f;

struct Edge{
	int v,w;
	inline Edge(int v=0,int w=0):v(v),w(w){
		return;
	}
};

int n;
vector<Edge> G[MAXN];

inline void Add_Edge(int u,int v,int w){
	G[u].push_back(Edge(v,w));
}

inline bool cmp(ll a,ll b){
	return a>b;
}

ll f[MAXN][2];

inline void dfs(int u,int father,int lim){
	for(Edge e:G[u])
		if(e.v!=father)
			dfs(e.v,u,lim);
	int tot=0;
	static ll a[MAXN],b[MAXN];
	for(Edge e:G[u])
		if(e.v!=father){
			++tot;
			a[tot]=e.w+f[e.v][1];
			b[tot]=max(f[e.v][0],f[e.v][1]);
		}
	ll val=0;
	for(int i=1;i<=tot;++i)
		val+=b[i],a[i]-=b[i];
	sort(a+1,a+tot+1,cmp);
	if(tot>=lim){
		f[u][0]=val;
		for(int i=1;i<=lim;++i)
			f[u][0]+=a[i];
	}
	else
		f[u][0]=-inf;
	if(lim){
		f[u][1]=val;
		for(int i=1;i<lim&&i<=tot;++i){
			if(a[i]<=0)
				break;
			f[u][1]+=a[i];
		}
	}
	else
		f[u][1]=-inf;
	return;
}

std::vector<ll> minimum_closure_costs(int N,std::vector<int> U,std::vector<int> V,std::vector<int> W) {
	n=N;
	ll sum=0;
	for(int i=1;i<=n-1;++i){
		static int u,v,w;
		u=U[i-1]+1,v=V[i-1]+1,w=W[i-1];
		sum+=w;
		Add_Edge(u,v,w),Add_Edge(v,u,w);
	}
	vector<ll> res;
	res.push_back(sum);
	for(int lim=1;lim<=n-1;++lim){
		dfs(1,0,lim);
		res.push_back(sum-max(f[1][0],f[1][1]));
	}
	return res;
}