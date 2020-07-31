#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
//#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++)
static char buf[100000],*p1=buf,*p2=buf;
inline int read(void){
	reg char ch=getchar();
	reg int res=0;
	while(ch<'0'||'9'<ch)ch=getchar();
	while('0'<=ch&&ch<='9')res=10*res+ch-'0',ch=getchar();
	return res;
}

const int MAXM=30+5;
const int MAXN=30+5;
const int MAXNM=MAXN*MAXM;
const int MAXE=MAXN*MAXM*8;
const int dx[]={-2,-2,-1,-1,1,1,2,2};
const int dy[]={-1,1,-2,2,-2,2,-1,1};

int m,n;
int M[MAXM][MAXN];
int sx,sy,ex,ey;

struct Node{
	int x,y,dis;
	inline Node(reg int x=0,reg int y=0,reg int dis=0):x(x),y(y),dis(dis){
		return;
	}
	inline bool operator<(const Node& a)const{
		return dis<a.dis;
	}
	inline bool operator>(const Node& a)const{
		return dis>a.dis;
	}
};

bool vis[MAXM][MAXN];
int dis[MAXM][MAXN];
priority_queue<Node,vector<Node>,greater<Node>/**/> Q;

inline bool check(reg int x,reg int y){
	return 1<=x&&x<=m&&1<=y&&y<=n&&M[x][y]!=2;
}

inline void Dijkstra(reg int sx,reg int sy){
	memset(vis,false,sizeof(vis));
	memset(dis,0X3F,sizeof(dis));
	dis[sx][sy]=0,Q.push(Node(sx,sy,0));
	while(!Q.empty()){
		static Node u;
		u=Q.top();
		Q.pop();
		reg int x=u.x,y=u.y;
		if(vis[x][y])
			continue;
		vis[x][y]=true;
		for(reg int i=0;i<8;++i){
			reg int fx=x+dx[i],fy=y+dy[i];
			if(check(fx,fy)&&dis[fx][fy]>dis[x][y]+(M[fx][fy]==0)){
				dis[fx][fy]=dis[x][y]+(M[fx][fy]==0);
				Q.push(Node(fx,fy,dis[fx][fy]));
			}
		}
	}
	return;
}

int cnt,head[MAXNM],to[MAXE],Next[MAXE];

inline void Add_Edge(reg int u,reg int v){
	Next[++cnt]=head[u];
	to[cnt]=v;
	head[u]=cnt;
	return;
}

int id[MAXM][MAXN];
int indeg[MAXNM];
ll f[MAXNM];

inline void Topo(void){
	queue<int> Q;
	f[id[sx][sy]]=1;
	Q.push(id[sx][sy]);
	while(!Q.empty()){
		reg int u=Q.front();
		Q.pop();
		for(reg int i=head[u];i;i=Next[i]){
			int v=to[i];
			--indeg[v];
			f[v]+=f[u];
			if(!indeg[v])
				Q.push(v);
		}
	}
	return;
}

int main(void){
	m=read(),n=read();
	for(reg int i=1;i<=m;++i)
		for(reg int j=1;j<=n;++j){
			M[i][j]=read();
			if(M[i][j]==3)
				sx=i,sy=j;
			else if(M[i][j]==4)
				ex=i,ey=j;
		}
	Dijkstra(sx,sy);
	reg int tot=0;
	for(reg int i=1;i<=m;++i)
		for(reg int j=1;j<=n;++j)
			id[i][j]=++tot;
	for(reg int i=1;i<=m;++i)
		for(reg int j=1;j<=n;++j)
			for(reg int k=0;k<8;++k){
				reg int fx=i+dx[k],fy=j+dy[k];
				if(check(fx,fy)&&dis[fx][fy]==dis[i][j]+(M[fx][fy]==0)){
					++indeg[id[fx][fy]];
					Add_Edge(id[i][j],id[fx][fy]);
				}
			}
	Topo();
	printf("%d\n%lld\n",dis[ex][ey],f[id[ex][ey]]);
	return 0;
}
