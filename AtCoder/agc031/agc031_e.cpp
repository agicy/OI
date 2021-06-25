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

inline ll readll(void){
	reg char ch=getchar();
	reg ll res=0;
	while(!isdigit(ch)) ch=getchar();
	while(isdigit(ch)) res=10*res+(ch^'0'),ch=getchar();
	return res;
}

inline int max(reg int a,reg int b){
	return a>b?a:b;
}

inline int min(reg int a,reg int b){
	return a<b?a:b;
}

inline ll max(reg ll a,reg ll b){
	return a>b?a:b;
}

const int MAXN=80+5;
const int MAXM=320+5;
const int inf=0x3f3f3f3f;

namespace Network{
	const int MAXV=4*MAXN;
	const int MAXE=(MAXN*MAXN*2+3*MAXN)*2;
	const ll inf=0x3f3f3f3f3f3f3f3f;
	int cnt,head[MAXV],to[MAXE],w[MAXE],Next[MAXE];
	ll p[MAXE];
	inline void Add_Edge(reg int u,reg int v,reg int len,reg ll val){
		Next[++cnt]=head[u];
		to[cnt]=v,w[cnt]=len,p[cnt]=val;
		head[u]=cnt;
		return;
	}
	inline void Add_Tube(reg int u,reg int v,reg int len,reg ll val){
		Add_Edge(u,v,len,val);
		Add_Edge(v,u,0,-val);
		return;
	}
	bool inque[MAXV];
	int cur[MAXV];
	ll dis[MAXV];
	queue<int> Q;
	inline bool spfa(int s,reg int t){
		fill(dis+s,dis+t+1,inf);
		inque[s]=true,dis[s]=0,Q.push(s);
		while(!Q.empty()){
			reg int u=Q.front();
			Q.pop();
			inque[u]=false;
			cur[u]=head[u];
			for(reg int i=head[u];i;i=Next[i]){
				int v=to[i];
				if(dis[v]>dis[u]+p[i]&&w[i]){
					dis[v]=dis[u]+p[i];
					if(!inque[v]){
						inque[v]=true;
						Q.push(v);
					}
				}
			}
		}
		return dis[t]!=inf;
	}
	bool vis[MAXV];
	inline int dfs(reg int u,reg int t,reg ll lim){
		if(u==t)
			return lim;
		vis[u]=true;
		reg int flow=0;
		for(reg int &i=cur[u];i;i=Next[i]){
			reg int v=to[i];
			if(dis[v]==dis[u]+p[i]&&w[i]&&!vis[v]){
				reg int f=dfs(v,t,min(lim-flow,w[i]));
				if(f){
					flow+=f;
					w[i]-=f,w[i^1]+=f;
					if(flow==lim)
						break;
				}
			}
		}
		vis[u]=false;
		return flow;
	}
	inline pair<int,ll> dinic(reg int s,reg int t){
		int res=0;
		ll cost=0;
		while(spfa(s,t)){
			reg int flow=dfs(s,t,inf);
			res+=flow,cost+=flow*dis[t];
		}
		return make_pair(res,cost);
	}
	inline void init(reg int s,reg int t){
		cnt=1,fill(head+s,head+t+1,0);
		return;
	}
}

struct Point{
	int x,y;
	ll v;
};

struct Limits{
	char ch;
	int a,b;
};

struct Interval{
	int l,r;
	inline Interval(reg int l=0,reg int r=0):l(l),r(r){
		return;
	}
	inline bool in(reg int x)const{
		return l<=x&&x<=r;
	}
};

inline Interval cap(const Interval& a,const Interval& b){
	return Interval(max(a.l,b.l),min(a.r,b.r));
}

int n,m;
Point a[MAXN];
Limits b[MAXM];

int main(void){
	n=read();
	for(reg int i=1;i<=n;++i)
		a[i].x=read(),a[i].y=read(),a[i].v=readll();
	m=read();
	for(reg int i=1;i<=m;++i){
		do
			b[i].ch=getchar();
		while(!isalpha(b[i].ch));
		b[i].a=read(),b[i].b=read();
	}
	reg ll ans=0;
	for(reg int k=1;k<=n;++k){
		static Interval invx[MAXN],invy[MAXN];
		fill(invx+1,invx+k+1,Interval(-inf,inf));
		fill(invy+1,invy+k+1,Interval(-inf,inf));
		for(reg int i=1;i<=m;++i){
			switch(b[i].ch){
				case 'L':{
					for(reg int j=b[i].b+1;j<=k;++j)
						invx[j]=cap(invx[j],Interval(b[i].a+1,inf));
					break;
				}
				case 'R':{
					for(reg int j=1;j<=k-b[i].b;++j)
						invx[j]=cap(invx[j],Interval(-inf,b[i].a-1));
					break;
				}
				case 'D':{
					for(reg int j=b[i].b+1;j<=k;++j)
						invy[j]=cap(invy[j],Interval(b[i].a+1,inf));
					break;
				}
				case 'U':{
					for(reg int j=1;j<=k-b[i].b;++j)
						invy[j]=cap(invy[j],Interval(-inf,b[i].a-1));
					break;
				}
			}
		}
		reg int s=0,t=2*k+2*n+1;
		Network::init(s,t);
		for(reg int i=1;i<=k;++i){
			Network::Add_Tube(s,i,1,0);
			Network::Add_Tube(k+n+n+i,t,1,0);
		}
		for(reg int i=1;i<=n;++i)
			Network::Add_Tube(k+i,k+n+i,1,-a[i].v);
		for(reg int i=1;i<=k;++i)
			for(reg int j=1;j<=n;++j){
				if(invx[i].in(a[j].x))
					Network::Add_Tube(i,k+j,1,0);
				if(invy[i].in(a[j].y))
					Network::Add_Tube(k+n+j,k+n+n+i,1,0);
			}
		pair<int,ll> res=Network::dinic(s,t);
		if(res.first==k)
			ans=max(ans,-res.second);
	}
	printf("%lld\n",ans);
	return 0;
}