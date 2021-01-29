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

const int MAXN=2.5e3+5;
const int MAXM=6.2e3+5;
const ll inf=0x3f3f3f3f3f3f3f3f;

int n,m,s,t;
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
		ll Min;
		int id;
		#define Min(x) unit[(x)].Min
		#define id(x) unit[(x)].id
	};
	Node unit[MAXN<<2];
	inline void build(reg int k,reg int l,reg int r){
		Min(k)=inf;
		if(l==r)
			return;
		build(lson,l,mid),build(rson,mid+1,r);
	}
	inline void update(reg int k,reg int l,reg int r,reg int pos,reg ll val){
		if(l==r){
			Min(k)=val,id(k)=pos;
			return;
		}
		if(pos<=mid)
			update(lson,l,mid,pos,val);
		else
			update(rson,mid+1,r,pos,val);
		if(Min(lson)<Min(rson))
			Min(k)=Min(lson),id(k)=id(lson);
		else
			Min(k)=Min(rson),id(k)=id(rson);
		return;
	}
	inline int query(void){
		return id(1);
	}
	#undef lson
	#undef rson
	#undef mid
}

ll dis[MAXN];

inline void dijkstra(reg int s){
	memset(dis,0x3f,sizeof(dis));
	SegmentTree::build(1,1,n);
	dis[s]=0,SegmentTree::update(1,1,n,s,0);
	for(reg int T=1;T<n;++T){
		reg int u=SegmentTree::query();
		if(u==t)
			break;
		SegmentTree::update(1,1,n,u,inf);
		for(reg int i=head[u];i;i=Next[i]){
			reg int v=to[i];
			if(dis[v]>dis[u]+w[i]){
				dis[v]=dis[u]+w[i];
				SegmentTree::update(1,1,n,v,dis[v]);
			}
		}
	}
	return;
}

int main(void){
	n=read(),m=read(),s=read(),t=read();
	for(reg int i=1;i<=m;++i){
		static int u,v,w;
		u=read(),v=read(),w=read();
		Add_Edge(u,v,w),Add_Edge(v,u,w);
	}
	dijkstra(s);
	printf("%lld\n",dis[t]);
	return 0;
}