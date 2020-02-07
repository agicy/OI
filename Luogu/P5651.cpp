#include<bits/stdc++.h>
using namespace std;
#define reg register
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
const int MAXM=2*MAXN;

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
};

int n,m,Q;
Edge E[MAXM];

inline void Read(void){
	n=read(),m=read(),Q=read();
	for(reg int i=1;i<=m;++i)
		E[i].Read();
	return;
}

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

int cnt,head[MAXN],to[MAXN<<1],w[MAXN<<1],Next[MAXN<<1];
UnionFind S;

inline void Add_Edge(reg int u,reg int v,reg int len){
	Next[++cnt]=head[u];
	to[cnt]=v;
	w[cnt]=len;
	head[u]=cnt;
	return;
}

int dis[MAXN];

inline void DFS(reg int ID,reg int father){
	for(reg int i=head[ID];i;i=Next[i])
		if(to[i]!=father){
			dis[to[i]]=dis[ID]^w[i];
			DFS(to[i],ID);
		}
	return;
}

inline void Work(void){
	S.Init(n);
	for(reg int i=1,cnt=0;i<=m&&cnt<n-1;++i)
		if(!S.search(E[i].f,E[i].t)){
			S.merge(E[i].f,E[i].t);
			Add_Edge(E[i].f,E[i].t,E[i].len);
			Add_Edge(E[i].t,E[i].f,E[i].len);
		}
	DFS(1,0);
	while(Q--){
		static int x,y;
		x=read(),y=read();
		printf("%d\n",dis[x]^dis[y]);
	}
	return;
}
