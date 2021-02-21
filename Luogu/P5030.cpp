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

const int MAXN=200+5;
const int MAXM=200+5;
const int MAXV=MAXN*MAXM;
const int MAXE=(MAXN*MAXM*8)*2;
const int inf=0x3f3f3f3f;

int n,m,k;
bool del[MAXN][MAXM];
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

inline int getId(reg int i,reg int j){
	return (i-1)*m+j;
}

int main(void){
	n=read(),m=read(),k=read();
	for(reg int i=1;i<=k;++i){
		static int x,y;
		x=read(),y=read();
		del[x][y]=true;
	}
	reg int s=0,t=n*m+1;
	reg int tot=0;
	for(reg int i=1;i<=n;++i)
		for(reg int j=1;j<=m;++j)
			if(!del[i][j]){
				++tot;
				if((i&1)){
					Add_Tube(s,getId(i,j),1);
					const int dx[]={-3,-3,-1,-1,1,1,3,3};
					const int dy[]={-1,1,-3,3,-3,3,-1,1};
					for(reg int k=0;k<8;++k){
						reg int fx=i+dx[k],fy=j+dy[k];
						if(1<=fx&&fx<=n&&1<=fy&&fy<=m&&!del[fx][fy])
							Add_Tube(getId(i,j),getId(fx,fy),inf);
					}
				}
				else
					Add_Tube(getId(i,j),t,1);
			}
	printf("%d\n",tot-dinic(s,t));
	return 0;
}