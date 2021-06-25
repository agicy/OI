#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++)
static char buf[1<<21],*p1=buf,*p2=buf;
inline int read(void){
	reg char ch=getchar();
	reg int res=0;
	while(!isdigit(ch)) ch=getchar();
	while(isdigit(ch)) res=10*res+(ch^'0'),ch=getchar();
	return res;
}

inline double min(reg double a,reg double b){
	return a<b?a:b;
}

const int MAXN=50+5;
const int MAXM=MAXN*(MAXN-1)+5;
const int MAXV=MAXN;
const int MAXE=MAXM*2;
const int inf=0x3f3f3f3f;

int n,m;
int cnt=1,head[MAXV],to[MAXE],w[MAXE],p[MAXE],Next[MAXE];

inline void Add_Edge(reg int u,reg int v,reg int len,reg int val){
	Next[++cnt]=head[u];
	to[cnt]=v,w[cnt]=len,p[cnt]=val;
	head[u]=cnt;
	return;
}

inline void Add_Tube(reg int u,reg int v,reg int len,reg int val){
	Add_Edge(u,v,len,val);
	Add_Edge(v,u,0,-val);
	return;
}

bool inque[MAXV];
int pre[MAXV],dis[MAXV],lim[MAXV];
queue<int> Q;

inline bool spfa(int s,reg int t){
	fill(dis+1,dis+n+1,inf);
	inque[s]=true,dis[s]=0,lim[s]=inf,Q.push(s);
	while(!Q.empty()){
		reg int u=Q.front();
		Q.pop();
		inque[u]=false;
		for(reg int i=head[u];i;i=Next[i]){
			int v=to[i];
			if(dis[v]>dis[u]+p[i]&&w[i]){
				pre[v]=i,dis[v]=dis[u]+p[i],lim[v]=min(lim[u],w[i]);
				if(!inque[v]){
					inque[v]=true;
					Q.push(v);
				}
			}
		}
	}
	return dis[t]<inf;
}

int tot,cost[MAXM],flow[MAXM];

inline int EK(reg int s,reg int t){
	reg int res=0;
	while(spfa(s,t)){
		reg int ptr=t;
		while(ptr!=s){
			w[pre[ptr]]-=lim[t],w[pre[ptr]^1]+=lim[t];
			ptr=to[pre[ptr]^1];
		}
		++tot;
		cost[tot]=cost[tot-1]+lim[t]*dis[t],flow[tot]=flow[tot-1]+lim[t];
		res+=lim[t];
	}
	return res;
}

inline double getVal(reg int a,reg int ptr){
	return 1.0*(cost[a]+ptr)/flow[a];
}

inline double query(reg int l,reg int r,reg int ptr){
	if(r-l<=3){
		reg double res=1e20;
		for(reg int i=l;i<=r;++i)
			res=min(res,getVal(i,ptr));
		return res;
	}
	reg int mid1=(2*l+r)/3,mid2=(l+2*r)/3;
	return getVal(mid1,ptr)<getVal(mid2,ptr)?query(l,mid2,ptr):query(mid1,r,ptr);
}

int main(void){
	n=read(),m=read();
	for(reg int i=1;i<=m;++i){
		static int u,v,w;
		u=read(),v=read(),w=read();
		Add_Tube(u,v,1,w);
	}
	EK(1,n);
	reg int q=read();
	while(q--)
		printf("%.10lf\n",query(1,tot,read()));
	return 0;
}