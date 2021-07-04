#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;

bool st;

#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++)
static char buf[1<<21],*p1=buf,*p2=buf;
inline int read(void){
	reg char ch=getchar();
	reg int res=0;
	while(!isdigit(ch)) ch=getchar();
	while(isdigit(ch)) res=10*res+(ch^'0'),ch=getchar();
	return res;
}

struct Vector{
	int x,y;
	inline Vector(reg int x=0,reg int y=0):x(x),y(y){
		return;
	}
	inline Vector operator+(const Vector& a)const{
		return Vector(x+a.x,y+a.y);
	}
	inline Vector operator-(const Vector& a)const{
		return Vector(x-a.x,y-a.y);
	}
};

inline int dot(const Vector& a,const Vector& b){
	return a.x*b.x+a.y*b.y;
}

inline int cross(const Vector& a,const Vector& b){
	return a.x*b.y-a.y*b.x;
}

typedef Vector Point;

const int MAXN=70+5;
const int inf=0x3f3f3f3f;

namespace Network{
	const int MAXV=MAXN*2;
	const int MAXE=(MAXN*MAXN+MAXN*2)*2;
	const int inf=0x3f3f3f3f;
	int cnt,head[MAXV],to[MAXE],w[MAXE],p[MAXE],nxt[MAXE];
	inline void init(reg int s,reg int t){
		cnt=1,fill(head+s,head+t+1,0);
		return;
	}
	inline void Add_Edge(reg int u,reg int v,reg int lim,reg int cot){
		nxt[++cnt]=head[u];
		to[cnt]=v,w[cnt]=lim,p[cnt]=cot;
		head[u]=cnt;
		return;
	}
	inline void Add_Tube(reg int u,reg int v,reg int lim,reg int cot){
		Add_Edge(u,v,lim,cot),Add_Edge(v,u,0,-cot);
		return;
	}
	bool inque[MAXV];
	int dis[MAXV];
	int cur[MAXV];
	queue<int> Q;
	inline bool spfa(int s,reg int t){
		fill(dis+s,dis+t+1,inf);
		inque[s]=true,dis[s]=0,Q.push(s);
		while(!Q.empty()){
			reg int u=Q.front();
			Q.pop();
			inque[u]=false;
			cur[u]=head[u];
			for(reg int i=head[u];i;i=nxt[i]){
				int v=to[i];
				if(dis[v]>dis[u]+p[i]&&w[i]){
					dis[v]=dis[u]+p[i];
					if(!inque[v])
						inque[v]=true,Q.push(v);
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
		for(reg int& i=cur[u];i;i=nxt[i]){
			reg int v=to[i];
			if(dis[v]==dis[u]+p[i]&&w[i]&&!vis[v]){
				reg int f=dfs(v,t,min(lim-flow,w[i]));
				if(f){
					flow+=f,w[i]-=f,w[i^1]+=f;
					if(flow==lim)
						break;
				}
			}
		}
		vis[u]=false;
		return flow;
	}
	inline pair<int,int> dinic(reg int s,reg int t){
		int flow=0,cost=0;
		while(spfa(s,t)){
			reg int f=dfs(s,t,inf);
			flow+=f,cost+=f*dis[t];
		}
		return make_pair(flow,cost);
	}
}

int n;
int a[MAXN][MAXN],b[MAXN][MAXN];
int w[MAXN][MAXN];
int ans;

inline Point getVal(void){
	Point res(0,0);
	reg int s=0,t=2*n+1;
	Network::init(s,t);
	for(reg int i=1;i<=n;++i)
		Network::Add_Tube(s,i,1,0),Network::Add_Tube(i+n,t,1,0);
	for(reg int i=1;i<=n;++i)
		for(reg int j=1;j<=n;++j)
			Network::Add_Tube(i,j+n,1,w[i][j]);
	Network::dinic(s,t);
	for(reg int i=1;i<=n;++i)
		for(reg int j=Network::head[i];j;j=Network::nxt[j])
			if(!Network::w[j]&&n<Network::to[j]&&Network::to[j]<=n*2){
				res=res+Point(a[i][Network::to[j]-n],b[i][Network::to[j]-n]);
				break;
			}
	ans=min(ans,res.x*res.y);
	return res;
}

inline void solve(const Point& A,const Point& B){
	for(reg int i=1;i<=n;++i)
		for(reg int j=1;j<=n;++j)
			w[i][j]=(A.y-B.y)*a[i][j]+(B.x-A.x)*b[i][j];
	Point C=getVal();
	if(cross(B-A,C-A)<0)
		solve(A,C),solve(C,B);
	return;
}

bool ed;

int main(void){
	reg int t=read();
	while(t--){
		n=read();
		for(reg int i=1;i<=n;++i)
			for(reg int j=1;j<=n;++j)
				a[i][j]=read();
		for(reg int i=1;i<=n;++i)
			for(reg int j=1;j<=n;++j)
				b[i][j]=read();
		ans=inf;
		for(reg int i=1;i<=n;++i)
			for(reg int j=1;j<=n;++j)
				w[i][j]=a[i][j];
		Point A=getVal();
		for(reg int i=1;i<=n;++i)
			for(reg int j=1;j<=n;++j)
				w[i][j]=b[i][j];
		Point B=getVal();
		solve(A,B);
		printf("%d\n",ans);
	}
	fprintf(stderr,"%.3lf s\n",1.0*clock()/CLOCKS_PER_SEC);
	fprintf(stderr,"%.3lf MiB\n",(&ed-&st)/1048576.0);
	return 0;
}