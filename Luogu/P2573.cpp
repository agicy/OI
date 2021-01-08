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

const int MAXN=1e5+5;
const int MAXM=1e6+5;

struct Edge{
	int u,v,val;
	inline Edge(reg int u=0,reg int v=0,reg int val=0):u(u),v(v),val(val){
		return;
	}
	inline bool operator<(const Edge& a)const{
		return val<a.val;
	}
};

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

int n,m;
int h[MAXN];
int cnt,head[MAXN],to[MAXM<<1],w[MAXM<<1],Next[MAXM<<1];
int tot;
Edge E[MAXM<<1];

inline void Add_Edge(reg int u,reg int v,reg int len){
	Next[++cnt]=head[u];
	to[cnt]=v;
	w[cnt]=len;
	head[u]=cnt;
	return;
}

bool vis[MAXN];
int Q[MAXN];

inline void bfs(reg int s){
	reg int head_=0,tail_=0;
	vis[s]=true,Q[tail_++]=s;
	while(head_<tail_){
		reg int u=Q[head_++];
		for(reg int i=head[u];i;i=Next[i]){
			reg int v=to[i];
			E[++tot]=Edge(u,v,w[i]);
			if(!vis[v])
				vis[v]=true,Q[tail_++]=v;
		}
	}
	return;
}

inline bool cmp(const Edge& a,const Edge& b){
	return h[a.v]==h[b.v]?a.val<b.val:h[a.v]>h[b.v];
}

int main(void){
	n=read(),m=read();
	for(reg int i=1;i<=n;++i)
		h[i]=read();
	for(reg int i=1;i<=m;++i){
		static int u,v,k;
		u=read(),v=read(),k=read();
		if(h[u]>=h[v])
			Add_Edge(u,v,k);
		if(h[v]>=h[u])
			Add_Edge(v,u,k);
	}
	bfs(1);
	reg int cnt=0;
	for(reg int i=1;i<=n;++i)
		if(vis[i])
			++cnt;
	reg ll ans=0;
	UnionFind::Init(n);
	sort(E+1,E+tot+1,cmp);
	for(reg int i=1;i<=tot;++i){
		if(!UnionFind::search(E[i].u,E[i].v)){
			ans+=E[i].val;
			UnionFind::merge(E[i].u,E[i].v);
		}
	}
	printf("%d %lld\n",cnt,ans);
	return 0;
}