#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++)
static char buf[100000],*p1=buf,*p2=buf;
inline ll read(void){
	reg char ch=getchar();
	reg ll res=0;
	while(ch<'0'||'9'<ch)ch=getchar();
	while('0'<=ch&&ch<='9')res=10ll*res+ch-'0',ch=getchar();
	return res;
}

const int MAXN=50000+5;

int n,m;

namespace SegmentTree{
	#define lson ( (k) << 1 )
	#define rson ( (k) << 1 | 1 )
	#define mid ( ( (l) + (r) ) >> 1 )
	struct Node{
		int sum,lsum,rsum;
		int tag;
		#define sum(x) unit[(x)].sum
		#define lsum(x) unit[(x)].lsum
		#define rsum(x) unit[(x)].rsum
		#define tag(x) unit[(x)].tag
	};
	Node unit[MAXN<<2];
	inline void pushup(reg int k,reg int l,reg int r){
		sum(k)=max(max(sum(lson),sum(rson)),rsum(lson)+lsum(rson));
		if(lsum(lson)==mid-l+1)
			lsum(k)=lsum(lson)+lsum(rson);
		else
			lsum(k)=lsum(lson);
		if(rsum(rson)==r-mid)
			rsum(k)=rsum(rson)+rsum(lson);
		else
			rsum(k)=rsum(rson);
		return;
	}
	inline void build(reg int k,reg int l,reg int r){
		if(l==r){
			sum(k)=lsum(k)=rsum(k)=1;
			return;
		}
		build(lson,l,mid),build(rson,mid+1,r);
		pushup(k,l,r);
		return;
	}
	inline void empty(reg int k,reg int l,reg int r){
		tag(k)=-1;
		sum(k)=lsum(k)=rsum(k)=r-l+1;
		return;
	}
	inline void fill(reg int k){
		tag(k)=1;
		sum(k)=lsum(k)=rsum(k)=0;
		return;
	}
	inline void pushdown(reg int k,reg int l,reg int r){
		if(tag(k)==-1){
			empty(lson,l,mid),empty(rson,mid+1,r);
			tag(k)=0;
		}
		else if(tag(k)==1){
			fill(lson),fill(rson);
			tag(k)=0;
		}
		return;
	}
	inline void Update0(reg int k,reg int l,reg int r,reg int L,reg int R){
		if(L<=l&&r<=R){
			empty(k,l,r);
			return;
		}
		pushdown(k,l,r);
		if(L<=mid)
			Update0(lson,l,mid,L,R);
		if(R>mid)
			Update0(rson,mid+1,r,L,R);
		pushup(k,l,r);
		return;
	}
	inline void Update1(reg int k,reg int l,reg int r,reg int L,reg int R){
		if(L<=l&&r<=R){
			fill(k);
			return;
		}
		pushdown(k,l,r);
		if(L<=mid)
			Update1(lson,l,mid,L,R);
		if(R>mid)
			Update1(rson,mid+1,r,L,R);
		pushup(k,l,r);
		return;
	}
	inline int query(reg int k,reg int l,reg int r,reg int v){
		if(v>sum(k))
			return 0;
		pushdown(k,l,r);
		if(v<=lsum(k))
			return l;
		else if(v<=sum(lson))
			return query(lson,l,mid,v);
		else if(v<=rsum(lson)+lsum(rson))
			return mid-rsum(lson)+1;
		else
			return query(rson,mid+1,r,v);
	}
}

int main(void){
	n=read(),m=read();
	SegmentTree::build(1,1,n);
	while(m--){
		static int opt,x,d;
		opt=read();
		switch(opt){
			case 1:{
				d=read();
				reg int tmp=SegmentTree::query(1,1,n,d);
				if(tmp!=0)
					SegmentTree::Update1(1,1,n,tmp,tmp+d-1);
				printf("%d\n", tmp);
				break;
			}
			case 2:{
				x=read(),d=read();
				SegmentTree::Update0(1,1,n,x,x+d-1);
				break;
			}
		}
	}
	return 0;
}