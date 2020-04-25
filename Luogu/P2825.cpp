#include<bits/stdc++.h>
using namespace std;
#define reg register
#define INF 0X3F3F3F3F

const int MAXN=50+5;
const int MAXM=50+5;

inline void Read(void);
inline void Work(void);

int main(void){
	Read();
	Work();
	return 0;
}

int n,m;
char M[MAXN][MAXM];

inline void Read(void){
	scanf("%d%d",&n,&m);
	for(reg int i=1;i<=n;++i)
		scanf("%s",M[i]+1);
	return;
}

int cnt=1,head[MAXN*MAXM],to[(MAXN*MAXM*3)<<1],w[(MAXN*MAXM*3)<<1],Next[(MAXN*MAXM*3)<<1];

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

int dep[MAXN*MAXM];
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

int cur[MAXN*MAXM];

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

bool vis[MAXN*MAXM];
int row[MAXN][MAXM];
int col[MAXN][MAXM];

inline void Work(void){
	for(reg int i=1;i<=n;++i)
		M[i][0]=M[i][m+1]='#';
	for(reg int i=1;i<=m;++i)
		M[0][i]=M[n+1][i]='#';
	reg int s=0,t=1;
	reg int tot=3;
	for(reg int i=1;i<=n;++i)
		for(reg int j=1;j<=m;++j){
			if(M[i][j]=='#')
				continue;
			if(M[i][j-1]=='#')
				++tot;
			row[i][j]=tot;
			if(!vis[tot]){
				vis[tot]=true;
				Add_Tube(s,tot,1);
			}
		}
	for(reg int i=1;i<=m;++i)
		for(reg int j=1;j<=n;++j){
			if(M[j][i]=='#')
				continue;
			if(M[j-1][i]=='#')
				++tot;
			col[j][i]=tot;
			if(!vis[tot]){
				vis[tot]=true;
				Add_Tube(tot,t,1);
			}
		}
	for(reg int i=1;i<=n;++i)
		for(reg int j=1;j<=m;++j)
			if(M[i][j]=='*')
				Add_Tube(row[i][j],col[i][j],1);
	reg int ans=Dinic(s,t);
	printf("%d\n",ans);
	return;
}
