#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;

const int MAXM=2e5+5;
const int inf=0x3f3f3f3f;

int m,p;

namespace SegmentTree{
	#define lson ( (k) << 1 )
	#define rson ( (k) << 1 | 1 )
	#define mid ( ( (l) + (r) ) >> 1 )
	struct Node{
		int Max;
		#define Max(x) unit[(x)].Max
	};
	Node unit[MAXM<<2];
	inline void pushup(reg int k){
		Max(k)=max(Max(lson),Max(rson));
		return;
	}
	inline void build(reg int k,reg int l,reg int r){
		if(l==r){
			Max(k)=-inf;
			return;
		}
		build(lson,l,mid),build(rson,mid+1,r);
		pushup(k);
		return;
	}
	inline void update(reg int k,reg int l,reg int r,reg int pos,reg int val){
		if(l==r){
			Max(k)=val;
			return;
		}
		if(pos<=mid)
			update(lson,l,mid,pos,val);
		else
			update(rson,mid+1,r,pos,val);
		pushup(k);
		return;
	}
	inline int query(reg int k,reg int l,reg int r,reg int L,reg int R){
		if(L<=l&&r<=R)
			return Max(k);
		int res=-inf;
		if(L<=mid)
			res=max(res,query(lson,l,mid,L,R));
		if(R>mid)
			res=max(res,query(rson,mid+1,r,L,R));
		return res;
	}
	#undef lson
	#undef rson
	#undef mid
}

int main(void){
	scanf("%d%d",&m,&p);
	reg int lastans=0;
	reg int tot=0;
	SegmentTree::build(1,1,m);
	for(reg int i=1;i<=m;++i){
		static char ch;
		static int x;
		do
			ch=getchar();
		while(ch!='Q'&&ch!='A');
		scanf("%d",&x);
		switch(ch){
			case 'A':{
				reg int tmp=(x+lastans)%p;
				SegmentTree::update(1,1,m,++tot,tmp);
				break;
			}
			case 'Q':{
				lastans=SegmentTree::query(1,1,m,tot-x+1,tot);
				printf("%d\n",lastans);
				break;
			}
			default:break;
		}
	}
	return 0;
}