#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++)
static char buf[100000],*p1=buf,*p2=buf;
inline int read(void){
	reg char ch=getchar();
	reg int res=0;
	while(ch<'0'||'9'<ch)ch=getchar();
	while('0'<=ch&&ch<='9')res=10*res+ch-'0',ch=getchar();
	return res;
}

const int MAXN=3e5+5;
const int MAXM=3e5+5;

int n,m;
int cnt,head[MAXN],from[MAXM<<1],to[MAXM<<1],w[MAXM<<1],Next[MAXM<<1];

inline void Add_Edge(reg int u,reg int v,reg int len){
	Next[++cnt]=head[u];
	from[cnt]=u,to[cnt]=v;
	w[cnt]=len;
	head[u]=cnt;
	return;
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

bool cut[MAXM<<1];
int tim,dfn[MAXN],low[MAXN];

inline void tarjan(reg int u,reg int id){
	dfn[u]=low[u]=++tim;
	for(reg int i=head[u];i;i=Next[i]){
		if(i==id)
			continue;
		reg int v=to[i];
		if(!dfn[v]){
			tarjan(v,i^1);
			low[u]=min(low[u],low[v]);
			if(dfn[u]<low[v])
				cut[i]=cut[i^1]=true;
		}
		else
			low[u]=min(low[u],dfn[v]);
	}
	return;
}

int main(void){
	reg int T=read();
	while(T--){
		cnt=1,memset(head,0,sizeof(head));
		memset(cut,false,sizeof(cut));
		n=read(),m=read();
		for(reg int i=1;i<=m;++i){
			static int x,y,c;
			x=read(),y=read(),c=read();
			Add_Edge(x,y,c);
			Add_Edge(y,x,c);
		}
		reg int src=read(),dst=read();
		Add_Edge(src,dst,0);
		Add_Edge(dst,src,0);
		tim=0,memset(dfn,0,sizeof(dfn));
		UnionFind::Init(n);
		for(reg int i=1;i<=n;++i)
			if(!dfn[i])
				tarjan(i,0);
		for(reg int i=2;i<=cnt;++i)
			if(!cut[i])
				UnionFind::merge(from[i],to[i]);
		if(!UnionFind::search(src,dst))
			puts("NO");
		else{
			reg bool flag=false;
			for(reg int i=2;i<=cnt;++i)
				if(!cut[i]&&UnionFind::search(src,from[i])&&w[i]){
					flag=true;
					break;
				}
			puts(flag?"YES":"NO");
		}
	}
	return 0;
}