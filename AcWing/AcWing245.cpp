#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

const int MAXN=5e5+5;

namespace SegmentTree{
	#define lson ( (k) << 1 )
	#define rson ( (k) << 1 | 1 )
	#define mid ( ( (l) + (r) ) >> 1 )
	struct Node{
		ll sum,lMax,rMax,Max;
	};
	Node unit[MAXN<<2];
	inline Node combine(const Node& left,const Node& right){
		Node res;
		res.sum=left.sum+right.sum;
		res.lMax=max(left.lMax,right.lMax+left.sum);
		res.rMax=max(right.rMax,left.rMax+right.sum);
		res.Max=max(max(left.Max,right.Max),left.rMax+right.lMax);
		return res;
	}
	inline void pushup(int k){
		unit[k]=combine(unit[lson],unit[rson]);
		return;
	}
	inline void build(int k,int l,int r,ll a[]){
		if(l==r){
			unit[k].sum=unit[k].lMax=unit[k].rMax=unit[k].Max=a[l];
			return;
		}
		build(lson,l,mid,a),build(rson,mid+1,r,a);
		pushup(k);
		return;
	}
	inline void update(int k,int l,int r,int pos,ll val){
		if(l==r){
			unit[k].sum=unit[k].lMax=unit[k].rMax=unit[k].Max=val;
			return;
		}
		if(pos<=mid)
			update(lson,l,mid,pos,val);
		else
			update(rson,mid+1,r,pos,val);
		pushup(k);
		return;
	}
	inline Node query(int k,int l,int r,int L,int R){
		if(L<=l&&r<=R)
			return unit[k];
		if(L<=mid&&mid<R){
			Node left=query(lson,l,mid,L,R),right=query(rson,mid+1,r,L,R);
			return combine(left,right);
		}
		else if(L<=mid)
			return query(lson,l,mid,L,R);
		else
			return query(rson,mid+1,r,L,R);
	}
	#undef lson
	#undef rson
	#undef mid
}

int n,m;
ll a[MAXN];

int main(void){
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;++i)
		scanf("%lld",&a[i]);
	SegmentTree::build(1,1,n,a);
	while(m--){
		static int k,x,y;
		scanf("%d%d%d",&k,&x,&y);
		switch(k){
			case 1:{
				if(x>y)
					swap(x,y);
				ll ans=SegmentTree::query(1,1,n,x,y).Max;
				printf("%lld\n",ans);
				break;
			}
			case 2:{
				SegmentTree::update(1,1,n,x,y);
				break;
			}
		}
	}
	return 0;
}