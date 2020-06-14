#include<bits/stdc++.h>
using namespace std;
#define reg register

const int MAXN=5000+5;
const int MAXM=500000+5;

struct Edge{
	int u,v;
	inline Edge(reg int u=0,reg int v=0):u(u),v(v){
		return;
	}
};

int n,m,q;
int c[MAXN];
Edge S[MAXM],D[MAXM];

namespace Kruskal{
	namespace Graph{
		int color[MAXN];
		int cnt,head[MAXN],to[MAXM<<1],Next[MAXM<<1];
		inline void Init(void){
			cnt=0;
			memset(head,0,sizeof(head));
			memset(color,0,sizeof(color));
			return;
		}
		inline void Add_Edge(reg int u,reg int v){
			Next[++cnt]=head[u];
			to[cnt]=v;
			head[u]=cnt;
		}
		inline void Add_Tube(reg int u,reg int v){
			Add_Edge(u,v);
			Add_Edge(v,u);
			return;
		}
		inline bool check(reg int ID,reg int col){
			if(color[ID])
				return color[ID]==col;
			color[ID]=col;
			for(reg int i=head[ID];i;i=Next[i])
				if(!check(to[i],col^1))
					return false;
			return true;
		}
	}
	namespace UnionFind{
		int ID[MAXN];
		inline void Init(reg int size){
			for(reg int i=1;i<=size;++i)
				ID[i]=i;
			return;
		}
		inline int find(reg int x){
			if(x==ID[x])
				return x;
			else
				return ID[x]=find(ID[x]);
		}
		inline void merge(reg int a,reg int b){
			reg int ra=find(a),rb=find(b);
			if(ra!=rb)
				ID[rb]=ra;
			return;
		}
		inline bool search(reg int a,reg int b){
			return find(a)==find(b);
		}
	}
	namespace G{
		int cnt,head[MAXN],to[MAXM<<1],Next[MAXM<<1];
		inline void Init(void){
			cnt=0;
			memset(head,0,sizeof(head));
			return;
		}
		inline void Add_Edge(reg int u,reg int v){
			Next[++cnt]=head[u];
			to[cnt]=v;
			head[u]=cnt;
		}
		inline void Add_Tube(reg int u,reg int v){
			Add_Edge(u,v);
			Add_Edge(v,u);
			return;
		}
	}
	using UnionFind::find;
	using UnionFind::merge;
	using UnionFind::search;
	using namespace G;
	inline void Init(reg int n){
		Graph::Init();
		UnionFind::Init(n);
		return;
	}
	inline void Kruskal(const Edge S[],reg int cntS){
		Init(n);
		for(reg int i=1;i<=cntS;++i)
			Graph::Add_Tube(S[i].u,S[i].v);
		reg int cnt=0;
		for(reg int i=1;i<=cntS&&cnt<n-1;++i)
			if(!search(S[i].u,S[i].v)){
				++cnt;
				merge(S[i].u,S[i].v);
				Add_Tube(S[i].u,S[i].v);
			}
		for(reg int i=1;i<=n;++i)
			if(!Graph::color[i])
				if(!Graph::check(i,2))
					Add_Edge(i,i);
	}
	bool vis[MAXN][MAXN],f[MAXN][MAXN];
	int Q1[MAXN*MAXN],Q2[MAXN*MAXN];
	inline void dp(void){
		reg int head1=0,tail1=0,head2=0,tail2=0;
		for(reg int i=1;i<=n;++i){
			vis[i][i]=f[i][i]=true;
			Q1[tail1++]=Q2[tail2++]=i;
			for(reg int j=head[i];j;j=Next[j]){
				vis[i][to[j]]=vis[to[j]][i]=true;
				if(c[i]!=c[to[j]])
					continue;
				f[i][to[j]]=f[to[j]][i]=true;
				Q1[tail1++]=i,Q2[tail2++]=to[j];
			}
		}
		while(head1<tail2){
			reg int x=Q1[head1++],y=Q2[head2++];
			for(reg int i=head[x];i;i=Next[i])
				for(reg int j=head[y];j;j=Next[j]){
					if(!vis[to[i]][to[j]]&&c[to[i]]==c[to[j]]){
						f[to[i]][to[j]]=f[to[j]][to[i]]=true;
						Q1[tail1++]=to[i],Q2[tail2++]=to[j];
					}
					vis[to[i]][to[j]]=vis[to[j]][to[i]]=true;
				}
		}
		return;
	}
}

int main(void){
	scanf("%d%d%d",&n,&m,&q);
	for(reg int i=1;i<=n;++i)
		scanf("%1d",&c[i]);
	reg int cntS=0,cntD=0;
	for(reg int i=1;i<=m;++i){
		static int u,v;
		scanf("%d%d",&u,&v);
		Kruskal::Graph::Add_Tube(u,v);
		if(c[u]!=c[v])
			D[++cntD]=Edge(u,v);
		else
			S[++cntS]=Edge(u,v);
	}
	Kruskal::Kruskal(S,cntS),Kruskal::Kruskal(D,cntD);
	Kruskal::dp();
	for(reg int i=1;i<=q;++i){
		static int u,v;
		scanf("%d%d",&u,&v);
		puts(Kruskal::f[u][v]?"YES":"NO");
	}
	return 0;
}