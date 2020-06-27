#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
#define INF 0X3F3F3F3F
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++)
static char buf[100000],*p1=buf,*p2=buf;
inline int read(void){
	reg char ch=getchar();
	reg int res=0;
	while(ch<'0'||'9'<ch)ch=getchar();
	while('0'<=ch&&ch<='9')res=10*res+ch-'0',ch=getchar();
	return res;
}

const int MAXN=200+5;
const int MAXM=1000+5;

int n,m;

namespace Graph{
	int cnt=1,head[MAXN],to[MAXM<<1],w[MAXM<<1],Next[MAXM<<1];
	inline void Add_Edge(reg int u,reg int v,reg int len){
		Next[++cnt]=head[u];
		to[cnt]=v;
		w[cnt]=len;
		head[u]=cnt;
		return;
	}
	inline void Add_Tube(reg int u,reg int v,reg int len){
		Add_Edge(u,v,len);
		Add_Edge(v,u,len);
		return;
	}
	int dep[MAXN];
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
	int cur[MAXN];
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
	bool vis[MAXN];
	inline void DFS(reg int ID){
		vis[ID]=true;
		for(reg int i=head[ID];i;i=Next[i])
			if(!vis[to[i]]&&w[i]>0)
				DFS(to[i]);
		return;
	}
}

int res[MAXN],tot;

namespace Tree{
	int cnt=1,head[MAXN],to[MAXN<<1],w[MAXN<<1],Next[MAXN<<1];
	inline void Add_Edge(reg int u,reg int v,reg int len){
		Next[++cnt]=head[u];
		to[cnt]=v;
		w[cnt]=len;
		head[u]=cnt;
		return;
	}
	inline void Add_Tube(reg int u,reg int v,reg int len){
		Add_Edge(u,v,len);
		Add_Edge(v,u,len);
		return;
	}
	int d;
	int id,x,y;
	bool vis[MAXN<<1];
	inline bool DFS(reg int ID,reg int father){
		reg bool flag=false;
		for(reg int i=head[ID];i;i=Next[i])
			if(to[i]!=father&&!vis[i]){
				if(w[i]<d){
					id=i;
					x=ID;
					y=to[i];
					d=w[i];
				}
				DFS(to[i],ID);
				flag=true;
			}
		return flag;
	}
	inline void Solve(reg int ID){
		d=INF;
		if(!DFS(ID,0)){
			res[++tot]=ID;
			return;
		}
		vis[id]=vis[id^1]=true;
		reg int p=x,q=y;
		Solve(p),Solve(q);
		return;
	}
}

int W[MAXM<<1];

int main(void){
	n=read(),m=read();
	for(reg int i=1;i<=m;++i){
		static int u,v,w;
		u=read(),v=read(),w=read();
		Graph::Add_Tube(u,v,w);
	}
	static int fa[MAXN];
	for(reg int i=2;i<=n;++i)
		fa[i]=1;
	for(reg int i=1;i<=Graph::cnt;++i)
		W[i]=Graph::w[i];
	reg int ans=0;
	for(reg int i=2;i<=n;++i){
		for(reg int j=1;j<=Graph::cnt;++j)
			Graph::w[j]=W[j];
		reg int s=fa[i],t=i;
		reg int res=Graph::Dinic(s,t);
		ans+=res;
		Tree::Add_Tube(s,t,res);
		memset(Graph::vis,false,sizeof(Graph::vis));
		Graph::DFS(s);
		for(reg int j=i+1;j<=n;++j)
			if(!Graph::vis[j]&&fa[j]==s)
				fa[j]=t;
	}
	printf("%d\n",ans);
	Tree::Solve(1);
	for(reg int i=1;i<=tot;++i)
		printf("%d%c",res[i],i==n?'\n':' ');
	return 0;
}