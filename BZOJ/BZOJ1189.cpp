#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++)
static char buf[100000],*p1=buf,*p2=buf;
inline int read(void){
	reg char ch=getchar();
	reg int res=0;
	while(!isdigit(ch))ch=getchar();
	while(isdigit(ch))res=10*res+(ch^'0'),ch=getchar();
	return res;
}

inline void read(reg char *s){
	*s=getchar();
	while(*s!='X'&&*s!='.'&&*s!='D')*s=getchar();
	while(*s=='X'||*s=='.'||*s=='D')*(++s)=getchar();
	*s='\0';
	return;
}

const int MAXN=20+5;
const int MAXM=20+5;
const int MAXV=1e4;
const int MAXE=2e5;
const int inf=0x3f3f3f3f;

int n,m;
char M[MAXN][MAXM];
int cnt=1,head[MAXV],to[MAXE],w[MAXE],Next[MAXE];

inline void Add_Edge(reg int u,reg int v,reg int len){
	Next[++cnt]=head[u];
	to[cnt]=v;
	w[cnt]=len;
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
	reg int head_=0,tail_=0;
	memset(dep,-1,sizeof(dep));
	dep[s]=1,Q[tail_++]=s;
	while(head_<tail_){
		reg int u=Q[head_++];
		for(reg int i=head[u];i;i=Next[i]){
			reg int v=to[i];
			if(dep[v]==-1&&w[i]){
				dep[v]=dep[u]+1;
				Q[tail_++]=v;
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

inline int getId(reg int i,reg int j){
	return (i-1)*m+j;
}

struct doors{
	int x,y,id;
	inline doors(reg int x=0,reg int y=0):x(x),y(y){
		id=getId(x,y);
		return;
	}
};

doors d[MAXN*MAXM];

struct Node{
	int x,y;
	inline Node(reg int x=0,reg int y=0):x(x),y(y){
		return;
	}
};

bool vis[MAXN*MAXM];
int dis[MAXN*MAXM][MAXN*MAXM];

inline void getDis(reg int sx,reg int sy,reg int dis[]){
	memset(vis,false,sizeof(vis));
	queue<Node> Q;
	vis[getId(sx,sy)]=true,dis[getId(sx,sy)]=0,Q.push(Node(sx,sy));
	while(!Q.empty()){
		static Node s;
		s=Q.front();
		Q.pop();
		reg int x=s.x,y=s.y;
		const int dx[]={-1,0,0,1};
		const int dy[]={0,-1,1,0};
		for(reg int i=0;i<4;++i){
			reg int fx=x+dx[i],fy=y+dy[i];
			if(1<=fx&&fx<=n&&1<=fy&&fy<=m){
				if(!vis[getId(fx,fy)]&&M[fx][fy]!='X'&&M[fx][fy]!='D'){
					vis[getId(fx,fy)]=true;
					dis[getId(fx,fy)]=dis[getId(x,y)]+1;
					Q.push(Node(fx,fy));
				}
			}
		}
	}
	return;
}

int main(void){
	n=read(),m=read();
	for(reg int i=1;i<=n;++i)
		read(M[i]+1);
	reg int sum=0;
	reg int s=0,t=n*m+1;
	reg int tot=0;
	for(reg int i=1;i<=n;++i)
		for(reg int j=1;j<=m;++j)
			switch(M[i][j]){
				case '.':{
					++sum;
					Add_Tube(s,getId(i,j),1);
					break;
				}
				case 'D':{
					d[++tot]=doors(i,j);
					break;
				}
			}
	memset(dis,0x3f,sizeof(dis));
	for(reg int i=1;i<=tot;++i)
		getDis(d[i].x,d[i].y,dis[i]);
	reg int vt=t;
	reg bool flag=false;
	for(reg int T=0,flow=0;T<=1e3;){
		flow+=dinic(s,t);
		if(flow==sum){
			flag=true;
			printf("%d\n",T);
			break;
		}
		++T;
		for(reg int k=1;k<=tot;++k){
			Add_Tube(++vt,t,1);
			for(reg int i=1;i<=n;++i)
				for(reg int j=1;j<=m;++j)
					if(M[i][j]=='.'&&dis[k][getId(i,j)]<=T)
						Add_Tube(getId(i,j),vt,1);
		}
	}
	if(!flag)
		puts("impossible");
	return 0;
}