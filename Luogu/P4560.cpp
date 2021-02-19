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

const int MAXN=2e6+5;
const int inf=0x3f3f3f3f;

namespace SegmentTree{
	#define lson ( (k) << 1 )
	#define rson ( (k) << 1 | 1 )
	#define mid ( ( (l) + (r) ) >> 1 )
	struct Node{
		int Max,Min;
		#define Max(x) unit[(x)].Max
		#define Min(x) unit[(x)].Min
	};
	Node unit[MAXN<<2];
	inline void build(reg int k,reg int l,reg int r){
		Max(k)=0,Min(k)=inf;
		if(l==r)
			return;
		build(lson,l,mid),build(rson,mid+1,r);
		return;
	}
	inline void cMax(reg int k,reg int val){
		if(Min(k)<val)
			Min(k)=val;
		if(Max(k)<val)
			Max(k)=val;
		return;
	}
	inline void cMin(reg int k,reg int val){
		if(Max(k)>val)
			Max(k)=val;
		if(Min(k)>val)
			Min(k)=val;
		return;
	}
	inline void pushdown(reg int k){
		if(Max(k)!=0){
			cMax(lson,Max(k)),cMax(rson,Max(k));
			Max(k)=0;
		}
		if(Min(k)!=inf){
			cMin(lson,Min(k)),cMin(rson,Min(k));
			Min(k)=inf;
		}
		return;
	}
	inline void updateMax(reg int k,reg int l,reg int r,reg int L,reg int R,reg int val){
		if(L<=l&&r<=R){
			cMax(k,val);
			return;
		}
		pushdown(k);
		if(L<=mid)
			updateMax(lson,l,mid,L,R,val);
		if(R>mid)
			updateMax(rson,mid+1,r,L,R,val);
		return;
	}
	inline void updateMin(reg int k,reg int l,reg int r,reg int L,reg int R,reg int val){
		if(L<=l&&r<=R){
			cMin(k,val);
			return;
		}
		pushdown(k);
		if(L<=mid)
			updateMin(lson,l,mid,L,R,val);
		if(R>mid)
			updateMin(rson,mid+1,r,L,R,val);
		return;
	}
	inline void print(reg int k,reg int l,reg int r){
		if(l==r){
			printf("%d\n",Max(k));
			return;
		}
		pushdown(k);
		print(lson,l,mid),print(rson,mid+1,r);
		return;
	}
	#undef lson
	#undef rson
	#undef mid
}

int n,k;

int main(void){
	n=read(),k=read();
	SegmentTree::build(1,1,n);
	while(k--){
		static int t,L,R,h;
		t=read(),L=read()+1,R=read()+1,h=read();
		switch(t){
			case 1:{
				SegmentTree::updateMax(1,1,n,L,R,h);
				break;
			}
			case 2:{
				SegmentTree::updateMin(1,1,n,L,R,h);
				break;
			}
		}
	}
	SegmentTree::print(1,1,n);
	return 0;
}