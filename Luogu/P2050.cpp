#include <iostream>
#include <iomanip>
#include <cstring>
#include <map>
#include <queue>
#define inf 2147483646
#define N 10000
using namespace std;
#define reg register

struct ed{
	int u,w,next,f;
}e[1000000];
int g[1000][2000],a[2000];
int n,m,st=1,ans,cost,sm,fir[30000],c[30000],d[30000];
int vis[30000],sp[30000];
queue<int> q; bool v[30000];
map<int,int> ha;

inline void Add_Edge(reg int u,reg int v,reg int len,reg int val){
	Next[++cnt]=head[u];
	to[cnt]=v;
	w[cnt]=len;
	p[cnt]=val;
	head[u]=cnt;
	return;
}

inline void Add_Tube(reg int u,reg int v,reg int len,reg int val){
	Add_Edge(u,v,len,val);
	Add_Edge(v,u,0,-val);
	return;
}

bool spfa()
{
	for (int i=0;i<=N;i++) d[i]=inf/2,c[i]=fir[i],v[i]=0;
	q.push(0); v[0]=1; d[0]=0;
	while (!q.empty())
	{
		int k=q.front(); q.pop();
		v[k]=0;
		for (int i=fir[k];i;i=e[i].next){
			int u=e[i].u,w=e[i].f;
			if (d[u]>d[k]+w&&e[i].w){
				d[u]=d[k]+w; if (!v[u]) v[u]=1,q.push(u);
			}
		}
	}
	return (d[N]<inf/2);
}

int dfs(int p,int now)
{
	if (p==N){v[N]=1; return now;}
	int mw=0;
	v[p]=1;
	for (int i=fir[p];i;i=e[i].next)
	{
		int u=e[i].u,w=e[i].f;
		if (d[u]==d[p]+w&&e[i].w&&(!v[u]||u==N))
		if (mw=dfs(u,min(e[i].w,now)))
		{
			e[i].w-=mw; e[i^1].w+=mw;
			cost+=mw*w; return mw;
		}
	}
}

void dinic()
{
	while (spfa()) {
		 ans+=dfs(0,inf);
		 for (int i=fir[N];i;i=e[i].next){
			int u=e[i].u,w=e[i].w;
			if (w&&!vis[u]) {
				vis[u]=1; int co=ha[u]; sp[co]++;
				add(++sm,N,1,0); ha[sm]=co;
				for (int i=1;i<=n;i++) add(i,sm,1,sp[co]*g[i][co]);
			 }
		 }
	}
}

int main()
{
	n=read(),m=read();
	reg int sum=0;
	for(reg int i=1;i<=n;++i){
		a[i]=read();
		sum+=a[i];
	}
	for(reg int i=1;i<=n;++i)
		for(reg int j=1;j<=m;++j)
			g[i][j]=read();
	for(reg int i=1;i<=n;++i)
	for (int i=1;i<=n;i++) add(0,i,a[i],0);
	sm=n;
	for(int j=1;j<=m;j++){
		add(++sm,N,1,0); ha[sm]=j; sp[j]=1;
		for (int i=1;i<=n;i++) add(i,sm,1,g[i][j]);
	}
	dinic();
	cout<<cost<<endl;
}