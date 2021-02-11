#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++)
static char buf[100000],*p1=buf,*p2=buf;
inline int read(void){
	reg bool f=false;
	reg char ch=getchar();
	reg int res=0;
	while(!isdigit(ch))f|=(ch=='-'),ch=getchar();
	while(isdigit(ch))res=10*res+(ch^'0'),ch=getchar();
	return f?-res:res;
}

const int MAXN=5e4+5;
const int MAXV=MAXN*2;
const int MAXE=1e6+5;
const int inf=0x3f3f3f3f;

int n,m;
int s,t;
int cnt=1,head[MAXV],to[MAXE],w[MAXE],Next[MAXE];

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
	reg int _head=0,_tail=0;
	memset(dep,-1,sizeof(dep));
	dep[s]=1,Q[_tail++]=s;
	while(_head<_tail){
		reg int u=Q[_head++];
		for(reg int i=head[u];i;i=Next[i]){
			reg int v=to[i];
			if(dep[v]==-1&&w[i]){
				dep[v]=dep[u]+1;
				Q[_tail++]=v;
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

struct Point{
	int x,y;
	inline Point(reg int x=0,reg int y=0):x(x),y(y){
		return;
	}
	inline bool operator<(const Point& a)const{
		return x<a.x||(x==a.x&&y<a.y);
	}
	inline Point operator+(const Point& a)const{
		return Point(x+a.x,y+a.y);
	}
};

Point p[MAXN];

map<Point,bool> vis;
map<Point,int> M,Id,f;

inline void link(reg int a,reg int b,reg int c){
	if(!vis[Point(s,a)])
		Add_Tube(s,a<<1,inf),vis[Point(1,a)]=true;
	if(!vis[Point(a,b)])
		Add_Tube(a<<1|1,b<<1,inf),vis[Point(a,b)]=true;
	if(!vis[Point(b,c)])
		Add_Tube(b<<1|1,c<<1,inf),vis[Point(b,c)]=true;
	if(!vis[Point(c,t)])
		Add_Tube(c<<1|1,t,inf),vis[Point(c,a)]=true;
	return;
}

int main(void){
	n=read();
	reg int tot=0;
	for(reg int i=1;i<=n;++i){
		static int x,y,z,c;
		x=read(),y=read(),z=read(),c=read();
		p[i]=Point(x-z,y-z);
		if(!Id[p[i]])
			Id[p[i]]=++tot;
		M[p[i]]+=c;
		f[p[i]]=(!((x+y+z)%3));
	}
	s=1,t=(tot+1)<<1;
	reg int sum=0;
	for(reg int i=1;i<=n;++i)
		if(f[p[i]]<2){
			reg int pt=Id[p[i]],w=M[p[i]]*(10+f[p[i]]);
			sum+=w;
			Add_Tube(2*pt,2*pt+1,w);
			if(!f[p[i]]){
				f[p[i]]=2;
				continue;
			}
			static int a[MAXN],b[MAXN];
			reg int totA=0,totB=0;
			f[p[i]]=2;
			if(!(a[++totA]=Id[p[i]+Point(0,1)]))
				--totA;
			if(!(a[++totA]=Id[p[i]+Point(1,0)]))
				--totA;
			if(!(a[++totA]=Id[p[i]+Point(-1,-1)]))
				--totA;
			if(!(b[++totB]=Id[p[i]+Point(0,-1)]))
				--totB;
			if(!(b[++totB]=Id[p[i]+Point(-1,0)]))
				--totB;
			if(!(b[++totB]=Id[p[i]+Point(1,1)]))
				--totB;
			for(reg int j=1;j<=totA;++j)
				for(reg int k=1;k<=totB;++k)
					link(a[j],pt,b[k]);
		}
	printf("%.1lf\n",(sum-dinic(s,t))/10.0);
	return 0;
}