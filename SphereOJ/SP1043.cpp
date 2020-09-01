#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

const int MAXN=5e4+5;

namespace SegmentTree{
	#define lson ( (k) << 1 )
	#define rson ( (k) << 1 | 1 )
	#define mid ( ( (l) + (r) ) >> 1 )
	struct Node{
		int sum;
		int lMax,rMax,Max;
		#define sum(x) unit[(x)].sum
		#define lMax(x) unit[(x)].lMax
		#define rMax(x) unit[(x)].rMax
		#define Max(x) unit[(x)].Max
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
	inline void build(int k,int l,int r,int a[]){
		if(l==r){
			sum(k)=lMax(k)=rMax(k)=Max(k)=a[l];
			return;
		}
		build(lson,l,mid,a),build(rson,mid+1,r,a);
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
int a[MAXN];

int main(void){
	scanf("%d",&n);
	for(int i=1;i<=n;++i)
		scanf("%d",&a[i]);
	scanf("%d",&m);
	SegmentTree::build(1,1,n,a);
	while(m--){
		static int x,y;
		scanf("%d%d",&x,&y);
		printf("%d\n",SegmentTree::query(1,1,n,x,y).Max);
	}
	return 0;
}