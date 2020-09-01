#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

const int MAXN=1e5+5;

int n,m,p;

namespace SegmentTree{
	#define lson ( (k) << 1 )
	#define rson ( (k) << 1 | 1 )
	#define mid ( ( (l) + (r) ) >> 1 )
	struct Node{
		int sum,tagA,tagM;
		#define sum(x) unit[(x)].sum
		#define tagA(x) unit[(x)].tagA
		#define tagM(x) unit[(x)].tagM
	};
	Node unit[MAXN<<2];
	inline void pushup(int k){
		sum(k)=(sum(lson)+sum(rson))%p;
		return;
	}
	inline void build(int k,int l,int r,int a[]){
		tagA(k)=0,tagM(k)=1;
		if(l==r){
			sum(k)=a[l];
			return;
		}
		build(lson,l,mid,a),build(rson,mid+1,r,a);
		pushup(k);
		return;
	}
	inline void Add(int k,int l,int r,int val){
		sum(k)=(sum(k)+1ll*val*(r-l+1)%p)%p;
		tagA(k)=(tagA(k)+val)%p;
		return;
	}
	inline void Mul(int k,int val){
		sum(k)=1ll*sum(k)*val%p;
		tagA(k)=1ll*tagA(k)*val%p;
		tagM(k)=1ll*tagM(k)*val%p;
		return;
	}
	inline void pushdown(int k,int l,int r){
		if(tagM(k)!=1){
			Mul(lson,tagM(k));
			Mul(rson,tagM(k));
			tagM(k)=1;
		}
		if(tagA(k)){
			Add(lson,l,mid,tagA(k));
			Add(rson,mid+1,r,tagA(k));
			tagA(k)=0;
		}
		return;
	}
	inline void updateMul(int k,int l,int r,int L,int R,int val){
		if(L<=l&&r<=R){
			Mul(k,val);
			return;
		}
		pushdown(k,l,r);
		if(L<=mid)
			updateMul(lson,l,mid,L,R,val);
		if(R>mid)
			updateMul(rson,mid+1,r,L,R,val);
		pushup(k);
		return;
	}
	inline void updateAdd(int k,int l,int r,int L,int R,int val){
		if(L<=l&&r<=R){
			Add(k,l,r,val);
			return;
		}
		pushdown(k,l,r);
		if(L<=mid)
			updateAdd(lson,l,mid,L,R,val);
		if(R>mid)
			updateAdd(rson,mid+1,r,L,R,val);
		pushup(k);
		return;
	}
	inline int query(int k,int l,int r,int L,int R){
		if(L<=l&&r<=R)
			return sum(k);
		pushdown(k,l,r);
		int res=0;
		if(L<=mid)
			res=(res+query(lson,l,mid,L,R))%p;
		if(R>mid)
			res=(res+query(rson,mid+1,r,L,R))%p;
		return res;
	}
	#undef lson
	#undef rson
	#undef mid
}

int a[MAXN];

int main(void){
	scanf("%d%d",&n,&p);
	for(int i=1;i<=n;++i)
		scanf("%d",&a[i]),a[i]%=p;
	SegmentTree::build(1,1,n,a);
	scanf("%d",&m);
	while(m--){
		static int opt,t,g,c;
		scanf("%d%d%d",&opt,&t,&g);
		switch(opt){
			case 1:{
				scanf("%d",&c);
				c%=p;
				SegmentTree::updateMul(1,1,n,t,g,c);
				break;
			}
			case 2:{
				scanf("%d",&c);
				c%=p;
				SegmentTree::updateAdd(1,1,n,t,g,c);
				break;
			}
			case 3:{
				printf("%d\n",SegmentTree::query(1,1,n,t,g));
				break;
			}
		}
	}
	return 0;
}