#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;

const int MAXN=50+5;
const int MAXM=MAXN*(MAXN-1)/2;
const int MAXV=2*MAXN;
const int MAXE=1e4+5;
const int inf=0x3f3f3f3f;

int n,m;
int cnt,head[MAXV],to[MAXE],w[MAXE],Next[MAXE];
int W[MAXE];

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
				w[i]-=f;
				w[i^1]+=f;
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
	while(scanf("%d%d",&n,&m)==2){
		cnt=1,memset(head,0,sizeof(head));
		for(reg int i=1;i<=n;++i)
			Add_Tube(i,i+n,1);
		for(reg int i=1;i<=m;++i){
			static char ch;
			static int x,y;
			cin>>ch,scanf("%d,%d",&x,&y),cin>>ch;
			++x,++y;
			Add_Tube(x+n,y,inf);
			Add_Tube(y+n,x,inf);
		}
		memcpy(W,w,sizeof(w));
		int ans=n;
		for(reg int s=n+1;s<=2*n;++s)
			for(reg int t=s-n+1;t<=n;++t){
				memcpy(w,W,sizeof(W));
				ans=min(ans,dinic(s,t));
			}
		printf("%d\n",ans);
	}
	return 0;
}