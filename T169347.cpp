#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++)
static char buf[100000],*p1=buf,*p2=buf;
inline int read(void){
	reg char ch=getchar();
	reg int res=0;
	while(!isdigit(ch))ch=getchar();
	while(isdigit(ch))res=10*res+(ch^'0'),ch=getchar();
	return res;
}

const int MAXN=3e5+5;
const int MAXM=6e5+5;

int n,m,C;
int deg[MAXN];
int cnt,head[MAXN],to[MAXN<<1],Next[MAXN<<1];
int l[MAXM],r[MAXM];

inline void Add_Edge(reg int u,reg int v){
	Next[++cnt]=head[u];
	to[cnt]=v;
	head[u]=cnt;
	return;
}

namespace Subtask1{
	const int MAXN=100+5;
	const int MAXLOG2N=7+1;
	int fa[MAXN][MAXLOG2N],dep[MAXN];
	inline void dfs(reg int u,reg int father){
		fa[u][0]=father;
		dep[u]=dep[father]+1;
		for(reg int i=1;i<MAXLOG2N;++i)
			fa[u][i]=fa[fa[u][i-1]][i-1];
		for(reg int i=head[u];i;i=Next[i]){
			reg int v=to[i];
			if(v!=father)
				dfs(v,u);
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
	inline int getDis(reg int x,reg int y){
		reg int lca=LCA(x,y);
		return dep[x]+dep[y]-(dep[lca]<<1);
	}
	namespace UnionFind{
		int fa[MAXN];
		inline void Init(reg int l,reg int r){
			for(reg int i=l;i<=r;++i)
				fa[i]=i;
			return;
		}
		inline int find(reg int x){
			if(x==fa[x])
				return x;
			else
				return fa[x]=find(fa[x]);
		}
		inline void merge(reg int a,reg int b){
			reg int ra=find(a),rb=find(b);
			fa[rb]=ra;
			return;
		}
		inline bool search(reg int a,reg int b){
			return find(a)==find(b);
		}
	}
	inline void Solve(void){
		dfs(1,0);
		for(reg int i=1;i<=m;++i){
			UnionFind::Init(l[i],r[i]);
			reg int ans=r[i]-l[i]+1;
			for(reg int j=l[i];j<=r[i];++j)
				for(reg int k=j+1;k<=r[i];++k)
					if(getDis(j,k)<=C){
						if(!UnionFind::search(j,k)){
							--ans;
							UnionFind::merge(j,k);
						}
					}
			printf("%d\n",ans);
		}
		return;
	}
}

namespace Subtask2{
	inline void Solve(void){
		for(reg int i=1;i<=m;++i)
			puts("1");
		return;
	}
}

namespace Subtask4{
	const int MAXLOG2N=19+1;
	int fa[MAXN][MAXLOG2N],dep[MAXN];
	inline void dfs(reg int u,reg int father){
		fa[u][0]=father;
		dep[u]=dep[father]+1;
		for(reg int i=1;i<MAXLOG2N;++i)
			fa[u][i]=fa[fa[u][i-1]][i-1];
		for(reg int i=head[u];i;i=Next[i]){
			reg int v=to[i];
			if(v!=father)
				dfs(v,u);
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
	inline int getDis(reg int x,reg int y){
		reg int lca=LCA(x,y);
		return dep[x]+dep[y]-(dep[lca]<<1);
	}
	namespace UnionFind{
		int fa[MAXN];
		inline void Init(reg int n){
			for(reg int i=1;i<=n;++i)
				fa[i]=i;
			return;
		}
		inline int find(reg int x){
			if(x==fa[x])
				return x;
			else
				return fa[x]=find(fa[x]);
		}
		inline void merge(reg int a,reg int b){
			reg int ra=find(a),rb=find(b);
			if(ra!=rb)
				fa[rb]=ra;
			return;
		}
		inline bool search(reg int a,reg int b){
			return find(a)==find(b);
		}
	}
	inline void Solve(void){
		dfs(1,0);
		UnionFind::Init(n);
		reg int ans=0;
		for(reg int i=1;i<=m;++i){
			++ans;
			for(reg int j=head[i];j;j=Next[j]){
				reg int v=to[j];
				if(v<i&&getDis(v,i)<=C&&!UnionFind::search(v,i)){
					--ans;
					UnionFind::merge(v,i);
				}
			}
			printf("%d\n",ans);
		}
		return;
	}
}

namespace Subtask5{
	const int MAXLOG2N=19+1;
	int fa[MAXN][MAXLOG2N],dep[MAXN];
	inline void dfs(reg int u,reg int father){
		fa[u][0]=father;
		dep[u]=dep[father]+1;
		for(reg int i=1;i<MAXLOG2N;++i)
			fa[u][i]=fa[fa[u][i-1]][i-1];
		for(reg int i=head[u];i;i=Next[i]){
			reg int v=to[i];
			if(v!=father)
				dfs(v,u);
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
	inline int getDis(reg int x,reg int y){
		reg int lca=LCA(x,y);
		return dep[x]+dep[y]-(dep[lca]<<1);
	}
	namespace UnionFind{
		int fa[MAXN];
		inline void Init(reg int l,reg int r){
			for(reg int i=l;i<=r;++i)
				fa[i]=i;
			return;
		}
		inline int find(reg int x){
			if(x==fa[x])
				return x;
			else
				return fa[x]=find(fa[x]);
		}
		inline void merge(reg int a,reg int b){
			reg int ra=find(a),rb=find(b);
			if(ra!=rb)
				fa[rb]=ra;
			return;
		}
		inline bool search(reg int a,reg int b){
			return find(a)==find(b);
		}
	}
	inline void Solve(void){
		dfs(1,0);
		for(reg int i=1;i<=m;++i){
			reg int x=r[i]-l[i]+1;
			if(n-x+1<=C)
				puts("1");
			else{
				UnionFind::Init(l[i],r[i]);
				reg int ans=r[i]-l[i]+1;
				for(reg int u=l[i];u<=r[i];++u)
					for(reg int v=u+1;v<=r[i];++v)
						if(getDis(u,v)<=C&&!UnionFind::search(u,v)){
							--ans;
							UnionFind::merge(u,v);
						}
				printf("%d\n",ans);
			}
		}
		return;
	}
}

int main(void){
	reg bool subtaskflagt1=true,subtaskflagt2=true;
	n=read(),m=read(),C=read();
	for(reg int i=2;i<=n;++i){
		static int p;
		p=read();
		++deg[p],++deg[i];
		Add_Edge(p,i),Add_Edge(i,p);
	}
	for(reg int i=1;i<=m;++i){
		l[i]=read(),r[i]=read();
		if(r[i]!=i)
			subtaskflagt2=false;
	}
	for(reg int i=1;i<=n;++i)
		if(deg[i]>2)
			subtaskflagt1=false;
	if(n<=100){
		Subtask1::Solve();
	}
	else if(C>=n-1){
		Subtask2::Solve();
	}
	else if(subtaskflagt1&&subtaskflagt2){
		Subtask4::Solve();
	}
	else if(subtaskflagt2){
		Subtask4::Solve();
	}
	else{
		Subtask5::Solve();
	}
	return 0;
}