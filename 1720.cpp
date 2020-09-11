#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++)
static char buf[100000],*p1=buf,*p2=buf;
inline int read(void){
	reg char ch=getchar();
	reg int res=0;
	while(ch<'0'||'9'<ch)ch=getchar();
	while('0'<=ch&&ch<='9')res=10*res+ch-'0',ch=getchar();
	return res;
}

const int MAXN=1e3+5;
const int MAXM=1e4+5;
const double eps=1e-4;
const double inf=1e8;

int n,m;
int cnt,head[MAXN],to[MAXM],w[MAXM],Next[MAXM];

inline void Add_Edge(reg int u,reg int v,reg int len){
	Next[++cnt]=head[u];
	to[cnt]=v;
	w[cnt]=len;
	head[u]=cnt;
	return;
}

bool vis[MAXN];
double dis[MAXN];

inline bool spfa(reg int u,reg double mid){
	vis[u]=true;
	for(reg int i=head[u];i;i=Next[i]){
		reg int v=to[i];
		if(dis[u]+w[i]-mid>=dis[v])
			continue;
		if(vis[v]&&dis[u]+w[i]-mid<=0)
			return true;
		dis[v]=dis[u]+w[i]-mid;
		if(!vis[v]&&spfa(v,mid))
			return true;
	}
	vis[u]=false;
	return false;
}

inline bool check(reg double mid){
	for(reg int i=1;i<=n;++i)
		vis[i]=false,dis[i]=0;
	for(reg int i=1;i<=n;++i)
		if(!dis[i]&&spfa(i,mid))
			return true;
	return false;
}

double l=inf,r=-inf,mid;

int main(void){
	n=read(),m=read();
	for(reg int i=1;i<=m;++i){
		static int u,v,w;
		u=read(),v=read(),w=read();
		Add_Edge(u,v,w);
		l=min(l,1.0*w),r=max(r,1.0*w);
	}
	reg bool flag=false;
	while(r-l>=eps){
		mid=0.5*(l+r);
		if(check(mid))
			flag=true,r=mid;
		else
			l=mid;
	}
	if(!flag)
		puts("PaPaFish is laying egg!");
	else
		printf("%.2lf\n",l);
	return 0;
}