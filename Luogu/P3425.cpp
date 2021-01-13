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

const int MAXN=1e4+5;
const int MAXM=1e4+5;
const int MAXV=MAXN+MAXM;
const int MAXE=2*(MAXM*3+MAXN);
const int inf=0x3f3f3f3f;

int cnt=1,head[MAXV],to[MAXE],w[MAXE],Next[MAXE];

inline void Add_Edge(reg int u,reg int v,reg int len){
	Next[++cnt]=head[u];
	to[cnt]=v,w[cnt]=len;
	head[u]=cnt;
	return;
}

inline int Add_Tube(reg int u,reg int v,reg int len){
	Add_Edge(u,v,len);
	Add_Edge(v,u,0);
	return cnt-1;
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

int n,m;
int s,t;
int u[MAXM],v[MAXM],id[MAXM];

inline void build(reg int mid){
	cnt=1,memset(head,0,sizeof(head));
	for(reg int i=1;i<=m;++i){
		Add_Tube(s,i,1);
		id[i]=Add_Tube(i,u[i]+m,1);
		Add_Tube(i,v[i]+m,1);
	}
	for(reg int i=1;i<=n;++i)
		Add_Tube(i+m,t,mid);
	return;
}

inline bool check(reg int mid){
	build(mid);
	reg int flow=dinic(s,t);
	return flow>=m;
}

int main(void){
	n=read(),m=read();
	s=0,t=n+m+1;
	for(reg int i=1;i<=m;++i)
		u[i]=read(),v[i]=read();
	reg int l=0,r=m,mid;
	while(l<r){
		mid=(l+r)>>1;
		if(check(mid))
			r=mid;
		else
			l=mid+1;
	}
	check(l);
	printf("%d\n",l);
	for(reg int i=1;i<=m;++i)
		if(!w[id[i]])
			puts("1");
		else
			puts("0");
	return 0;
}