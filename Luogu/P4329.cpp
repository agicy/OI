#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++)
static char buf[1<<21],*p1=buf,*p2=buf;
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
	if(x<0) x=-x,putchar('-');
	if(x==0) putchar('0');
	else while(x) buf[++p]=(x%10)^'0',x/=10;
	while(~p) putchar(buf[p--]);
	putchar('\n');
	return;
}

const int MAXN=20+5;
const int MAXV=2*MAXN;
const int MAXE=(2*MAXN+MAXN*MAXN)*2;
const double inf=1.0/0.0;
const double eps=1e-6;

int n;
int cnt=1,head[MAXV],to[MAXE],w[MAXE],Next[MAXE];
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
double dis[MAXV];
queue<int> Q;

inline bool spfa(reg int s,reg int t){
	fill(dis+s,dis+t+1,inf);
	inque[s]=true,dis[s]=0,Q.push(s);
	while(!Q.empty()){
		reg int u=Q.front();
		Q.pop();
		inque[u]=false;
		for(reg int i=head[u];i;i=Next[i]){
			reg int v=to[i];
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

double cost;
bool vis[MAXV];
int cur[MAXV];

inline int dfs(reg int u,reg int t,reg int lim){
	if(u==t){
		cost+=dis[t]*lim;
		return lim;
	}
	vis[u]=true;
	reg int flow=0;
	for(reg int &i=cur[u];i;i=Next[i]){
		reg int v=to[i];
		if(fabs(dis[u]+p[i]-dis[v])<eps&&w[i]&&!vis[v]){
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

inline int dinic(reg int s,reg int t){
	reg int res=0;
	while(spfa(s,t)){
		memcpy(cur,head,sizeof(head));
		res+=dfs(s,t,0x3f3f3f3f);
	}
	return res;
}

int main(void){
	n=read();
	reg int s=0,t=n*2+1;
	for(reg int i=1;i<=n;++i){
		for(reg int j=1;j<=n;++j){
			static int p;
			p=read();
			Add_Tube(i,j+n,1,-log(p/100.0));
		}
		Add_Tube(s,i,1,0),Add_Tube(i+n,t,1,0);
	}
	reg int flow=dinic(s,t);
	reg double ans=-cost;
	printf("%lf\n",exp(ans)*100*(flow==n));
	return 0;
}