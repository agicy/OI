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

const int MAXN=1e5+5;

namespace SegmentTree{
	#define lson ( (k) << 1 )
	#define rson ( (k) << 1 | 1 )
	#define mid ( ( (l) + (r) ) >> 1 )
	struct Node{
		int val,tag;
		#define val(x) unit[(x)].val
		#define tag(x) unit[(x)].tag
	};
	Node unit[MAXN<<2];
	inline void pushup(reg int k){
		val(k)=val(lson)|val(rson);
		return;
	}
	inline void build(reg int k,reg int l,reg int r){
		if(l==r){
			val(k)=1;
			return;
		}
		build(lson,l,mid),build(rson,mid+1,r);
		pushup(k);
		return;
	}
	inline void set(reg int k,reg int x){
		val(k)=tag(k)=x;
		return;
	}
	inline void pushdown(reg int k){
		if(tag(k)){
			set(lson,tag(k));
			set(rson,tag(k));
			tag(k)=0;
		}
		return;
	}
	inline void update(reg int k,reg int l,reg int r,reg int L,reg int R,reg int Val){
		if(L<=l&&r<=R){
			set(k,Val);
			return;
		}
		pushdown(k);
		if(L<=mid)
			update(lson,l,mid,L,R,Val);
		if(R>mid)
			update(rson,mid+1,r,L,R,Val);
		pushup(k);
		return;
	}
	inline int query(reg int k,reg int l,reg int r,reg int L,reg int R){
		if(L<=l&&r<=R)
			return val(k);
		pushdown(k);
		reg int res=0;
		if(L<=mid)
			res|=query(lson,l,mid,L,R);
		if(R>mid)
			res|=query(rson,mid+1,r,L,R);
		return res;
	}
	#undef lson
	#undef rson
	#undef mid
}

int n,m,k;

inline int getCnt(reg int x){
	reg int res=0;
	for(reg int i=0;i<k;++i)
		if((x>>i)&1)
			++res;
	return res;
}

int main(void){
	n=read(),m=read(),k=read();
	SegmentTree::build(1,1,n);
	while(m--){
		static char opt;
		static int l,r,x;
		do
			opt=getchar();
		while(opt!='C'&&opt!='P');
		switch(opt){
			case 'C':{
				l=read(),r=read(),x=read();
				SegmentTree::update(1,1,n,l,r,1<<(x-1));
				break;
			}
			case 'P':{
				l=read(),r=read();
				printf("%d\n",getCnt(SegmentTree::query(1,1,n,l,r)));
				break;
			}
		}
	}
	return 0;
}