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

const int MAXN=123456+5;
const int MAXM=123456+5;
const int MAXLOG2N=17+1;

int n,m;

namespace Tree{
	int cnt,head[MAXN],to[MAXN<<1],Next[MAXN<<1];
	inline void Add_Edge(reg int u,reg int v){
		Next[++cnt]=head[u];
		to[cnt]=v;
		head[u]=cnt;
		return;
	}
	int fa[MAXN][MAXLOG2N],dep[MAXN];
	int tim,dfn[MAXN];
	bool vis[MAXN];
	int Min[MAXN][MAXLOG2N];
	inline void dfs(reg int u,reg int father){
		vis[u]=true;
		fa[u][0]=father;
		dep[u]=dep[father]+1;
		Min[u][0]=u;
		dfn[u]=++tim;
		for(reg int i=1;i<MAXLOG2N;++i){
			fa[u][i]=fa[fa[u][i-1]][i-1];
			Min[u][i]=min(Min[u][i-1],Min[fa[u][i-1]][i-1]);
		}
		for(reg int i=head[u];i;i=Next[i]){
			reg int v=to[i];
			if(v!=father)
				dfs(v,u);
		}
		return;
	}
	inline pair<int,int> LCA(int x,int y){
		if(dep[x]>dep[y])
			swap(x,y);
		int res=1e9;
		for(reg int i=MAXLOG2N-1;i>=0;--i)
			if(dep[fa[y][i]]>=dep[x]){
				res=min(res,Min[y][i]);
				y=fa[y][i];
			}
		if(x==y)
			return make_pair(x,min(res,x));
		for(reg int i=MAXLOG2N-1;i>=0;--i)
			if(fa[x][i]!=fa[y][i]){
				res=min(res,min(Min[x][i],Min[y][i]));
				x=fa[x][i],y=fa[y][i];
			}
		return make_pair(fa[x][0],min(min(res,min(Min[x][0],Min[y][0])),fa[x][0]));
	}
	inline pair<int,int> getInfo(reg int x,reg int y){
		pair<int,int> p=LCA(x,y);
		reg int lca=p.first;
		reg int M=p.second;
		return make_pair(dep[x]+dep[y]-(dep[lca]<<1),M);
	}
}

namespace Vitrual_Tree{
	int cnt,head[MAXN],to[MAXN<<1],w[MAXN<<1],Next[MAXN<<1];
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
	bool vis[MAXN];
	int dis[MAXN];
	queue<int> Q;
	inline int bfs(int s){
		memset(vis,false,sizeof(vis));
		memset(dis,0,sizeof(dis));
		vis[s]=true,dis[s]=0,Q.push(s);
		while(!Q.empty()){
			reg int u=Q.front();
			Q.pop();
			for(reg int i=head[u];i;i=Next[i]){
				int v=to[i];
				if(!vis[v]){
					vis[v]=true;
					dis[v]=dis[u]+w[i];
					Q.push(v);
				}
			}
		}
		reg int res=s;
		for(reg int i=1;i<=n;++i)
			if(dis[i]>dis[res])
				res=i;
		return res;
	}
}

inline bool cmp(reg int a,reg int b){
	return Tree::dfn[a]<Tree::dfn[b];
}

int h[MAXM];
int tmp[MAXM];
bool key[MAXN];
int S[MAXM];

int main(void){
	n=read(),m=read();
	for(reg int i=1;i<n;++i){
		static int x,y;
		x=read(),y=read();
		Tree::Add_Edge(x,y);
		Tree::Add_Edge(y,x);
	}
	Tree::dfs(1,0);
	for(reg int i=1;i<=m;++i){
		h[i]=read();
		tmp[i]=h[i];
		key[h[i]]=true;
	}
	sort(tmp+1,tmp+m+1,cmp);
	reg int top=0;
	S[++top]=tmp[1];
	using Tree::dep;
	reg ll sum=0;
	reg int ans1=tmp[1];
	for(reg int i=2;i<=m;++i){
		reg int x=tmp[i],y=Tree::LCA(x,S[top]).first;
		while(top>1&&dep[y]<=dep[S[top-1]]){
			pair<int,int> p=Tree::getInfo(S[top-1],S[top]);
			ans1=min(ans1,p.second);
			sum+=p.first;
			Vitrual_Tree::Add_Tube(S[top-1],S[top],p.first);
			--top;
		}
		if(S[top]!=y){
			pair<int,int> p=Tree::getInfo(y,S[top]);
			ans1=min(ans1,p.second);
			sum+=p.first;
			Vitrual_Tree::Add_Tube(y,S[top],p.first);
			S[top]=y;
		}
		S[++top]=x;
	}
	while(top>1){
		pair<int,int> p=Tree::getInfo(S[top-1],S[top]);
		ans1=min(ans1,p.second);
		sum+=p.first;
		Vitrual_Tree::Add_Tube(S[top-1],S[top],p.first);
		--top;
	}
	reg int rt=S[1];
	reg int x=Vitrual_Tree::bfs(rt);
	reg int y=Vitrual_Tree::bfs(x);
	reg ll ans2=sum*2-Vitrual_Tree::dis[y];
	printf("%d\n%lld\n",ans1,ans2);
	return 0;
}