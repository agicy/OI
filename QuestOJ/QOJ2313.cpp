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
	while(isdigit(ch))res=10*res+ch-'0',ch=getchar();
	return res;
}

const int MAXN=5e5+5;
const int MAXM=5e5+5;
const int p=998244353;

inline int add(reg int a,reg int b){
	a+=b;
	return a>=p?a-p:a;
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
		fa[rb]=ra;
		return;
	}
	inline bool search(reg int a,reg int b){
		return find(a)==find(b);
	}
}

int n,m;
int cnt,head[MAXN],to[MAXN<<1],w[MAXN<<1],Next[MAXN<<1];

inline void Add_Edge(reg int u,reg int v,reg int len){
	Next[++cnt]=head[u];
	to[cnt]=v;
	w[cnt]=len;
	head[u]=cnt;
	return;
}

int V[MAXN];
bool tag[MAXN];
int ans;

inline bool dfs(reg int u,reg int father){
	reg bool sum=tag[u];
	for(reg int i=head[u];i;i=Next[i]){
		reg int v=to[i];
		if(v!=father){
			V[v]=w[i];
			sum^=dfs(v,u);
		}
	}
	if(!sum)
		ans=add(ans,V[u]);
	return sum;
}

int main(void){
	n=read(),m=read();
	UnionFind::Init(n);
	reg int val=1;
	for(reg int i=1;i<=m;++i){
		val=add(val,val);
		ans=add(ans,val);
		static int u,v;
		u=read(),v=read();
		if(!UnionFind::search(u,v)){
			UnionFind::merge(u,v);
			Add_Edge(u,v,val);
			Add_Edge(v,u,val);
		}
		else
			tag[u]=!tag[u],tag[v]=!tag[v];
	}
	dfs(1,0);
	printf("%d\n",ans);
	return 0;
}