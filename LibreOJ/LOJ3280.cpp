#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++)
static char buf[100000],*p1=buf,*p2=buf;
inline int read(void){
	reg char ch=getchar();
	reg int res=0;
	while(ch<'0'||'9'<ch)ch=getchar();
	while('0'<=ch&&ch<='9')res=10*res+ch-'0',ch=getchar();
	return res;
}

const int MAXN=200000+5;
const int MAXLOG2N=18+1;
const int MAXK=200000+5;

int n,K;
vector<int> V[MAXK];
int tot;

namespace Graph{
	const int MAXV=5e6;
	vector<int> G[MAXV];
	inline void Add_Edge(reg int u,int v){
		G[u].push_back(v);
		return;
	}
	bool vis[MAXV];
	int tim,dfn[MAXV],low[MAXV];
	int top,S[MAXV];
	int Tarjan_cnt,color[MAXV];
	inline void Tarjan(reg int ID){
		vis[ID]=true;
		dfn[ID]=low[ID]=++tim;
		S[++top]=ID;
		for(reg int i=0,size=G[ID].size();i<size;++i){
			reg int to=G[ID][i];
			if(!dfn[to]){
				Tarjan(to);
				low[ID]=min(low[ID],low[to]);
			}
			else if(vis[to])
				low[ID]=min(low[ID],dfn[to]);
		}
		if(dfn[ID]==low[ID]){
			reg int To;
			++Tarjan_cnt;
			do{
				To=S[top--];
				vis[To]=false;
				color[To]=Tarjan_cnt;
			}while(To!=ID);
		}
		return;
	}
	bool out[MAXV];
	int size[MAXV];
	inline void Solve(void){
		for(reg int i=1;i<=tot;++i)
			if(!dfn[i])
				Tarjan(i);
		for(reg int i=1;i<=tot;++i)
			if(!out[color[i]])
				for(reg int j=0,size=G[i].size();j<size;++j)
					if(color[i]!=color[G[i][j]]){
						out[color[i]]=true;
						break;
					}
		for(reg int i=1;i<=K;++i)
			++size[color[i]];
		int ans=K-1;
		for(reg int i=1;i<=Tarjan_cnt;++i)
			if(!out[i])
				ans=min(ans,size[i]-1);
		printf("%d\n",ans);
		return;
	}
}

namespace Tree{
	vector<int> T[MAXN];
	inline void Add_Edge(reg int u,int v){
		T[u].push_back(v);
		return;
	}
	int fa[MAXN][MAXLOG2N],dep[MAXN];
	int tim,dfn[MAXN];
	int pos[MAXN][MAXLOG2N];
	inline void DFS(reg int ID,reg int father){
		dfn[ID]=++tim;
		fa[ID][0]=father;
		pos[ID][0]=++tot;
		dep[ID]=dep[father]+1;
		for(reg int i=1;(1<<i)<=dep[ID];++i){
			fa[ID][i]=fa[fa[ID][i-1]][i-1];
			pos[ID][i]=++tot;
			Graph::Add_Edge(pos[ID][i],pos[ID][i-1]);
			Graph::Add_Edge(pos[ID][i],pos[fa[ID][i-1]][i-1]);
		}
		for(reg int i=0,size=T[ID].size();i<size;++i){
			reg int to=T[ID][i];
			if(to!=father)
				DFS(to,ID);
		}
		return;
	}
	inline int LCA(int x,int y){
		if(dep[x]>dep[y])
			swap(x,y);
		for(reg int i=MAXLOG2N-1;i>=0;--i)
			if(dep[fa[y][i]]>=dep[x])
				y=fa[y][i];
		if(x==y)
			return x;
		for(reg int i=MAXLOG2N-1;i>=0;--i)
			if(fa[x][i]!=fa[y][i])
				x=fa[x][i],y=fa[y][i];
		return fa[x][0];
	}
	inline void Add_Edge(reg int id,reg int x,reg int y){
		reg int lca=LCA(x,y);
		for(reg int i=MAXLOG2N-1;i>=0;--i){
			if(dep[fa[x][i]]>=dep[lca]){
				Graph::Add_Edge(id,pos[x][i]);
				x=fa[x][i];
			}
			if(dep[fa[y][i]]>=dep[lca]){
				Graph::Add_Edge(id,pos[y][i]);
				y=fa[y][i];
			}
		}
		Graph::Add_Edge(id,pos[lca][0]);
		return;
	}
	inline bool cmp(reg int a,reg int b){
		return dfn[a]<dfn[b];
	}
	inline void Solve(reg int id){
		if(V[id].size()){
			sort(V[id].begin(),V[id].end(),cmp);
			V[id].push_back(V[id][0]);
			for(reg int i=1,size=V[id].size();i<size;++i)
				Add_Edge(id,V[id][i-1],V[id][i]);
		}
		return;
	}
}

int main(void){
	n=read(),K=read();
	for(reg int i=1;i<n;++i){
		static int a,b;
		a=read(),b=read();
		Tree::Add_Edge(a,b);
		Tree::Add_Edge(b,a);
	}
	tot=K;
	Tree::DFS(1,0);
	for(int i=1;i<=n;++i){
		static int c;
		c=read();
		V[c].push_back(i);
		Graph::Add_Edge(Tree::pos[i][0],c);
	}
	for(reg int i=1;i<=K;++i)
		Tree::Solve(i);
	Graph::Solve();
	return 0;
}