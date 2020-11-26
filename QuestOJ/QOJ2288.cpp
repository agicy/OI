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

inline void cMax(reg int &a,reg int b){
	if(a<b)
		a=b;
	return;
}

const int MAXN=50+5;
const int MAXM=50+5;
const int MAXV=1e5+5;
const int MAXE=3e5+5;
const int inf=0x3f3f3f3f;

int n,m;
int M[MAXN][MAXM];
int id[MAXN][MAXM];
int cnt=1,head[MAXV],to[MAXE],w[MAXE],p[MAXE],Next[MAXE];

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
queue<int> Q;

inline bool bfs(int s,reg int t){
	memset(dep,-1,sizeof(dep));
	dep[s]=1,Q.push(s);
	while(!Q.empty()){
		reg int u=Q.front();
		Q.pop();
		for(reg int i=head[u];i;i=Next[i]){
			int v=to[i];
			if(dep[v]==-1&&w[i]){
				dep[v]=dep[u]+1;
				Q.push(v);
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

int main(void){
	n=read(),m=read();
	reg int tot=0;
	for(reg int i=1;i<=n;++i)
		for(reg int j=1;j<=m;++j){
			M[i][j]=read();
			id[i][j]=++tot;
		}
	reg int nm=n*m;
	reg int s=0,t=2*nm+1;
	reg int ans=0;
	for(reg int i=1;i<=n;++i)
		for(reg int j=1;j<=m;++j){
			int Max=0;
			if(M[i][j]<0){
				switch(M[i][j]){
					case -1:{
						Add_Tube(s,id[i][j],inf);
						for(reg int k=i;k>=1;--k)
							cMax(Max,M[k][j]);
						for(reg int k=i;k>=1;--k)
							Add_Tube(id[k][j],id[k-1][j],Max-max(M[k][j],0));
						break;
					}
					case -2:{
						Add_Tube(s,id[i][j],inf);
						for(reg int k=i;k<=n;++k)
							cMax(Max,M[k][j]);
						for(reg int k=i;k<n;++k)
							Add_Tube(id[k][j],id[k+1][j],Max-max(M[k][j],0));
						break;
					}
					case -3:{
						Add_Tube(id[i][j]+nm,t,inf);
						for(reg int k=j;k>=1;--k)
							cMax(Max,M[i][k]);
						for(reg int k=j;k>=2;--k)
							Add_Tube(id[i][k-1]+nm,id[i][k]+nm,Max-max(M[i][k],0));
						break;
					}
					case -4:{
						Add_Tube(id[i][j]+nm,t,inf);
						for(reg int k=j;k<=m;++k)
							cMax(Max,M[i][k]);
						for(reg int k=j;k<m;++k)
							Add_Tube(id[i][k+1]+nm,id[i][k]+nm,Max-max(M[i][k],0));
						break;
					}
				}
			}
			ans+=Max;
			Add_Tube(id[i][j],id[i][j]+nm,inf);
		}
	printf("%d\n",ans-dinic(s,t));
	return 0;
}