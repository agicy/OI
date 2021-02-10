#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++)
static char buf[100000],*p1=buf,*p2=buf;
inline int read(void){
	reg char ch=getchar();
	reg int res=0;
	while(!isdigit(ch))ch=getchar();
	while(isdigit(ch))res=10*res+(ch^'0'),ch=getchar();
	return res;
}

inline int max(reg int a,reg int b){
	return a>b?a:b;
}

inline int min(reg int a,reg int b){
	return a<b?a:b;
}

const int MAXN=1e4+5;
const int MAXM=1.5e5+5;
const int MAXV=MAXN;
const int MAXE=(MAXN+MAXM)*2;

int cnt=1,head[MAXV],to[MAXE],w[MAXE],Next[MAXE];

inline void Add_Edge(reg int u,reg int v,reg int len){
	Next[++cnt]=head[u];
	to[cnt]=v,w[cnt]=len;
	head[u]=cnt;
	return;
}

inline void Add_Tube(reg int u,reg int v,reg int len){
	Add_Edge(u,v,len);
	Add_Edge(v,u,0);
	return;
}

namespace Network{
	const int inf=0x3f3f3f3f;
	int dep[MAXV];
	int Q[MAXV];
	inline bool bfs(reg int s,reg int t){
		reg int _head=0,_tail=0;
		memset(dep,-1,sizeof(dep));
		dep[s]=1,Q[_tail++]=s;
		while(_head<_tail){
			reg int u=Q[_head++];
			for(reg int i=head[u];i;i=Next[i]){
				reg int v=to[i];
				if(dep[v]==-1&&w[i]){
					dep[v]=dep[u]+1;
					Q[_tail++]=v;
				}
			}
		}
		return dep[t]!=-1;
	}
	int cur[MAXV];
	inline int dfs(reg int u,reg int t,reg int lim){
		if(u==t)
			return lim;
		reg int flow=0;
		for(reg int &i=cur[u];i;i=Next[i]){
			reg int v=to[i];
			if(dep[v]==dep[u]+1&&w[i]){
				reg int f=dfs(v,t,min(lim-flow,w[i]));
				if(f){
					flow+=f;
					w[i]-=f,w[i^1]+=f;
					if(flow==lim)
						break;
				}
			}
		}
		return flow;
	}
	inline int dinic(reg int s,reg int t){
		reg int res=0;
		while(bfs(s,t)){
			memcpy(cur,head,sizeof(head));
			res+=dfs(s,t,inf);
		}
		return res;
	}
}

namespace Graph{
	bool vis[MAXV];
	int tim,dfn[MAXV],low[MAXV];
	int top,S[MAXV];
	int scc_cnt,col[MAXV];
	inline void tarjan(reg int u){
		vis[u]=true;
		dfn[u]=low[u]=++tim;
		S[++top]=u;
		for(reg int i=head[u];i;i=Next[i])
			if(w[i]){
				reg int v=to[i];
				if(!dfn[v]){
					tarjan(v);
					low[u]=min(low[u],low[v]);
				}
				else if(vis[v])
					low[u]=min(low[u],dfn[v]);
			}
		if(dfn[u]==low[u]){
			++scc_cnt;
			reg int v;
			do{
				v=S[top--];
				vis[v]=false;
				col[v]=scc_cnt;
			}while(u!=v);
		}
		return;
	}
}

int n,m;
vector<int> G[MAXN];
int c[MAXN];
vector<pair<int,int>/**/> ans;

inline void dfs(reg int u,reg int color){
	c[u]=color;
	for(vector<int>::iterator it=G[u].begin();it!=G[u].end();++it){
		reg int v=*it;
		if(c[v]==-1)
			dfs(v,color^1);
	}
	return;
}

int main(void){
	n=read(),m=read();
	for(reg int i=1;i<=m;++i){
		static int u,v;
		u=read(),v=read();
		G[u].push_back(v);
		G[v].push_back(u);
	}
	memset(c,-1,sizeof(c));
	for(reg int i=1;i<=n;++i)
		if(c[i]==-1)
			dfs(i,0);
	reg int s=0,t=n+1;
	for(reg int i=1;i<=n;++i)
		if(!c[i]){
			Add_Tube(s,i,1);
			for(vector<int>::iterator it=G[i].begin();it!=G[i].end();++it)
				Add_Tube(i,*it,1);
		}
		else
			Add_Tube(i,t,1);
	Network::dinic(s,t);
	for(reg int i=s;i<=t;++i)
		if(!Graph::dfn[i])
			Graph::tarjan(i);
	for(reg int u=1;u<=n;++u)
		if(!c[u])
			for(reg int i=head[u];i;i=Next[i])
				if(!w[i]){
					reg int v=to[i];
					if(1<=v&&v<=n&&Graph::col[u]!=Graph::col[v])
						ans.push_back(make_pair(min(u,v),max(u,v)));
				}
	sort(ans.begin(),ans.end());
	printf("%lu\n",ans.size());
	for(vector<pair<int,int>/**/>::iterator it=ans.begin();it!=ans.end();++it)
		printf("%d %d\n",it->first,it->second);
	return 0;
}