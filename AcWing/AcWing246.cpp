#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

const int MAXN=5e5+5;

inline ll gcd(ll a,ll b){
	return b==0?a:gcd(b,a%b);
}

namespace SegmentTree{
	#define lson ( (k) << 1 )
	#define rson ( (k) << 1 | 1 )
	#define mid ( ( (l) + (r) ) >> 1 )
	struct Node{
		ll v,d;
		#define v(x) unit[(x)].v
		#define d(x) unit[(x)].d
	};
	Node unit[MAXN<<2];
	inline void pushup(int k){
		v(k)=v(lson)+v(rson);
		d(k)=gcd(d(lson),d(rson));
		return;
	}
	inline void build(int k,int l,int r,ll a[]){
		if(l==r){
			v(k)=d(k)=a[l];
			return;
		}
		build(lson,l,mid,a),build(rson,mid+1,r,a);
		pushup(k);
		return;
	}
	inline ll queryGcd(int k,int l,int r,int L,int R){
		if(L<=l&&r<=R)
			return d(k);
		if(R<=mid)
			return queryGcd(lson,l,mid,L,R);
		else if(L>mid)
			return queryGcd(rson,mid+1,r,L,R);
		else
			return gcd(queryGcd(lson,l,mid,L,R),queryGcd(rson,mid+1,r,L,R));
	}
	inline ll queryVal(int k,int l,int r,int L,int R){
		if(L<=l&&r<=R)
			return v(k);
		if(R<=mid)
			return queryVal(lson,l,mid,L,R);
		else if(L>mid)
			return queryVal(rson,mid+1,r,L,R);
		else
			return queryVal(lson,l,mid,L,R)+queryVal(rson,mid+1,r,L,R);
	}
	inline void update(int k,int l,int r,int pos,ll val){
		if(l==r){
			v(k)+=val,d(k)+=val;
			return;
		}
		if(pos<=mid)
			update(lson,l,mid,pos,val);
		else
			update(rson,mid+1,r,pos,val);
		pushup(k);
		return;
	}
	#undef lson
	#undef rson
	#undef mid
}

int n,m;
ll a[MAXN],b[MAXN];

int main(void){
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;++i){
		scanf("%lld",&a[i]);
		b[i]=a[i]-a[i-1];
	}
	SegmentTree::build(1,1,n,b);
	while(m--){
		static char opt[4];
		static ll l,r,d;
		scanf("%s",opt);
		switch(opt[0]){
			case 'C':{
				scanf("%lld%lld%lld",&l,&r,&d);
				SegmentTree::update(1,1,n,l,d);
				if(r+1<=n)
					SegmentTree::update(1,1,n,r+1,-d);
				break;
			}
			case 'Q':{
				scanf("%lld%lld",&l,&r);
				ll tmp1=SegmentTree::queryVal(1,1,n,1,l);
				ll tmp2=SegmentTree::queryGcd(1,1,n,l+1,r);
				printf("%lld\n",abs(gcd(tmp1,tmp2)));
				break;
			}
		}
	}
	return 0;
}