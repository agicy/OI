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

const int MAXN=30+5;
const int MAXV=MAXN*MAXN;
const int MAXE=1e5+5;
const int inf=0X3F3F3F3F;

int n,m;
int S,E;
int M[MAXN][MAXN];
int p[MAXN][MAXN];
bool vis[MAXN][MAXN];
int cnt,head[MAXV],to[MAXE],Next[MAXE];

inline void Add_Edge(reg int u,reg int v){
	Next[++cnt]=head[u];
	to[cnt]=v;
	head[u]=cnt;
	return;
}

inline bool check(reg int x,reg int y){
	return 1<=x&&x<=n&&1<=y&&y<=m&&!vis[x][y];
}

inline void DFS(reg int id,reg int x,reg int y){
	vis[x][y]=true;
	const int dx[]={-2,-2,-1,-1,1,1,2,2};
	const int dy[]={-1,1,-2,2,-2,2,-1,1};
	for(reg int i=0;i<8;++i){
		reg int fx=x+dx[i],fy=y+dy[i];
		if(check(fx,fy)){
			if(M[fx][fy]==1)
				DFS(id,fx,fy);
			else{
				vis[fx][fy]=true;
				Add_Edge(id,p[fx][fy]);
			}
		}
	}
	return;
}

bool inque[MAXV];
int dis[MAXV];
ll f[MAXV];
queue<int> Q;

inline void SPFA(void){
	memset(dis,0X3F,sizeof(dis));
	inque[S]=true,dis[S]=0,f[S]=1,Q.push(S);
	while(!Q.empty()){
		reg int u=Q.front();
		Q.pop();
		inque[u]=false;
		for(reg int i=head[u];i;i=Next[i]){
			int v=to[i];
			if(dis[v]>dis[u]+1){
				dis[v]=dis[u]+1;
				f[v]=f[u];
				if(!inque[v]){
					inque[v]=true;
					Q.push(v);
				}
			}
			else if(dis[v]==dis[u]+1)
				f[v]+=f[u];
		}
	}
	return;
}

int main(void){
	n=read(),m=read();
	reg int cnt=0;
	for(reg int i=1;i<=n;++i)
		for(reg int j=1;j<=m;++j)
			p[i][j]=++cnt;
	for(reg int i=1;i<=n;++i)
		for(reg int j=1;j<=m;++j){
			M[i][j]=read();
			if(M[i][j]==3)
				S=p[i][j];
			if(M[i][j]==4)
				E=p[i][j];
		}
	for(reg int i=1;i<=n;++i)
		for(reg int j=1;j<=m;++j)
			if(M[i][j]==0||M[i][j]==3){
				memset(vis,false,sizeof(vis));
				DFS(p[i][j],i,j);
			}
	SPFA();
	if(dis[E]<inf)
		printf("%d\n%lld\n",dis[E]-1,f[E]);
	else
		puts("-1");
	return 0;
}