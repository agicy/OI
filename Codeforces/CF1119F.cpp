#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++)
static char buf[1<<21],*p1=buf,*p2=buf;
#define flush() (fwrite(wbuf,1,wp1,stdout),wp1=0)
#define putchar(c) (wp1==wp2&&(flush(),0),wbuf[wp1++]=c)
static char wbuf[1<<21];int wp1;const int wp2=1<<21;
inline int read(void){
	reg char ch=getchar();
	reg int res=0;
	while(!isdigit(ch)) ch=getchar();
	while(isdigit(ch)) res=10*res+(ch^'0'),ch=getchar();
	return res;
}

inline void write(reg ll x){
	static char buf[32];
	reg int p=-1;
	if(!x) putchar('0');
	else while(x) buf[++p]=(x%10)^'0',x/=10;
	while(~p) putchar(buf[p--]);
	return;
}

inline unsigned max(reg unsigned a,reg unsigned b){
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

const int MAXN=2.5e5+5;

int n;
int u[MAXN],v[MAXN],w[MAXN];
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
	reg ll S1=0,S2=sum[u];
	dp[u][0]=sum[u],dp[u][1]=sum[u]-((Q[u].size()==lim)?Q[u].top():0);
	reg int tot=0;
	static int bac[MAXN];
	for(reg unsigned i=1;i<=min(top,lim);++i){
		S1+=S[i];
		while(Q[u].size()>lim-i){
			bac[++tot]=Q[u].top(),S2-=Q[u].top();
			Q[u].pop();
		}
		dp[u][0]=max(dp[u][0],S1+S2);
		if(i==lim)
			continue;
		dp[u][1]=max(dp[u][1],S1+S2-((Q[u].size()>=lim-i)?Q[u].top():0));
	}
	for(reg int i=1;i<=tot;++i)
		Q[u].push(bac[i]);
	dp[u][0]+=ans,dp[u][1]+=ans;
	if(!father)
		f[lim]+=dp[u][0];
	return;
}

inline void del(reg int u){
	for(Edge e:G[u])
		sum[e.v]+=e.w,Q[e.v].push(e.w);
	return;
}

int main(void){
	n=read();
	reg ll S=0;
	for(reg int i=1;i<n;++i){
		u[i]=read(),v[i]=read(),w[i]=read();
		++deg[u[i]],++deg[v[i]];
		G[u[i]].push_back(Edge(v[i],w[i])),G[v[i]].push_back(Edge(u[i],w[i]));
		S+=w[i];
	}
	for(reg int i=1;i<n;++i)
		f[max(deg[u[i]],deg[v[i]])]+=w[i];
	for(reg int i=1;i<n;++i)
		f[i]+=f[i-1];
	vector<int> Ver;
	Ver.reserve(n);
	for(int i=1;i<=n;++i)
		Ver.push_back(i);
	sort(Ver.begin(),Ver.end(),cmpV);
	for(reg int i=1;i<=n;++i)
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
				dfs(u,0);
		}
	}
	for(reg int i=0;i<n;++i)
		write(S-f[i]),putchar(i==n-1?'\n':' ');
	flush();
	return 0;
}