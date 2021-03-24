#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;

const int MAXN=3e3+5;
const int MAXM=1e4+5;
const double eps=1e-10;

int n,m;
int cnt,head[MAXN],to[MAXM],Next[MAXM];
double w[MAXM];

inline void Add_Edge(reg int u,reg int v,reg double len){
	Next[++cnt]=head[u];
	to[cnt]=v,w[cnt]=len;
	head[u]=cnt;
	return;
}

bool vis[MAXN];
double dis[MAXN];
double x;

inline bool spfa(reg int u){
	vis[u]=true;
	for(reg int i=head[u];i;i=Next[i]){
		reg int v=to[i];
		if(dis[v]>dis[u]+w[i]-x){
			dis[v]=dis[u]+w[i]-x;
			if(vis[v]||spfa(v))
				return true;
		}
	}
	vis[u]=false;
	return false;
}

inline bool check(reg double mid){
	fill(vis+1,vis+n+1,false);
	fill(dis+1,dis+n+1,0);
	x=mid;
	for(reg int i=1;i<=n;++i)
		if(spfa(i))
			return true;
	return false;
}

int main(void){
	scanf("%d%d",&n,&m);
	for(reg int i=1;i<=m;++i){
		static int u,v;
		static double w;
		scanf("%d%d%lf",&u,&v,&w);
		Add_Edge(u,v,w);
	}
	reg double l=-1e7,r=1e7,mid;
	while(r-l>eps){
		mid=(l+r)*0.5;
		if(check(mid))
			r=mid;
		else
			l=mid;
	}
	printf("%.8lf\n",l);
	return 0;
}