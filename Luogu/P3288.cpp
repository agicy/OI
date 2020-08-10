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

const int MAXN=5e3+5;
const int MAXM=3e3+5;
const double inf=1e8;
const double eps=1e-4;

int n,m;
int cnt,head[MAXN],to[MAXM<<1],w[MAXM<<1],Next[MAXM<<1];

inline void Add_Edge(reg int u,reg int v,reg int len){
	Next[++cnt]=head[u];
	to[cnt]=v;
	w[cnt]=len;
	head[u]=cnt;
	return;
}

bitset<MAXN> vis;
double dis[MAXN];
double x;

inline bool spfa(reg int u){
	vis[u]=true;
	for(reg int i=head[u];i;i=Next[i]){
		reg int v=to[i];
		if(dis[v]>dis[u]+w[i]+x){
			dis[v]=dis[u]+w[i]+x;
			if(vis[v]||spfa(v))
				return true;
		}
	}
	vis[u]=false;
	return false;
}

inline bool check(reg double mid){
	vis.reset();
	memset(dis,0,sizeof(dis));
	x=mid;
	for(reg int i=1;i<=n;++i)
		if(spfa(i))
			return true;
	return false;
}

int main(void){
	n=read()+2,m=read();
	for(reg int i=1;i<=m;++i){
		static int u,v,a,b,c,d;
		u=read(),v=read(),a=read(),b=read(),c=read(),d=read();
		if(c)
			Add_Edge(v,u,a-d);
		Add_Edge(u,v,b+d);
	}
	reg double l=0,r=inf,mid;
	while(r-l>eps){
		mid=0.5*(l+r);
		if(check(mid))
			l=mid;
		else
			r=mid;
	}
	printf("%.2lf\n",l);
	return 0;
}