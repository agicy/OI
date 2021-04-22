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
const int MAXQ=2e5+5;
const ll inf=0x3f3f3f3f3f3f3f3f;

namespace SegmentTree{
	#define lson ( (k) << 1 )
	#define rson ( (k) << 1 | 1 )
	#define mid ( ( (l) + (r) ) >> 1 )
	struct Node{
		ll Min1,Min2,tag;
		#define Min1(x) unit[(x)].Min1
		#define Min2(x) unit[(x)].Min2
		#define tag(x) unit[(x)].tag
	};
	Node unit[MAXN<<2];
	inline void pushup(reg int k){
		Min1(k)=min(Min1(lson),Min1(rson));
		Min2(k)=min(Min2(lson),Min2(rson));
		return;
	}
	inline void build(reg int k,reg int l,reg int r){
		tag(k)=0;
		if(l==r){
			Min1(k)=Min2(k)=inf;
			return;
		}
		build(lson,l,mid),build(rson,mid+1,r);
		pushup(k);
		return;
	}
	inline void add(reg int k,reg ll val){
		Min1(k)+=val;
		Min2(k)+=val;
		tag(k)+=val;
		return;
	}
	inline void pushdown(reg int k){
		if(tag(k)){
			add(lson,tag(k));
			add(rson,tag(k));
			tag(k)=0;
		}
		return;
	}
	inline void update(reg int k,reg int l,reg int r,reg int L,reg int R,reg ll val){
		if(L<=l&&r<=R){
			add(k,val);
			return;
		}
		pushdown(k);
		if(L<=mid)
			update(lson,l,mid,L,R,val);
		if(R>mid)
			update(rson,mid+1,r,L,R,val);
		pushup(k);
		return;
	}
	inline void update(reg int k,reg int l,reg int r,reg int pos,reg ll val){
		if(l==r){
			Min1(k)=min(Min1(k),val-pos);
			Min2(k)=min(Min2(k),val+pos);
			return;
		}
		pushdown(k);
		if(pos<=mid)
			update(lson,l,mid,pos,val);
		else
			update(rson,mid+1,r,pos,val);
		pushup(k);
		return;
	}
	inline ll queryMin1(reg int k,reg int l,reg int r,reg int L,reg int R){
		if(L<=l&&r<=R)
			return Min1(k);
		pushdown(k);
		if(L<=mid&&mid<R)
			return min(queryMin1(lson,l,mid,L,R),queryMin1(rson,mid+1,r,L,R));
		else if(L<=mid)
			return queryMin1(lson,l,mid,L,R);
		else
			return queryMin1(rson,mid+1,r,L,R);
	}
	inline ll queryMin2(reg int k,reg int l,reg int r,reg int L,reg int R){
		if(L<=l&&r<=R)
			return Min2(k);
		pushdown(k);
		if(L<=mid&&mid<R)
			return min(queryMin2(lson,l,mid,L,R),queryMin2(rson,mid+1,r,L,R));
		else if(L<=mid)
			return queryMin2(lson,l,mid,L,R);
		else
			return queryMin2(rson,mid+1,r,L,R);
	}
	inline ll query(reg int k,reg int l,reg int r){
		if(l==r)
			return Min1(k)+l;
		pushdown(k);
		return min(query(lson,l,mid),query(rson,mid+1,r));
	}
	#undef lson
	#undef rson
	#undef mid
}

int n,Q,a,b;
int x[MAXQ];

int main(void){
	n=read(),Q=read(),a=read(),b=read();
	x[0]=a;
	SegmentTree::build(1,1,n);
	SegmentTree::update(1,1,n,b,0);
	for(reg int i=1;i<=Q;++i){
		x[i]=read();
		reg ll res=min(SegmentTree::queryMin1(1,1,n,1,x[i])+x[i],SegmentTree::queryMin2(1,1,n,x[i],n)-x[i]);
		SegmentTree::update(1,1,n,1,n,abs(x[i]-x[i-1]));
		SegmentTree::update(1,1,n,x[i-1],res);
	}
	printf("%lld\n",SegmentTree::query(1,1,n));
	return 0;
}