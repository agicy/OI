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

const int MAXN=100000+5;
const int MAXM=300000+5;
const int MAXLOG2N=18+1;

inline void Read(void);
inline void Work(void);

int main(void){
	Read();
	Work();
	return 0;
}

int n,m;

struct Edge{
	int from,to,len;
	inline Edge(reg int from=0,reg int to=0,reg int len=0):from(from),to(to),len(len){
		return;
	}
	inline bool operator<(const Edge& a)const{
		return len<a.len;
	}
};

int tot;
Edge E[MAXM];

inline void Read(void){
	n=read(),m=read();
	for(reg int i=1;i<=m;++i){
		static int a,b,l;
		a=read(),b=read(),l=read();
		E[++tot]=Edge(a,b,l);
	}
	return;
}

namespace UnionFind{
	int ID[MAXN<<1];
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
}

using namespace UnionFind;

int Count;
int v[MAXN<<1];
int cnt,head[MAXN<<1],to[MAXN<<1],Next[MAXN<<1];
inline void Add_Edge(reg int u,reg int v){
	Next[++cnt]=head[u];
	to[cnt]=v;
	head[u]=cnt;
	return;
}

inline void Kruskal(void){
	reg int cnt=0;
	for(reg int i=1;i<=tot&&cnt<n-1;++i){
		if(!search(E[i].from,E[i].to)){
			++cnt;
			reg int k=++Count,fa=find(E[i].from),fb=find(E[i].to);
			v[k]=E[i].len;
			Add_Edge(k,fa),Add_Edge(k,fb);
			merge(k,fa),merge(k,fb);
		}
	}
	return;
}

int fa[MAXN<<1][MAXLOG2N];
int dep[MAXN<<1];

inline void DFS(reg int ID,reg int father){
	fa[ID][0]=father;
	dep[ID]=dep[father]+1;
	for(reg int i=1;i<MAXLOG2N;++i)
		fa[ID][i]=fa[fa[ID][i-1]][i-1];
	for(reg int i=head[ID];i;i=Next[i])
		if(to[i]!=father)
			DFS(to[i],ID);
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
	Count=n;
	Init(2*n);
	sort(E+1,E+tot+1);
	Kruskal();
	dep[0]=1;
	DFS(Count,0);
	reg int q=read();
	while(q--){
		static int a,b;
		a=read(),b=read();
		if(!search(a,b))
			puts("impossible");
		else
			printf("%d\n",v[LCA(a,b)]);
	}
	return;
}