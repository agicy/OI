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
	while(ch<'0'||'9'<ch)f|=(ch=='-'),ch=getchar();
	while('0'<=ch&&ch<='9')res=10*res+ch-'0',ch=getchar();
	return f?-res:res;
}

const double eps=1e-8;

int dcmp(reg double x){
	if(fabs(x)<eps)
		return 0;
	else
		return x<0?-1:1;
}

const int MAXN=100+5;
const int MAXV=2*MAXN;
const int MAXE=(MAXN*2+MAXN*MAXN)*2;
const double inf=1e18;

struct Node{
	int x,y;
};

inline double sqr(reg double x){
	return x*x;
}

inline double getDis(const Node& a,const Node& b){
	return sqrt(sqr(a.x-b.x)+sqr(a.y-b.y));
}

int n;
Node B[MAXN],W[MAXN];
int cnt=1,head[MAXV],to[MAXE],w[MAXE],Next[MAXE];
double p[MAXE];

inline void Add_Edge(reg int u,reg int v,reg int len,reg double val){
	Next[++cnt]=head[u];
	to[cnt]=v;
	w[cnt]=len;
	p[cnt]=val;
	head[u]=cnt;
	return;
}

inline void Add_Tube(reg int u,reg int v,reg int len,reg double val){
	Add_Edge(u,v,len,val);
	Add_Edge(v,u,0,-val);
	return;
}

bool inque[MAXV];
double dis[MAXV];
queue<int> Q;

inline bool spfa(int s,reg int t){
	fill(dis+s,dis+t+1,inf);
	inque[s]=true,dis[s]=0,Q.push(s);
	while(!Q.empty()){
		reg int u=Q.front();
		Q.pop();
		inque[u]=false;
		for(reg int i=head[u];i;i=Next[i]){
			int v=to[i];
			if(dcmp(dis[u]+p[i]-dis[v])<0&&w[i]!=0){
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

double Cost;
bool vis[MAXV];
int cur[MAXV];

inline int dfs(reg int u,reg int t,reg int lim){
	if(u==t){
		Cost+=lim*dis[u];
		return lim;
	}
	reg int flow=0;
	vis[u]=true;
	for(reg int &i=cur[u];i;i=Next[i]){
		reg int v=to[i];
		if(dcmp(dis[u]+p[i]-dis[v])==0&&w[i]!=0&&!vis[v]){
			reg int f=dfs(v,t,min(lim-flow,w[i]));
			if(f){
				flow+=f;
				w[i]-=f;
				w[i^1]+=f;
				if(flow==lim)
					break;
			}
		}
	}
	vis[u]=false;
	return flow;
}

inline int dinic(reg int s,reg int t){
	reg int res=0;
	while(spfa(s,t)){
		memcpy(cur,head,sizeof(head));
		res+=dfs(s,t,0x3f3f3f3f);
	}
	return res;
}

double Dis[MAXN][MAXN];

int main(void){
	n=read();
	for(reg int i=1;i<=n;++i)
		B[i].x=read(),B[i].y=read();
	for(reg int i=1;i<=n;++i)
		W[i].x=read(),W[i].y=read();
	reg int s=0,t=2*n+1;
	for(reg int i=1;i<=n;++i)
		Add_Tube(s,i,1,0);
	for(reg int i=1;i<=n;++i)
		Add_Tube(i+n,t,1,0);
	for(reg int i=1;i<=n;++i)
		for(reg int j=1;j<=n;++j)
			Dis[i][j]=getDis(B[i],W[j]);
	for(reg int i=1;i<=n;++i)
		for(reg int j=1;j<=n;++j)
			Add_Tube(i,j+n,1,Dis[i][j]);
	dinic(s,t);
	for(reg int i=1;i<=n;++i)
		for(reg int j=head[i];j;j=Next[j]){
			reg int v=to[j];
			if(n<v&&v<=2*n&&!w[j]){
				printf("%d\n",v-n);
				break;
			}
		}
	return 0;
}