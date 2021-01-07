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

const int MAXN=1e3+5;
const int MAXM=2e4+5;
const int MAXV=MAXN;
const int MAXE=2*(MAXN+MAXM);
const int inf=0x3f3f3f3f;

int n,m;
int a[MAXM],b[MAXM],l[MAXM],p[MAXM];
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

int deg[MAXN];

inline bool check(reg int x){
	cnt=1,memset(head,0,sizeof(head));
	memset(deg,0,sizeof(deg));
	reg int s=0,t=n+1;
	for(reg int i=1;i<=m;++i){
		if(l[i]<=x)
			--deg[a[i]],++deg[b[i]];
		else
			return false;
		if(p[i]<=x)
			Add_Tube(b[i],a[i],1);
	}
	for(reg int i=1;i<=n;++i)
		if(deg[i]&1)
			return false;
	reg int sum=0;
	for(reg int i=1;i<=n;++i)
		if(deg[i]>0)
			sum+=(deg[i]>>1),Add_Tube(s,i,deg[i]>>1);
		else
			Add_Tube(i,t,(-deg[i])>>1);
	return dinic(s,t)==sum;
}

int id[MAXM];

namespace Graph{
	int cnt,head[MAXN],to[MAXM],w[MAXM],Next[MAXM];
	inline void Add_Edge(reg int u,reg int v,reg int len){
		Next[++cnt]=head[u];
		to[cnt]=v;
		w[cnt]=len;
		head[u]=cnt;
		return;
	}
	bool vis[MAXM];
	int top,ans[MAXM];
	inline void dfs(reg int u){
		for(reg int i=head[u];i;i=Next[i]){
			reg int v=to[i];
			head[u]=i;
			if(!vis[w[i]]){
				vis[w[i]]=true;
				dfs(v);
				ans[++top]=w[i];
			}
		}
		return;
	}
}

inline void output(reg int ans){
	cnt=1,memset(head,0,sizeof(head));
	memset(deg,0,sizeof(deg));
	reg int s=0,t=n+1;
	for(reg int i=1;i<=m;++i){
		if(l[i]<=ans)
			--deg[a[i]],++deg[b[i]];
		if(p[i]<=ans){
			id[i]=cnt+1;
			Add_Tube(b[i],a[i],1);
		}
	}
	reg int sum=0;
	for(reg int i=1;i<=n;++i)
		if(deg[i]>0)
			sum+=(deg[i]>>1),Add_Tube(s,i,deg[i]>>1);
		else
			Add_Tube(i,t,(-deg[i])>>1);
	dinic(s,t);
	for(reg int i=1;i<=m;++i)
		if(l[i]<=ans&&p[i]<=ans)
			if(!w[id[i]])
				Graph::Add_Edge(b[i],a[i],i);
			else
				Graph::Add_Edge(a[i],b[i],i);
		else if(l[i]<=ans)
			Graph::Add_Edge(a[i],b[i],i);
		else
			Graph::Add_Edge(b[i],a[i],i);
	Graph::dfs(1);
	for(reg int i=Graph::top;i>=1;--i)
		printf("%d%c",Graph::ans[i],i==1?'\n':' ');
	return;
}

int main(void){
	n=read(),m=read();
	int Minx=inf,Maxx=-inf;
	for(reg int i=1;i<=m;++i){
		a[i]=read(),b[i]=read(),l[i]=read(),p[i]=read();
		if(l[i]>p[i])
			swap(a[i],b[i]),swap(l[i],p[i]);
		Minx=min(Minx,l[i]),Maxx=max(Maxx,p[i]);
	}
	reg int l=Minx,r=Maxx,mid;
	while(l<r){
		mid=(l+r)>>1;
		if(check(mid))
			r=mid;
		else
			l=mid+1;
	}
	if(!check(l))
		puts("NIE"),exit(0);
	printf("%d\n",l);
	output(l);
	return 0;
}