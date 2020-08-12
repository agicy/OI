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

const int MAXN=5e5+5;
const int MAXM=5e5+5;

struct Edge{
	int u,v,l,r;
	inline Edge(reg int u=0,reg int v=0,reg int l=0,reg int r=0):u(u),v(v),l(l),r(r){
		return;
	}
};

struct Stack{
	int rx,ry,add;
	inline Stack(reg int rx=0,reg int ry=0,reg int add=0):rx(rx),ry(ry),add(add){
		return;
	}
};

const int MAXSIZE=5e5+5;

Edge E[MAXM];
int top;
Stack S[MAXSIZE];

namespace UnionFind{
	int fa[MAXN],siz[MAXN];
	inline void Init(reg int S){
		for(reg int i=1;i<=S;++i)
			fa[i]=i,siz[i]=1;
		return;
	}
	inline int find(reg int x){
		if(x==fa[x])
			return x;
		else
			return find(fa[x]);
	}
	inline void merge(reg int x,reg int y){
		int rx=find(x),ry=find(y);
		if(rx==ry)
			return;
		if(siz[rx]>siz[ry])
			swap(rx,ry);
		S[++top]=Stack(rx,ry,siz[rx]==siz[ry]);
		fa[rx]=ry;
		if(siz[rx]==siz[ry])siz[ry]++;
	}
	inline bool search(reg int a,reg int b){
		return find(a)==find(b);
	}
}

using namespace UnionFind;

int n,m;
map<pair<int,int>,int> M;
int id[MAXM];
pair<int,int> Q[MAXM];

namespace SegmentTree{
	#define lson ( (k) << 1 )
	#define rson ( (k) << 1 | 1 )
	#define mid ( ( (l) + (r) ) >> 1 )
	struct Node{
		vector<pair<int,int>/**/> V;
		#define V(x) unit[(x)].V
	};
	Node unit[MAXN<<2];
	inline void update(reg int k,reg int l,reg int r,reg int L,reg int R,int u,int v){
		if(L<=l&&r<=R){
			V(k).push_back(make_pair(u,v));
			return;
		}
		if(L<=mid)
			update(lson,l,mid,L,R,u,v);
		if(R>mid)
			update(rson,mid+1,r,L,R,u,v);
		return;
	}
	inline void solve(reg int k,reg int l,reg int r){
		reg int last=top;
		for(reg int i=0,size=V(k).size();i<size;++i)
			merge(V(k)[i].first,V(k)[i].second);
		if(l==r&&id[l]){
			reg int u=Q[id[l]].first,v=Q[id[l]].second;
			puts(search(u,v)?"Y":"N");
		}
		if(l!=r)
			solve(lson,l,mid),solve(rson,mid+1,r);
		while(top>last){
			siz[S[top].ry]-=S[top].add;
			fa[S[top].rx]=S[top].rx;
			--top;
		}
		return;
	}
}

int main(void){
	n=read(),m=read();
	reg int cntE=0,cntQ=0;
	for(reg int i=1;i<=m;++i){
		static int op,x,y;
		op=read(),x=read(),y=read();
		if(x>y)
			swap(x,y);
		if(op==0)
			M[make_pair(x,y)]=i;
		else if(op==1){
			reg int l=M[make_pair(x,y)];
			M.erase(make_pair(x,y));
			E[++cntE]=Edge(x,y,l,i);
		}
		else{
			Q[++cntQ]=make_pair(x,y);
			id[i]=cntQ;
		}
	}
	for(map<pair<int,int>,int>::iterator it=M.begin();it!=M.end();++it)
		E[++cntE]=Edge(it->first.first,it->first.second,it->second,m);
	for(reg int i=1;i<=cntE;++i)
		SegmentTree::update(1,1,m,E[i].l,E[i].r,E[i].u,E[i].v);
	Init(n);
	SegmentTree::solve(1,1,m);
	return 0;
}