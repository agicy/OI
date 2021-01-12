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
		ll sum;
		int Max;
		#define sum(x) unit[(x)].sum
		#define Max(x) unit[(x)].Max
	};
	Node unit[MAXN<<2];
	inline void pushup(reg int k){
		sum(k)=sum(lson)+sum(rson);
		Max(k)=max(Max(lson),Max(rson));
		return;
	}
	inline void build(reg int k,reg int l,reg int r,reg int a[]){
		if(l==r){
			sum(k)=Max(k)=a[l];
			return;
		}
		build(lson,l,mid,a),build(rson,mid+1,r,a);
		pushup(k);
		return;
	}
	inline void update(reg int k,reg int l,reg int r,reg int L,reg int R,reg int val){
		if(Max(k)<val)
			return;
		if(l==r){
			sum(k)%=val,Max(k)%=val;
			return;
		}
		if(L<=mid&&mid<R)
			update(lson,l,mid,L,R,val),update(rson,mid+1,r,L,R,val);
		else if(L<=mid)
			update(lson,l,mid,L,R,val);
		else
			update(rson,mid+1,r,L,R,val);
		pushup(k);
		return;
	}
	inline void update(reg int k,reg int l,reg int r,reg int pos,reg int val){
		if(l==r){
			sum(k)=Max(k)=val;
			return;
		}
		if(pos<=mid)
			update(lson,l,mid,pos,val);
		else
			update(rson,mid+1,r,pos,val);
		pushup(k);
		return;
	}
	inline ll query(reg int k,reg int l,reg int r,reg int L,reg int R){
		if(L<=l&&r<=R)
			return sum(k);
		if(L<=mid&&mid<R)
			return query(lson,l,mid,L,R)+query(rson,mid+1,r,L,R);
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
	n=read(),m=read();
	for(reg int i=1;i<=n;++i)
		a[i]=read();
	SegmentTree::build(1,1,n,a);
	while(m--){
		static int type,l,r,x,k;
		type=read();
		switch(type){
			case 1:{
				l=read(),r=read();
				printf("%lld\n",SegmentTree::query(1,1,n,l,r));
				break;
			}
			case 2:{
				l=read(),r=read(),x=read();
				SegmentTree::update(1,1,n,l,r,x);
				break;
			}
			case 3:{
				k=read(),x=read();
				SegmentTree::update(1,1,n,k,x);
				break;
			}
		}
	}
	return 0;
}