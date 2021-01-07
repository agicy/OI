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

const int MAXN=50+5;
const int MAXM=50+5;
const int MAXV=MAXN+MAXM;
const int MAXE=2*(MAXN+MAXM+MAXN*MAXM);
const double eps=1e-5;
const double inf=1e18;

int n,m;
int a[MAXN],b[MAXM];
int c[MAXM][MAXN];
int suma;

int cnt,head[MAXV],to[MAXE],Next[MAXE];
double w[MAXE];

inline void Add_Edge(reg int u,reg int v,reg double len){
	Next[++cnt]=head[u];
	to[cnt]=v;
	w[cnt]=len;
	head[u]=cnt;
	return;
}

inline void Add_Tube(reg int u,reg int v,reg double len){
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
			if(dep[v]==-1&&w[i]>eps){
				dep[v]=dep[u]+1;
				Q[tail_++]=v;
			}
		}
	}
	return dep[t]!=-1;
}

int cur[MAXV];

inline double dfs(reg int u,reg int t,reg double lim){
	if(u==t)
		return lim;
	reg double flow=0;
	for(reg int &i=cur[u];i;i=Next[i]){
		reg int v=to[i];
		if(dep[v]==dep[u]+1&&w[i]>eps){
			reg double f=dfs(v,t,min(lim-flow,w[i]));
			if(f>eps){
				flow+=f;
				w[i]-=f,w[i^1]+=f;
				if(fabs(lim-flow)<eps)
					break;
			}
		}
	}
	return flow;
}

inline double dinic(reg int s,reg int t){
	reg double res=0;
	while(bfs(s,t)){
		memcpy(cur,head,sizeof(head));
		res+=dfs(s,t,inf);
	}
	return res;
}

inline bool check(reg double mid){
	cnt=1,memset(head,0,sizeof(head));
	reg int s=0,t=n+m+1;
	for(reg int i=1;i<=n;++i)
		Add_Tube(i,t,a[i]);
	for(reg int i=1;i<=m;++i)
		Add_Tube(s,n+i,b[i]*mid);
	for(reg int i=1;i<=m;++i)
		for(reg int j=1;j<=n;++j)
			if(c[i][j])
				Add_Tube(n+i,j,inf);
	reg double flow=dinic(s,t);
	return fabs(flow-suma)<eps;
}

int main(void){
	n=read(),m=read();
	for(reg int i=1;i<=n;++i)
		a[i]=read(),suma+=a[i];
	for(reg int i=1;i<=m;++i)
		b[i]=read();
	for(reg int i=1;i<=m;++i)
		for(reg int j=1;j<=n;++j)
			c[i][j]=read();
	reg double l=0,r=1e6,mid;
	while(r-l>eps){
		mid=0.5*(l+r);
		if(check(mid))
			r=mid;
		else
			l=mid;
	}
	printf("%lf\n",l);
	return 0;
}