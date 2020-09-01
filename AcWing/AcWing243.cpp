#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

const int MAXN=1e5+5;

int n,m;
int a[MAXN];

namespace SegmentTree{
	#define lson ( (k) << 1 )
	#define rson ( (k) << 1 | 1 )
	#define mid ( ( (l) + (r) ) >> 1 )
	struct Node{
		ll sum,tag;
		#define sum(x) unit[(x)].sum
		#define tag(x) unit[(x)].tag
	};
	Node unit[MAXN<<2];
	inline void pushup(int k){
		sum(k)=sum(lson)+sum(rson);
		return;
	}
	inline void build(int k,int l,int r,int a[]){
		if(l==r){
			sum(k)=a[l];
			return;
		}
		build(lson,l,mid,a),build(rson,mid+1,r,a);
		pushup(k);
		return;
	}
	inline void add(int k,int l,int r,int val){
		sum(k)+=1ll*(r-l+1)*val;
		tag(k)+=val;
		return;
	}
	inline void pushdown(int k,int l,int r){
		if(tag(k)){
			add(lson,l,mid,tag(k));
			add(rson,mid+1,r,tag(k));
			tag(k)=0;
		}
		return;
	}
	inline void update(int k,int l,int r,int L,int R,int val){
		if(L<=l&&r<=R){
			add(k,l,r,val);
			return;
		}
		pushdown(k,l,r);
		if(L<=mid)
			update(lson,l,mid,L,R,val);
		if(R>mid)
			update(rson,mid+1,r,L,R,val);
		pushup(k);
		return;
	}
	inline ll query(int k,int l,int r,int L,int R){
		if(L<=l&&r<=R)
			return sum(k);
		pushdown(k,l,r);
		ll res=0;
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

using namespace SegmentTree;

int main(void){
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;++i)
		scanf("%d",&a[i]);
	build(1,1,n,a);
	while(m--){
		static char opt;
		static int l,r,d;
		cin>>opt>>l>>r;
		switch(opt){
			case 'C':{
				scanf("%d",&d);
				update(1,1,n,l,r,d);
				break;
			}
			case 'Q':{
				printf("%lld\n",query(1,1,n,l,r));
				break;
			}
		}
	}
	return 0;
}