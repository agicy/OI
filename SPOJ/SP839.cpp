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

const int MAXN=500+5;
const int MAXM=3e3+5;
const int MAXV=MAXN;
const int MAXE=1e5;
const int inf=0x3f3f3f3f;

int cnt,head[MAXV],to[MAXE],w[MAXE],Next[MAXE];

inline void Add_Edge(reg int u,reg int v,reg int len){
	Next[++cnt]=head[u];
	to[cnt]=v;
	w[cnt]=len;
	head[u]=cnt;
	return;
}

inline void Add_Tube(reg int u,reg int v,reg int len){
	Add_Edge(u,v,len);
	Add_Edge(v,u,0);
	return;
}

int dep[MAXV];
int Q[MAXV];

inline bool bfs(reg int s,reg int t){
	reg int head_=0,tail_=0;
	memset(dep,-1,sizeof(dep));
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
				w[i]-=f,w[i^1]+=f;
				if(flow==lim)
					break;
			}
		}
	}
	return flow;
}

inline void dinic(reg int s,reg int t){
	while(bfs(s,t)){
		memcpy(cur,head,sizeof(head));
		while(dfs(s,t,inf));
	}
	return;
}

bool vis[MAXV];
int ans[MAXN];

inline void find(reg int u,const int& val){
	vis[u]=true,ans[u]|=val;
	for(reg int i=head[u];i;i=Next[i])
		if(w[i]&&!vis[to[i]])
			find(to[i],val);
	return;
}

int n,m,k;
int u[MAXM],v[MAXM];
int x[MAXN],y[MAXN];

int main(void){
	reg int t=read();
	while(t--){
		n=read(),m=read();
		for(reg int i=1;i<=m;++i)
			u[i]=read(),v[i]=read();
		memset(ans,0,sizeof(ans));
		k=read();
		for(reg int i=1;i<=k;++i)
			x[i]=read(),y[i]=read();
		reg int s=0,t=n+1;
		for(reg int j=0;j<31;++j){
			cnt=1,memset(head,0,sizeof(head));
			for(reg int i=1;i<=m;++i)
				Add_Edge(u[i],v[i],1),Add_Edge(v[i],u[i],1);
			for(reg int i=1;i<=k;++i)
				if((y[i]&(1<<j)))
					Add_Tube(s,x[i],inf);
				else
					Add_Tube(x[i],t,inf);
			dinic(s,t);
			memset(vis,false,sizeof(vis));
			find(s,1<<j);
		}
		for(reg int i=1;i<=n;++i)
			printf("%d\n",ans[i]);
	}
	return 0;
}