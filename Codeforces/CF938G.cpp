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

const int MAXN=2e5+5;
const int MAXM=2e5+5;
const int MAXQ=2e5+5;
const int MAXLOG2D=30;
const int MAXT=MAXM+MAXQ;
const int MAXE=MAXM+MAXQ;

struct Edge{
	int u,v,w;
	inline Edge(reg int u=0,reg int v=0,reg int w=0):u(u),v(v),w(w){
		return;
	}
};

struct Basis{
	int unit[MAXLOG2D];
	inline Basis(void){
		memset(unit,0,sizeof(unit));
		return;
	}
	inline void insert(reg int x){
		for(reg int i=MAXLOG2D-1;i>=0;--i)
			if((x>>i)&1){
				if(!unit[i]){
					unit[i]=x;
					return;
				}
				x^=unit[i];
			}
		return;
	}
	inline int query(reg int x){
		for(reg int i=MAXLOG2D-1;i>=0;--i)
			if((x^unit[i])<x)
				x^=unit[i];
		return x;
	}
};

struct Event{
	int u;
	inline Event(reg int u=0):u(u){
		return;
	}
};

namespace UnionFind{
	int fa[MAXN],f[MAXN],siz[MAXN];
	inline void Init(reg int n){
		for(reg int i=1;i<=n;++i)
			fa[i]=i,f[i]=0,siz[i]=1;
		return;
	}
	inline int find(reg int x){
		while(x!=fa[x])
			x=fa[x];
		return x;
	}
	inline int getVal(reg int x){
		reg int res=0;
		while(x!=fa[x])
			res^=f[x],x=fa[x];
		return res;
	}
	inline Event merge(const Edge& e){
		reg int ra=find(e.u),rb=find(e.v),val=e.w^getVal(e.u)^getVal(e.v);
		if(ra==rb)
			return Event(0);
		else if(siz[ra]>siz[rb]){
			siz[ra]+=siz[rb];
			fa[rb]=ra;
			f[rb]=val;
			return Event(rb);
		}
		else{
			siz[rb]+=siz[ra];
			fa[ra]=rb;
			f[ra]=val;
			return Event(ra);
		}
	}
	inline void undo(const Event& e){
		reg int u=e.u;
		f[u]=0;
		siz[fa[u]]-=siz[u];
		fa[u]=u;
		return;
	}
}

int n,m,q;
map<pair<int,int>,int> M;
Edge E[MAXE];
int lef[MAXE],rig[MAXE];
int qx[MAXT],qy[MAXT];

namespace SegmentTree{
	#define lson ( (k) << 1 )
	#define rson ( (k) << 1 | 1 )
	#define mid ( ( (l) + (r) ) >> 1 )
	struct Node{
		vector<Edge> V;
		#define V(x) unit[(x)].V
	};
	Node unit[MAXT<<2];
	inline void update(reg int k,reg int l,reg int r,reg int L,reg int R,const Edge& e){
		if(L<=l&&r<=R){
			V(k).push_back(e);
			return;
		}
		if(L<=mid)
			update(lson,l,mid,L,R,e);
		if(R>mid)
			update(rson,mid+1,r,L,R,e);
		return;
	}
	int top;
	Event S[MAXE];
	inline void query(reg int k,reg int l,reg int r,Basis G){
		reg int tmp=top;
		for(vector<Edge>::iterator it=V(k).begin();it!=V(k).end();++it){
			Event e=UnionFind::merge(*it);
			if(e.u)
				S[++top]=e;
			else
				G.insert(it->w^UnionFind::getVal(it->u)^UnionFind::getVal(it->v));
		}
		if(l==r)
			printf("%d\n",G.query(UnionFind::getVal(qx[l])^UnionFind::getVal(qy[l])));
		else{
			query(lson,l,mid,G),query(rson,mid+1,r,G);
		}
		while(top>tmp)
			UnionFind::undo(S[top--]);
		return;
	}
	#undef lson
	#undef rson
	#undef mid
}


int main(void){
	n=read(),m=read();
	reg int tot=0,tim=1;
	for(reg int i=1;i<=m;++i){
		static int x,y,d;
		x=read(),y=read(),d=read();
		M[make_pair(x,y)]=++tot;
		lef[tot]=tim,rig[tot]=-1;
		E[tot]=Edge(x,y,d);
	}
	q=read();
	for(reg int i=1;i<=q;++i){
		static int opt,x,y,d;
		opt=read();
		switch(opt){
			case 1:{
				x=read(),y=read(),d=read();
				M[make_pair(x,y)]=++tot;
				lef[tot]=tim,rig[tot]=-1;
				E[tot]=Edge(x,y,d);
				break;
			}
			case 2:{
				x=read(),y=read();
				rig[M[make_pair(x,y)]]=tim-1;
				break;
			}
			case 3:{
				x=read(),y=read();
				qx[tim]=x,qy[tim]=y,++tim;
				break;
			}
		}
	}
	--tim;
	for(reg int i=1;i<=tot;++i)
		if(rig[i]==-1)
			rig[i]=tim;
	for(reg int i=1;i<=tot;++i)
		if(lef[i]<=rig[i])
			SegmentTree::update(1,1,tim,lef[i],rig[i],E[i]);
	UnionFind::Init(n);
	Basis G;
	SegmentTree::query(1,1,tim,G);
	return 0;
}