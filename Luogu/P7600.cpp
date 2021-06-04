#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;

inline unsigned max(reg unsigned a,reg unsigned b){
	return a>b?a:b;
}

inline ll max(reg ll a,reg ll b){
	return a>b?a:b;
}

inline unsigned min(reg unsigned a,reg unsigned b){
	return a<b?a:b;
}

struct Edge{
	int v,w;
	inline Edge(reg int v=0,reg int w=0):v(v),w(w){
		return;
	}
};

const int MAXN=1e5+5;

int n;
unsigned deg[MAXN];
vector<Edge> G[MAXN];

inline bool cmpV(reg int a,reg int b){
	return deg[a]<deg[b];
}

inline bool cmpE(const Edge& a,const Edge& b){
	return deg[a.v]>deg[b.v];
}

ll f[MAXN];
unsigned lim,vis[MAXN];
ll sum[MAXN];
priority_queue<int,vector<int>,greater<int> > Q[MAXN];
priority_queue<int,vector<int>,less<int> > tQ[MAXN];
ll dp[MAXN][2];

inline void dfs(reg int u,reg int father){
	vis[u]=lim;
	for(Edge e:G[u])
		if(e.v!=father)
			dfs(e.v,u);
	reg ll ans=0;
	reg unsigned top=0;
	static ll S[MAXN];
	for(Edge e:G[u])
		if(e.v!=father){
			ans+=dp[e.v][0];
			if(e.w>dp[e.v][0]-dp[e.v][1])
				S[++top]=e.w-(dp[e.v][0]-dp[e.v][1]);
		}
	sort(S+1,S+top+1),reverse(S+1,S+top+1);
	reg ll tmp=sum[u];
	dp[u][0]=sum[u],dp[u][1]=sum[u]-((Q[u].size()==lim)?Q[u].top():0);
	reg int tot=0;
	static int bac[MAXN];
	for(reg unsigned i=1;i<=min(top,lim);++i){
		tmp+=S[i];
		while(Q[u].size()>lim-i){
			bac[++tot]=Q[u].top(),tmp-=Q[u].top();
			Q[u].pop();
		}
		dp[u][0]=max(dp[u][0],tmp);
		if(i==lim)
			continue;
		dp[u][1]=max(dp[u][1],tmp-((Q[u].size()>=lim-i)?Q[u].top():0));
	}
	for(reg int i=1;i<=tot;++i)
		Q[u].push(bac[i]);
	dp[u][0]+=ans,dp[u][1]+=ans;
	if(father==-1)
		f[lim]+=dp[u][0];
	return;
}

inline void del(reg int u){
	for(Edge e:G[u])
		sum[e.v]+=e.w,Q[e.v].push(e.w);
	return;
}

vector<ll> minimum_closure_costs(int N,vector<int> U,vector<int> V,vector<int> W){
	n=N;
	reg ll S=0;
	for(reg int i=0;i<n-1;++i){
		reg int u=U[i],v=V[i],w=W[i];
		++deg[u],++deg[v];
		G[u].push_back(Edge(v,w)),G[v].push_back(Edge(u,w));
		S+=w;
	}
	for(reg int i=0;i<n-1;++i){
		reg int u=U[i],v=V[i],w=W[i];
		f[max(deg[u],deg[v])]+=w;
	}
	for(reg int i=1;i<n;++i)
		f[i]+=f[i-1];
	vector<int> Ver;
	Ver.reserve(n);
	for(int i=0;i<n;++i)
		Ver.push_back(i);
	sort(Ver.begin(),Ver.end(),cmpV);
	for(reg int i=0;i<n;++i)
		sort(G[i].begin(),G[i].end(),cmpE);
	reg int ptr=0;
	for(reg int i=1;i<n;++i){
		lim=i;
		while(ptr<n&&deg[Ver[ptr]]<=lim)
			del(Ver[ptr++]);
		for(reg int j=ptr;j<n;++j){
			reg int u=Ver[j];
			while(G[u].size()&&deg[G[u].back().v]<=lim)
				G[u].pop_back();
		}
		for(reg int j=ptr;j<n;++j){
			reg int u=Ver[j];
			while(Q[u].size()>lim){
				int x=Q[u].top();
				Q[u].pop();
				sum[u]-=x,tQ[u].push(x);
			}
			while(Q[u].size()<lim&&tQ[u].size()){
				int x=tQ[u].top();
				tQ[u].pop();
				sum[u]+=x,Q[u].push(x);
			}
			while(Q[u].size()&&tQ[u].size()&&Q[u].top()<tQ[u].top()){
				int x=Q[u].top(),y=tQ[u].top();
				Q[u].pop(),tQ[u].pop();
				sum[u]=sum[u]-x+y;
				Q[u].push(y),tQ[u].push(x);
			}
		}
		for(reg int j=ptr;j<n;++j){
			reg int u=Ver[j];
			if(vis[u]!=lim)
				dfs(u,-1);
		}
	}
	vector<ll> res;
	res.reserve(n);
	for(reg int i=0;i<n;++i)
		res.push_back(S-f[i]);
	return res;
}