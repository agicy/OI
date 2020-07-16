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

const int MAXN=300000+5;
const int MAXLOG2N=19+1;
const int MAXM=300000+5;

int n;

namespace Tree{
	int cnt,head[MAXN],to[MAXN<<1],Next[MAXN<<1];
	inline void Add_Edge(reg int u,reg int v){
		Next[++cnt]=head[u];
		to[cnt]=v;
		head[u]=cnt;
		return;
	}
	int fa[MAXN][MAXLOG2N],dep[MAXN];
	int size[MAXN];
	int tim,dfn[MAXN];
	inline void DFS(reg int u,reg int father){
		size[u]=1;
		dfn[u]=++tim;
		fa[u][0]=father;
		dep[u]=dep[father]+1;
		for(reg int i=1;i<MAXLOG2N;++i){
			fa[u][i]=fa[fa[u][i-1]][i-1];
			if(!fa[u][i])
				break;
		}
		for(reg int i=head[u];i;i=Next[i]){
			reg int v=to[i];
			if(v!=father){
				DFS(v,u);
				size[u]+=size[v];
			}
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
}


int h[MAXN],tmp[MAXN];

inline bool cmp(reg int a,reg int b){
	return Tree::dfn[a]<Tree::dfn[b];
}

bool key[MAXN];
int ans[MAXN];

namespace Vitrual_Tree{ 
	int cnt,head[MAXN],to[MAXN<<1],Next[MAXN<<1];
	inline void Add_Edge(reg int u,reg int v){
		Next[++cnt]=head[u];
		to[cnt]=v;
		head[u]=cnt;
		return;
	}
	pair<int,int> g[MAXN];
	inline void DFS1(reg int u){
		if(key[u])
			g[u]=make_pair(0,u);
		else
			g[u]=make_pair(INF,0);
		for(reg int i=head[u];i;i=Next[i]){
			reg int v=to[i];
			using namespace Tree;
			DFS1(v);
			g[u]=min(g[u],make_pair(g[v].first+dep[v]-dep[u],g[v].second));
		}
		return;
	}
	inline void DFS2(reg int u,pair<int,int> P){
		if(P<g[u])
			g[u]=P;
		else
			P=g[u];
		for(reg int i=head[u];i;i=Next[i]){
			reg int v=to[i];
			using namespace Tree;
			DFS2(v,make_pair(P.first+dep[v]-dep[u],P.second));
		}
		return;
	}
	int id[MAXN],up[MAXN];
	inline void DFS3(reg int u){
		id[u]=g[u].second;
		ans[id[u]]+=Tree::size[u];
		for(reg int i=head[u];i;i=Next[i]){
			reg int v=to[i];
			using namespace Tree;
			reg int tmp=v;
			for(reg int j=MAXLOG2N-1;j>=0;--j)
				if(fa[tmp][j]&&dep[fa[tmp][j]]>dep[u])
					tmp=fa[tmp][j];
			ans[id[u]]-=size[up[v]=tmp];
			DFS3(v);
		}
		return;
	}
	inline void DFS4(reg int u){
		for(reg int i=head[u];i;i=Next[i]){
			reg int v=to[i];
			using namespace Tree;
			reg int x=up[v],y=v,h;
			if(id[u]==id[v])
				ans[id[u]]+=size[x]-size[v];
			else{
				h=dep[id[v]]+dep[u]-g[u].first;
				h=(h&1)?((h+1)>>1):(id[v]<id[u]?(h>>1):((h>>1)+1));
				for(reg int j=MAXLOG2N-1;j>=0;--j)
					if(fa[y][j]&&dep[fa[y][j]]>=h)
						y=fa[y][j];
				ans[id[v]]+=size[y]-size[v];
				ans[id[u]]+=size[x]-size[y];
			}
			DFS4(v);
		}
		return;
	}
	inline void Init(reg int u){
		id[u]=up[u]=0;
		for(reg int i=head[u];i;i=Next[i])
			Init(to[i]);
		head[u]=0;
		return;
	}
}

int main(void){
	n=read();
	for(reg int i=1;i<n;++i){
		static int x,y;
		x=read(),y=read();
		Tree::Add_Edge(x,y);
		Tree::Add_Edge(y,x);
	}
	Tree::DFS(1,0);
	reg int q=read();
	while(q--){
		static int m;
		m=read();
		for(reg int i=1;i<=m;++i){
			h[i]=read();
			tmp[i]=h[i];
			key[h[i]]=true;
		}
		sort(tmp+1,tmp+m+1,cmp);
		static int S[MAXM];
		reg int top;
		S[top=1]=tmp[1];
		using namespace Tree;
		using namespace Vitrual_Tree;
		for(reg int i=2;i<=m;++i){
			reg int x=tmp[i],y=LCA(x,S[top]);
			while(top>1&&dep[y]<=dep[S[top-1]])
				Vitrual_Tree::Add_Edge(S[top-1],S[top]),--top;
			if(S[top]!=y)
				Vitrual_Tree::Add_Edge(y,S[top]),S[top]=y;
			S[++top]=x;
		}
		while(top>1)
			Vitrual_Tree::Add_Edge(S[top-1],S[top]),--top;
		reg int root=S[1];
		DFS1(root);
		DFS2(root,g[root]);
		DFS3(root);
		DFS4(root);
		ans[id[root]]+=size[1]-size[root];
		for(reg int i=1;i<=m;++i)
			printf("%d%c",ans[h[i]],i==m?'\n':' ');
		Init(root);
		Vitrual_Tree::cnt=0;
		for(reg int i=1;i<=m;++i){
			key[h[i]]=false;
			ans[h[i]]=0;
		}
	}
	return 0;
}
