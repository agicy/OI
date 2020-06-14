#include<bits/stdc++.h>
using namespace std;
#define reg register
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

const int MAXN=100+5;
const int MAXM=100+5;
const int MAXV=MAXN*MAXM*2;
const int MAXE=MAXN*MAXM*14;

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
queue<int> Q;

inline bool BFS(int s,reg int t){
	memset(dep,-1,sizeof(dep));
	while(!Q.empty())Q.pop();
	dep[s]=1,Q.push(s);
	while(!Q.empty()){
		reg int ID=Q.front();
		Q.pop();
		for(reg int i=head[ID];i;i=Next[i])
			if(dep[to[i]]==-1&&w[i]>0){
				dep[to[i]]=dep[ID]+1;
				Q.push(to[i]);
			}
	}
	return dep[t]!=-1;
}

int cur[MAXV];

inline int DFS(reg int ID,reg int t,reg int lim){
	if(ID==t)
		return lim;
	reg int flow=0;
	for(reg int &i=cur[ID];i;i=Next[i])
		if(dep[to[i]]==dep[ID]+1&&w[i]>0){
			reg int f=DFS(to[i],t,min(lim-flow,w[i]));
			if(f){
				flow+=f;
				w[i]-=f;
				w[i^1]+=f;
				if(flow==lim)
					break;
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

int n,m;
int a[MAXN][MAXM],b[MAXN][MAXM],c[MAXN][MAXM];

inline int GetID(reg int i,reg int j){
	return (i-1)*m+j;
}

inline bool check(reg int x,reg int y){
	return 1<=x&&x<=n&&1<=y&&y<=m;
}

const int dx[]={-1,0,0,1},dy[]={0,-1,1,0};

int main(void){
	n=read(),m=read();
	reg int V=n*m;
	reg int s=0,t=2*V+1;
	for(reg int i=1;i<=n;++i)
		for(reg int j=1;j<=m;++j)
			a[i][j]=read();
	for(reg int i=1;i<=n;++i)
		for(reg int j=1;j<=m;++j)
			b[i][j]=read();
	for(reg int i=1;i<=n;++i)
		for(reg int j=1;j<=m;++j)
			c[i][j]=read();
	reg int ans=0;
	for(reg int i=1;i<=n;++i)
		for(reg int j=1;j<=m;++j){
			ans+=a[i][j]+b[i][j]+1e4;
			if((i+j)&1){
				Add_Tube(s,GetID(i,j),a[i][j]+1e4);
				Add_Tube(GetID(i,j)+V,t,b[i][j]+1e4);
				Add_Tube(GetID(i,j),GetID(i,j)+V,INF);
			}
			else{
				Add_Tube(s,GetID(i,j)+V,b[i][j]+1e4);
				Add_Tube(GetID(i,j),t,a[i][j]+1e4);
				Add_Tube(GetID(i,j)+V,GetID(i,j),INF);
			}
			for(reg int k=0;k<4;++k){
				reg int fx=i+dx[k],fy=j+dy[k];
				if(check(fx,fy)){
					ans+=c[i][j];
					Add_Tube(GetID(i,j)+V,GetID(fx,fy)+V,c[i][j]+c[fx][fy]);
				}
			}
		}
	printf("%d\n",ans-Dinic(s,t));
	return 0;
}