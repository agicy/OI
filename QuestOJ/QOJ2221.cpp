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

inline int min(reg int a,reg int b){
	return a<b?a:b;
}

const int MAXN=300+5;
const int MAXM=1e3+5;
const int MAXV=MAXN;
const int MAXE=MAXM*2;
const int inf=0x3f3f3f3f;

int n,m;
int cnt=1,head[MAXV],to[MAXE],w[MAXE],Next[MAXE];

inline void Add_Edge(reg int u,reg int v){
	Next[++cnt]=head[u];
	to[cnt]=v;
	head[u]=cnt;
	return;
}

int dep[MAXV];
int Q[MAXV];

inline bool bfs(reg int s,reg int t){
	memset(dep,-1,sizeof(dep));
	reg int head_=0,tail_=0;
	dep[s]=1,Q[tail_++]=s;
	while(head_<tail_){
		reg int u=Q[head_++];
		for(reg int i=head[u];i;i=Next[i]){
			reg int v=to[i];
			if(dep[v]==-1&&w[i]){
				dep[v]=dep[u]+1;
				Q[tail_++]=v;
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
				w[i]-=f;
				w[i^1]+=f;
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

bool vis[MAXN];
int fa[MAXN];
int W[MAXE];

inline void dfs(reg int u){
	vis[u]=true;
	for(reg int i=head[u];i;i=Next[i]){
		reg int v=to[i];
		if(w[i]&&!vis[v])
			dfs(v);
	}
	return;
}

int main(void){
	n=read(),m=read();
	for(reg int i=1;i<=m;++i){
		static int x,y;
		x=read(),y=read();
		Add_Edge(x,y);
		Add_Edge(y,x);
	}
	fill(W+1,W+cnt+1,1);
	for(reg int i=2;i<=n;++i)
		fa[i]=1;
	reg int ans=m;
	for(reg int i=2;i<=n;++i){
		fill(w+1,w+cnt+1,1);
		reg int s=fa[i],t=i;
		memset(vis,false,sizeof(vis));
		ans=min(ans,dinic(s,t));
		dfs(s);
		for(reg int j=i+1;j<=n;++j)
			if(!vis[j]&&fa[j]==s)
				fa[j]=i;
	}
	printf("%d\n",ans);
	return 0;
}