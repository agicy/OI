#pragma GCC optimize(2)
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

const int MAXN=1.5e5+5;
const int MAXM=1.5e5+5;
const int inf=0x3f3f3f3f;

int n,m;
int cnt,head[MAXN],to[MAXM<<1],w[MAXM<<1],Next[MAXM<<1];

inline void Add_Edge(reg int u,reg int v,reg int len){
	Next[++cnt]=head[u];
	to[cnt]=v,w[cnt]=len;
	head[u]=cnt;
	return;
}

namespace SegmentTree{
	#define lson ( (k) << 1 )
	#define rson ( (k) << 1 | 1 )
	#define mid ( ( (l) + (r) ) >> 1 )
	struct Node{
		int Min;
		int id;
		#define Min(x) unit[(x)].Min
		#define id(x) unit[(x)].id
	};
	const int MAXSIZE=1048576;
	Node unit[MAXSIZE];
	int limit;
	inline void build(reg int n){
		limit=1;
		while(limit<n)
			limit<<=1;
		memset(unit,0x3f,sizeof(unit));
		for(reg int i=limit+1;i<=limit+n;++i)
			id(i)=i-limit;
		for(reg int i=limit-1;i;--i)
			if(Min(i<<1)<Min(i<<1|1))
				Min(i)=Min(i<<1),id(i)=id(i<<1);
			else
				Min(i)=Min(i<<1|1),id(i)=id(i<<1|1);
		return;
	}
	inline void update(reg int pos,reg int val){
		Min(pos+=limit)=val;
		while(pos){
			pos>>=1;
			if(Min(pos<<1)<Min(pos<<1|1))
				Min(pos)=Min(pos<<1),id(pos)=id(pos<<1);
			else
				Min(pos)=Min(pos<<1|1),id(pos)=id(pos<<1|1);
		}
		return;
	}
	inline int query(void){
		return id(1);
	}
	#undef lson
	#undef rson
	#undef mid
}

bool vis[MAXN];
int dis[MAXN];

inline void dijkstra(reg int s){
	memset(dis,0x3f,sizeof(dis));
	vis[0]=true,SegmentTree::build(n);
	dis[s]=0,SegmentTree::update(s,0);
	for(reg int T=1;T<n;++T){
		reg int u=SegmentTree::query();
		if(u>=n||u<0)
			break;
		SegmentTree::update(u,inf);
		for(reg int i=head[u];i;i=Next[i]){
			reg int v=to[i];
			if(dis[v]>dis[u]+w[i]){
				dis[v]=dis[u]+w[i];
				SegmentTree::update(v,dis[v]);
			}
		}
	}
	return;
}

int main(void){
	n=read(),m=read();
	for(reg int i=1;i<=m;++i){
		static int u,v,w;
		u=read(),v=read(),w=read();
		Add_Edge(u,v,w);
	}
	dijkstra(1);
	printf("%d\n",dis[n]==inf?-1:dis[n]);
	return 0;
}