#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
#define INF 0X7F7F7F7F7F7F7F7F
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
const int MAXW=200000;
const int delta=100000;

int n;
int a[MAXN],b[MAXN];
ll dp[MAXN];

struct Line{
	ll k,b;
	inline Line(reg ll k=0,reg ll b=0):k(k),b(b){
		return;
	}
};

Line L[MAXN];

inline ll GetY(reg int id,reg ll x){
	return L[id].k*(x-delta)+L[id].b;
}

int cnt,head[MAXN],to[MAXN<<1],Next[MAXN<<1];

inline void Add_Edge(reg int u,reg int v){
	Next[++cnt]=head[u];
	to[cnt]=v;
	head[u]=cnt;
	return;
}

inline void Add_Tube(reg int u,reg int v){
	Add_Edge(u,v);
	Add_Edge(v,u);
	return;
}

namespace SegmentTree{
	#define mid ( ( (l) + (r) ) >> 1 )
	struct Node{
		int lson,rson;
		int id;
		inline Node(reg int lson=0,reg int rson=0,reg int id=0):lson(lson),rson(rson),id(id){
			return;
		}
		#define lson(x) unit[(x)].lson
		#define rson(x) unit[(x)].rson
		#define id(x) unit[(x)].id
	};
	Node unit[MAXN];
	int tot,root[MAXN];
	inline void Update(reg int &k,reg int l,reg int r,reg int y){
		if(!k){
			unit[k=y]=Node(0,0,id(y));
			return;
		}
		if(GetY(id(k),l)<=GetY(id(y),l)&&GetY(id(k),r)<=GetY(id(y),r)){
			return;
		}
		if(GetY(id(k),l)>=GetY(id(y),l)&&GetY(id(k),r)>=GetY(id(y),r)){
			id(k)=id(y);
			return;
		}
		reg int &a=id(k),&b=id(y);
		if(L[a].k<L[b].k){
			if(GetY(a,mid)>GetY(b,mid)){
				swap(a,b);
				Update(rson(k),mid+1,r,y);
			}
			else
				Update(lson(k),l,mid,y);
		}
		else{
			if(GetY(a,mid)>GetY(b,mid)){
				swap(a,b);
				Update(lson(k),l,mid,y);
			}
			else
				Update(rson(k),mid+1,r,y);
		}
		return;
	}
	inline int merge(int p,reg int q,reg int l,reg int r){
		if(!p||!q)
			return p|q;
		if(l==r){
			if(GetY(id(p),l)>GetY(id(q),l))
				return q;
			else
				return p;
		}
		lson(p)=merge(lson(p),lson(q),l,mid);
		rson(p)=merge(rson(p),rson(q),mid+1,r);
		Update(p,l,r,q);
		return p;
	}
	inline ll Query(reg int k,reg int l,reg int r,reg int pos){
		if(!k)
			return INF;
		if(l==r)
			return GetY(id(k),pos);
		if(pos<=mid)
			return min(GetY(id(k),pos),Query(lson(k),l,mid,pos));
		else
			return min(GetY(id(k),pos),Query(rson(k),mid+1,r,pos));
	}
	#undef mid
}

using namespace SegmentTree;

inline void DFS(reg int ID,reg int father){
	for(reg int i=head[ID];i;i=Next[i])
		if(to[i]!=father){
			DFS(to[i],ID);
			root[ID]=merge(root[ID],root[to[i]],0,MAXW);
		}
	if(root[ID])
		dp[ID]=Query(root[ID],0,MAXW,a[ID]+delta);
	L[ID]=Line(b[ID],dp[ID]);
	unit[++tot]=Node(0,0,ID);
	Update(root[ID],0,MAXW,tot);
	return;
}

int main(void){
	n=read();
	for(reg int i=1;i<=n;++i)
		a[i]=read();
	for(reg int i=1;i<=n;++i)
		b[i]=read();
	//puts("AAAA");
	for(reg int i=1;i<n;++i){
		static int u,v;
		u=read(),v=read();
		Add_Tube(u,v);
	}
	DFS(1,0);
	for(reg int i=1;i<=n;++i)
		printf("%lld%c",dp[i],i==n?'\n':' ');
	return 0;
}