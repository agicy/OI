#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
#define flush() (fwrite(wbuf,1,wp1,stdout),wp1=0)
#define putchar(c) (wp1==wp2&&(flush(),0),wbuf[wp1++]=c)
static char wbuf[1<<21];int wp1;const int wp2=1<<21;
inline int read(void){
	reg bool f=false;
	reg char ch=getchar();
	reg int res=0;
	while(!isdigit(ch))f|=(ch=='-'),ch=getchar();
	while(isdigit(ch)) res=10*res+(ch^'0'),ch=getchar();
	return f?-res:res;
}

inline void writeln(reg int x){
	static char buf[32];
	reg int p=-1;
	if(!x) putchar('0');
	else while(x) buf[++p]=(x%10)^'0',x/=10;
	while(~p) putchar(buf[p--]);
	putchar('\n');
	return;
}

const int MAXN=100+5;
#define eps 1e-5

namespace Network{
	const int MAXV=MAXN*2+MAXN*MAXN;
	const int MAXE=(MAXN*2+MAXN*MAXN)*2;
	int cnt,head[MAXV],to[MAXE],w[MAXE],Next[MAXE];
	double p[MAXE];
	inline void Add_Edge(reg int u,reg int v,reg int len,reg double val){
		Next[++cnt]=head[u];
		to[cnt]=v,w[cnt]=len,p[cnt]=val;
		head[u]=cnt;
		return;
	}
	inline void Add_Tube(reg int u,reg int v,reg int len,reg double val){
		Add_Edge(u,v,len,val);
		Add_Edge(v,u,0,-val);
		return;
	}
	bool inque[MAXV];
	int cur[MAXV];
	double dis[MAXV];
	queue<int> Q;
	inline bool spfa(int s,reg int t){
		const double inf=1e20;
		fill(dis+s,dis+t+1,inf);
		inque[s]=true,dis[s]=0,Q.push(s);
		while(!Q.empty()){
			reg int u=Q.front();
			Q.pop();
			inque[u]=false,cur[u]=head[u];
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
	inline int dfs(reg int u,reg int t,reg int lim){
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
	inline pair<int,double> dinic(reg int s,reg int t){
		const int inf=0x3f3f3f3f;
		int flow=0;
		double cost=0;
		while(spfa(s,t)){
			reg int tmp=dfs(s,t,inf);
			flow+=tmp,cost+=tmp*dis[t];
		}
		return make_pair(flow,cost);
	}
	inline void Init(reg int s,reg int t){
		cnt=1,fill(head+s,head+t+1,0);
		return;
	}
}

struct Point{
	int x,y;
};

inline double sqr(reg double x){
	return x*x;
}

inline double getDis(const Point& a,const Point& b){
	return sqrt(sqr(a.x-b.x)+sqr(a.y-b.y));
}

int n;
Point a[MAXN],b[MAXN];

int main(void){
	while(scanf("%d",&n)!=EOF){
		reg int s=0,t=2*n+1;
		Network::Init(s,t);
		for(reg int i=1;i<=n;++i)
			a[i].x=read(),a[i].y=read();
		for(reg int i=1;i<=n;++i)
			b[i].x=read(),b[i].y=read();
		for(reg int i=1;i<=n;++i)
			for(reg int j=1;j<=n;++j)
				Network::Add_Tube(i,j+n,1,getDis(a[i],b[j]));
		for(reg int i=1;i<=n;++i)
			Network::Add_Tube(s,i,1,0);
		for(reg int i=1;i<=n;++i)
			Network::Add_Tube(i+n,t,1,0);
		Network::dinic(s,t);
		for(reg int u=1;u<=n;++u)
			for(reg int i=Network::head[u];i;i=Network::Next[i])
				if(!Network::w[i]){
					writeln(Network::to[i]-n);
					break;
				}
	}
	flush();
	return 0;
}