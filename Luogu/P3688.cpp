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
const int mod=998244353;

inline int add(reg int a,reg int b){
	a+=b;
	return a>=mod?a-mod:a;
}

inline int sub(reg int a,reg int b){
	a-=b;
	return a<0?a+mod:a;
}

inline int fpow(reg int x,reg int exp){
	reg int res=1;
	while(exp){
		if(exp&1)
			res=1ll*res*x%mod;
		x=1ll*x*x%mod;
		exp>>=1;
	}
	return res;
}

inline int mul(reg int p,reg int q){
	return add(1ll*p*q%mod,1ll*sub(p,1)*sub(q,1)%mod);
}

int n,m;

namespace SegmentTree{
	namespace SegmentTree{
		const int MAXSIZE=MAXN*400;
		#define mid ( ( (l) + (r) ) >> 1 )
		struct Node{
			int lson,rson;
			int val;
			#define lson(x) unit[(x)].lson
			#define rson(x) unit[(x)].rson
			#define val(x) unit[(x)].val
		};
		int tot;
		Node unit[MAXSIZE];
		inline void update(reg int &k,reg int l,reg int r,reg int L,reg int R,reg int p){
			if(!k){
				k=++tot;
				val(k)=1;
			}
			if(L<=l&&r<=R){
				val(k)=mul(val(k),p);
				return;
			}
			if(L<=mid)
				update(lson(k),l,mid,L,R,p);
			if(R>mid)
				update(rson(k),mid+1,r,L,R,p);
			return;
		}
		inline int query(reg int k,reg int l,reg int r,reg int pos){
			if(!k)
				return 1;
			if(l==r)
				return val(k);
			if(pos<=mid)
				return mul(val(k),query(lson(k),l,mid,pos));
			else
				return mul(val(k),query(rson(k),mid+1,r,pos));
		}
		#undef mid
		#undef lson
		#undef rson
		#undef mid
	}
	#define lson ( (k) << 1 )
	#define rson ( (k) << 1 | 1 )
	#define mid ( ( (l) + (r) ) >> 1 )
	int rt[MAXN<<2];
	inline void update(reg int k,reg int l,reg int r,reg int Lx,reg int Rx,reg int Ly,reg int Ry,reg int p){
		if(Lx<=l&&r<=Rx){
			SegmentTree::update(rt[k],1,n,Ly,Ry,p);
			return;
		}
		if(Lx<=mid)
			update(lson,l,mid,Lx,Rx,Ly,Ry,p);
		if(Rx>mid)
			update(rson,mid+1,r,Lx,Rx,Ly,Ry,p);
		return;
	}
	inline int query(reg int k,reg int l,reg int r,reg int posx,reg int posy){
		if(l==r)
			return SegmentTree::query(rt[k],1,n,posy);
		if(posx<=mid)
			return mul(query(lson,l,mid,posx,posy),SegmentTree::query(rt[k],1,n,posy));
		else
			return mul(query(rson,mid+1,r,posx,posy),SegmentTree::query(rt[k],1,n,posy));
	}
	#undef mid
}

int main(void){
	n=read(),m=read();
	while(m--){
		static int opt,l,r;
		opt=read(),l=read(),r=read();
		switch(opt){
			case 1:{
				reg int p=fpow(r-l+1,mod-2);
				if(l>1)
					SegmentTree::update(1,0,n,1,l-1,l,r,sub(1,p)),SegmentTree::update(1,0,n,0,0,1,l-1,0);
				if(r<n)
					SegmentTree::update(1,0,n,l,r,r+1,n,sub(1,p)),SegmentTree::update(1,0,n,0,0,r+1,n,0);
				SegmentTree::update(1,0,n,l,r,l,r,sub(1,add(p,p))),SegmentTree::update(1,0,n,0,0,l,r,p);
				break;
			}
			case 2:{
				printf("%d\n",SegmentTree::query(1,0,n,l-1,r));
				break;
			}
		}
	}
	return 0;
}