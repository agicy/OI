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

const int MAXN=10000+5;
const int MAXLOG2N=14+1;
const int MAXM=100000+5;


inline void Read(void);
inline void Work(void);

int main(void){
	Read();
	Work();
	return 0;
}

struct Edge{
	int f,t,len;
	inline void Read(void){
		f=read(),t=read(),len=read();
		return;
	}
	inline bool operator<(const Edge& a)const{
		return len<a.len;
	}
};

struct UnionFind{
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
};

int n,m;
Edge E[MAXM];
UnionFind U;

inline void Read(void){
	n=read(),m=read();
	U.Init(n);
	for(reg int i=1;i<=m;++i)
		E[i].Read();
	return;
}

int cnt,head[MAXN],to[MAXN<<1],w[MAXN<<1],Next[MAXN<<1];

inline void Add_Edge(reg int u,reg int v,reg int len){
	Next[++cnt]=head[u];
	to[cnt]=v;
	w[cnt]=len;
	head[u]=cnt;
	return;
}

int dep[MAXN];
int fa[MAXN][MAXLOG2N];
int W[MAXN][MAXLOG2N];

inline void DFS(reg int ID,reg int father){
	fa[ID][0]=father;
	dep[ID]=dep[father]+1;
	for(reg int i=1;i<MAXLOG2N;++i)
		fa[ID][i]=fa[fa[ID][i-1]][i-1];
	for(reg int i=1;i<MAXLOG2N;++i)
		W[ID][i]=max(W[ID][i-1],W[fa[ID][i-1]][i-1]);
	for(reg int i=head[ID];i;i=Next[i])
		if(to[i]!=father){
			W[to[i]][0]=w[i];
			DFS(to[i],ID);
		}
	return;
}

inline pair<int,int> LCA(int x,int y){
	if(dep[x]>dep[y])
		swap(x,y);
	int Max=0;
	for(reg int i=MAXLOG2N-1;i>=0;--i)
		if(dep[fa[y][i]]>=dep[x]){
			Max=max(Max,W[y][i]);
			y=fa[y][i];
		}
	if(x==y)
		return make_pair(x,Max);
	for(reg int i=MAXLOG2N-1;i>=0;--i)
		if(fa[x][i]!=fa[y][i]){
			Max=max(Max,max(W[x][i],W[y][i]));
			x=fa[x][i],y=fa[y][i];
		}
	return make_pair(fa[x][0],max(Max,max(W[x][0],W[y][0])));
}

inline void Work(void){
	sort(E+1,E+m+1);
	reg int cnt=0;
	for(reg int i=1;i<=m&&cnt<n-1;++i){
		if(!U.search(E[i].f,E[i].t)){
			++cnt;
			U.merge(E[i].f,E[i].t);
			Add_Edge(E[i].f,E[i].t,E[i].len);
			Add_Edge(E[i].t,E[i].f,E[i].len);
		}
	}
	DFS(1,0);
	reg int q=read();
	while(q--){
		static int s,t;
		s=read(),t=read();
		printf("%d\n",LCA(s,t).second);
	}
	return;
}