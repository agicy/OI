#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
#define INF 0X3F3F3F3F
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

const int MAXM=30+5;
const int MAXN=30+5;
const int MAXV=MAXM*MAXN*2;
const int MAXE=(MAXM*MAXN*(1+4)+(MAXN+MAXM)*2)*2;

int m,n;
int a[MAXM][MAXN];
int id[MAXM][MAXN];

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

inline bool check(reg int x,reg int y){
	return 1<=x&&x<=m&&1<=y&&y<=n&&a[x][y]!=-1;
}

int dep[MAXV];
queue<int> Q;

inline bool BFS(int s,reg int t){
	memset(dep,-1,sizeof(dep));
	while(!Q.empty())Q.pop();
	dep[s]=1,Q.push(s);
	while(!Q.empty()){
		reg int u=Q.front();
		Q.pop();
		for(reg int i=head[u];i;i=Next[i]){
			int v=to[i];
			if(dep[v]==-1&&w[i]>0){
				dep[v]=dep[u]+1;
				Q.push(v);
			}
		}
	}
	return dep[t]!=-1;
}

int cur[MAXV];

inline int DFS(reg int u,reg int t,reg int lim){
	if(u==t)
		return lim;
	reg int flow=0;
	for(reg int &i=cur[u];i;i=Next[i]){
		reg int v=to[i];
		if(dep[v]==dep[u]+1&&w[i]>0){
			reg int f=DFS(v,t,min(lim-flow,w[i]));
			if(f){
				flow+=f;
				w[i]-=f;
				w[i^1]+=f;
				if(flow==lim)
					break;
			}
		}
	}
	return flow;
}

inline int Dinic(reg int s,reg int t){
	reg int res=0;
	while(BFS(s,t)){
		memcpy(cur,head,sizeof(head));
		res+=DFS(s,t,INF);
	}
	return res;
}

int main(void){
	m=read(),n=read();
	reg int mn=m*n;
	reg int s=0,t=2*mn+1;
	reg int tot=0;
	for(reg int i=1;i<=m;++i)
		for(reg int j=1;j<=n;++j){
			a[i][j]=read();
			id[i][j]=++tot;
			Add_Tube(id[i][j],id[i][j]+mn,a[i][j]);
		}
	for(reg int i=1;i<=m;++i){
		Add_Tube(s,id[i][1],INF);
		Add_Tube(s,id[i][n],INF);
	}
	for(reg int i=2;i<n;++i){
		Add_Tube(s,id[1][i],INF);
		Add_Tube(s,id[m][i],INF);
	}
	for(reg int i=1;i<=m;++i)
		for(reg int j=1;j<=n;++j){
			if(a[i][j]==0)
				Add_Tube(id[i][j],t,INF);
			else if(a[i][j]>0){
				const int dx[]={-1,0,0,1};
				const int dy[]={0,-1,1,0};
				for(reg int k=0;k<4;++k){
					reg int fx=i+dx[k],fy=j+dy[k];
					if(check(fx,fy))
						Add_Tube(id[i][j]+mn,id[fx][fy],INF);
				}
			}
		}
	reg int ans=Dinic(s,t);
	printf("%d\n",ans);
	return 0;
}