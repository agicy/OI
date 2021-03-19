#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
#define getchar()(p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++)
static char buf[100000],*p1=buf,*p2=buf;
inline int read(void){
	reg char ch=getchar();
	reg int res=0;
	while(!isdigit(ch))ch=getchar();
	while(isdigit(ch))res=10*res+(ch^'0'),ch=getchar();
	return res;
}

const int MAXN=2e3+5;
const int MAXV=MAXN<<2;
const int MAXE=MAXN<<4;
const int inf=0x3f3f3f3f;

int n,m;
int s,t,id[MAXN][MAXN];
int tot;
int cnt=1,head[MAXV],to[MAXE],w[MAXE],p[MAXE],Next[MAXE];

inline void Add_Edge(reg int u,reg int v,reg int len,reg int val){
	Next[++cnt]=head[u];
	to[cnt]=v,w[cnt]=len,p[cnt]=val;
	head[u]=cnt;
	return;
}

inline void Add_Tube(reg int u,reg int v,reg int len,reg int val){
	if(!u||v==t)
		++tot;
	Add_Edge(u,v,len,val);
	Add_Edge(v,u,0,-val);
	return;
}

inline void Init(void){
	reg bool f=false;
	for(reg int i=1;i<=n;++i,f=!f)
		for(reg int j=1,g=f;j<=m;++j,g=!g){
			reg int S=read();
			reg int cnt=0;
			if(!g){
				for(reg int k=0;k<4;++k)
					if((S>>k)&1)
						++cnt,Add_Tube(s,k+id[i][j],1,0);
			}
			else{
				for(reg int k=0;k<4;++k)
					if((S>>k)&1)
						++cnt,Add_Tube(k+id[i][j],t,1,0);
			}
			if(cnt==1||cnt==3){
				reg int x;
				if(cnt==1){
					for(reg int k=0;k<4;++k)
						if((S>>k)&1){
							x=k;
							break;
						}
				}
				else{
					for(reg int k=0;k<4;++k)
						if(!((S>>k)&1)){
							x=k;
							break;
						}
				}
				reg int y=x^2,v=x+id[i][j];
				for(reg int k=0;k<4;++k)
					if(k!=x)
						(g^(cnt==3))?Add_Tube(k+id[i][j],v,1,1+(k==y)):Add_Tube(v,k+id[i][j],1,1+(k==y));
			}
			else if(cnt==2&&(S!=5&&S!=10)){
				for(reg int k=0;k<4;++k)
					if((S>>k)&1)
						g?Add_Tube((k^2)+id[i][j],k+id[i][j],1,1):Add_Tube(k+id[i][j],(k^2)+id[i][j],1,1);
			}
			if(!g){
				if(i>1)
					Add_Tube(id[i][j],2+id[i-1][j],1,0);
				if(j<m)
					Add_Tube(1+id[i][j],3+id[i][j+1],1,0);
				if(i<n)
					Add_Tube(2+id[i][j],id[i+1][j],1,0);
				if(j>1)
					Add_Tube(3+id[i][j],1+id[i][j-1],1,0);
			}
		}
	return;
}

bool inque[MAXV];
int dis[MAXV];
queue<int> Q;

inline bool spfa(int s,reg int t){
	memset(dis,0x3f,sizeof(dis));
	inque[s]=true,dis[s]=0,Q.push(s);
	while(!Q.empty()){
		reg int u=Q.front();
		Q.pop();
		inque[u]=false;
		for(reg int i=head[u];i;i=Next[i]){
			int v=to[i];
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

bool vis[MAXV];
int cost;
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
		if(dis[v]==dis[u]+p[i]&&w[i]&&!vis[v]){
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
	cost=0;
	while(spfa(s,t)){
		memcpy(cur,head,sizeof(head));
		res+=dfs(s,t,inf);
	}
	return res;
}

int main(void){
	n=read(),m=read();
	t=1;
	for(reg int i=1;i<=n;++i)
		for(reg int j=1;j<=m;++j,t+=4)
			id[i][j]=t;
	Init();
	if(tot&1)
		puts("-1");
	else{
		reg int flow=dinic(s,t);
		printf("%d\n",(flow<<1)==tot?cost:-1);
	}
	return 0;
}