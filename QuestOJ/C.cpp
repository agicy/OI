#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
typedef unsigned long long ull;
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

const int MAXN=300000+5;
const int MAXM=300000+5;
const int MAXLOG2N=19+1;

struct Edge{
	int f,t;
	inline Edge(void){
		f=t=0;
		return;
	}
	inline Edge(reg int a,reg int b){
		f=a,t=b;
		return;
	}
};

struct UnionFind{
	int ID[MAXN];
	inline void Init(reg int n){
		for(reg int i=1;i<=n;++i)
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
};

int n,m;
int Q;
int cnt,head[MAXN],to[MAXN<<1],Next[MAXN<<1];
bool w[MAXN<<1];
int tot;
Edge E[MAXM];
UnionFind S;

inline void Read(void);
inline void Work(void);

int main(void){
	Read();
	Work();
	return 0;
}

inline void Add_Edge(reg int u,reg int v,reg bool len){
	Next[++cnt]=head[u];
	to[cnt]=v;
	w[cnt]=len;
	head[u]=cnt;
	return;
}

inline void Read(void){
	reg int cnt=0;
	n=read(),m=read();
	S.Init(n);
	for(reg int i=1;i<=m;++i){
		static int x,y,z;
		x=read(),y=read(),z=read();
		if(z==1){
			if(!S.search(x,y)){
				++cnt;
				Add_Edge(x,y,true);
				Add_Edge(y,x,true);
				S.merge(x,y);
			}
		}
		else
			E[++tot]=Edge(x,y);
	}
	for(reg int i=1;i<=tot&&cnt<n-1;++i){
		if(!S.search(E[i].f,E[i].t)){
			++cnt;
			Add_Edge(E[i].f,E[i].t,false);
			Add_Edge(E[i].t,E[i].f,false);
			S.merge(E[i].f,E[i].t);
		}
	}
	return;
}

int fa[MAXN][MAXLOG2N];
int dep[MAXN];
int dis[MAXN];

inline void DFS(reg int ID,reg int father){
	dep[ID]=dep[father]+1;
	fa[ID][0]=father;
	for(reg int i=head[ID];i;i=Next[i])
		if(to[i]!=father){
			dis[to[i]]=dis[ID]+w[i];
			DFS(to[i],ID);
		}
	return;
}

inline void LCA_Init(void){
	for(reg int j=1;j<MAXLOG2N;++j)
		for(reg int i=1;i<=n;++i)
			fa[i][j]=fa[fa[i][j-1]][j-1];
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

inline void Work(void){
	DFS(1,0);
	LCA_Init();
	Q=read();
	while(Q--){
		static int s,t,lca;
		s=read(),t=read();
		lca=LCA(s,t);
		reg int sum=dis[s]+dis[t]-dis[lca]*2;
		puts(sum?"YES":"NO");
	}
	return;
}
