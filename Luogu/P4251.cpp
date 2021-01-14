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

const int MAXN=250+5;
const int MAXM=250+5;
const int MAXV=MAXN+MAXM;
const int MAXE=2*(MAXN*MAXM+MAXN+MAXM);
const int inf=0x3f3f3f3f;

int n,m,k;
int a[MAXN][MAXM];
int cnt,head[MAXV],to[MAXE],w[MAXE],Next[MAXE];

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

inline bool check(reg int mid){
	cnt=1,memset(head,0,sizeof(head));
	reg int s=0,t=n+m+1;
	for(reg int i=1;i<=n;++i)
		for(reg int j=1;j<=m;++j)
			if(a[i][j]<=mid)
				Add_Tube(i,j+n,1);
	for(reg int i=1;i<=n;++i)
		Add_Tube(s,i,1);
	for(reg int i=1;i<=m;++i)
		Add_Tube(i+n,t,1);
	reg int flow=dinic(s,t);
	return flow>=n-k+1;
}

int main(void){
	n=read(),m=read(),k=read();
	int Min=inf,Max=-inf;
	for(reg int i=1;i<=n;++i)
		for(reg int j=1;j<=m;++j){
			a[i][j]=read();
			Max=max(Max,a[i][j]),Min=min(Min,a[i][j]);
		}
	reg int l=Min,r=Max,mid;
	while(l<r){
		mid=(l+r)>>1;
		if(check(mid))
			r=mid;
		else
			l=mid+1;
	}
	printf("%d\n",l);
	return 0;
}