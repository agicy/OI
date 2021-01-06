#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++)
static char buf[100000],*p1=buf,*p2=buf;
inline int read(void){
	reg bool f=false;
	reg char ch=getchar();
	reg int res=0;
	while(!isdigit(ch))f|=(ch=='-'),ch=getchar();
	while(isdigit(ch))res=10*res+(ch^'0'),ch=getchar();
	return f?-res:res;
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

inline int dinic(reg int s,reg int t){
	reg int res=0;
	while(bfs(s,t)){
		memcpy(cur,head,sizeof(head));
		res+=dfs(s,t,inf);
	}
	return res;
}

bool vis[MAXV];
int ans[MAXV];

inline void find(reg int u,const int& val){
	vis[u]=true,ans[u]|=val;
	for(reg int i=head[u];i;i=Next[i])
		if(w[i]&&!vis[to[i]])
			find(to[i],val);
	return;
}

int n,m;
int val[MAXN];
int u[MAXM],v[MAXM];

int main(void){
	n=read(),m=read();
	for(reg int i=1;i<=n;++i)
		val[i]=read();
	for(reg int i=1;i<=m;++i)
		u[i]=read(),v[i]=read();
	reg int s=0,t=n+1;
	reg ll ans1=0,ans2=0;
	for(reg int j=0;j<31;++j){
		cnt=1,memset(head,0,sizeof(head));
		for(reg int i=1;i<=m;++i)
			Add_Tube(u[i],v[i],1),Add_Tube(v[i],u[i],1);
		for(reg int i=1;i<=n;++i)
			if(val[i]>=0){
				if((val[i]&(1<<j)))
					Add_Tube(s,i,inf);
				else
					Add_Tube(i,t,inf);
			}
		ans1+=(1ll<<j)*dinic(s,t);
		memset(vis,false,sizeof(vis));
		find(s,1<<j);
	}
	for(reg int i=1;i<=n;++i)
		if(val[i]>=0)
			ans2+=val[i];
		else
			ans2+=ans[i];
	printf("%lld\n%lld\n",ans1,ans2);
	return 0;
}