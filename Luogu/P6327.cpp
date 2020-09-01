#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

const int MAXN=2e5+5;

namespace SegmentTree{
	#define lson ( (k) << 1 )
	#define rson ( (k) << 1 | 1 )
	#define mid ( ( (l) + (r) ) >> 1 )
	struct Node{
		double s,c;
		ll tag;
		#define s(x) unit[(x)].s
		#define c(x) unit[(x)].c
		#define tag(x) unit[(x)].tag
	};
	Node unit[MAXN<<2];
	inline void pushup(int k){
		s(k)=s(lson)+s(rson);
		c(k)=c(lson)+c(rson);
		return;
	}
	inline void build(int k,int l,int r,ll a[]){
		if(l==r){
			s(k)=sin(a[l]),c(k)=cos(a[l]),tag(k)=0;
			return;
		}
		build(lson,l,mid,a),build(rson,mid+1,r,a);
		pushup(k);
		return;
	}
	inline void add(int k,ll val){
		double si=sin(val),co=cos(val);
		double tmps=s(k),tmpc=c(k);
		s(k)=tmps*co+tmpc*si;
		c(k)=tmpc*co-tmps*si;
		tag(k)+=val;
		return;
	}
	inline void pushdown(int k){
		if(tag(k)){
			add(lson,tag(k));
			add(rson,tag(k));
			tag(k)=0;
		}
		return;
	}
	inline void update(int k,int l,int r,int L,int R,ll val){
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
	inline double query(int k,int l,int r,int L,int R){
		if(L<=l&&r<=R)
			return s(k);
		pushdown(k);
		double res=0;
		if(L<=mid)
			res+=query(lson,l,mid,L,R);
		if(R>mid)
			res+=query(rson,mid+1,r,L,R);
		return res;
	}
	#undef lson
	#undef rson
	#undef mid
}

int n,m;
ll a[MAXN];

int main(void){
	scanf("%d",&n);
	for(int i=1;i<=n;++i)
		scanf("%lld",&a[i]);
	SegmentTree::build(1,1,n,a);
	scanf("%d",&m);
	while(m--){
		static int opt,l,r,v;
		scanf("%d",&opt);
		switch(opt){
			case 1:{
				scanf("%d%d%d",&l,&r,&v);
				SegmentTree::update(1,1,n,l,r,v);
				break;
			}
			case 2:{
				scanf("%d%d",&l,&r);
				printf("%.1lf\n",SegmentTree::query(1,1,n,l,r));
				break;
			}
		}
	}
	return 0;
}