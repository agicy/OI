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
	while(isdigit(ch))res=10*res+ch-'0',ch=getchar();
	return res;
}

const int MAXN=1e5+5;
const int MAXM=1e5+5;

namespace SegmentTree{
	#define lson ( (k) << 1 )
	#define rson ( (k) << 1 | 1 )
	#define mid ( ( (l) + (r) ) >> 1 )
	struct Node{
		int sum,tag;
		#define sum(x) unit[(x)].sum
		#define tag(x) unit[(x)].tag
	};
	Node unit[MAXN<<2];
	inline void pushup(reg int k){
		sum(k)=sum(lson)&sum(rson);
		return;
	}
	inline void Or(reg int k,reg int val){
		sum(k)|=val,tag(k)|=val;
		return;
	}
	inline void pushdown(reg int k){
		if(tag(k)){
			Or(lson,tag(k));
			Or(rson,tag(k));
			tag(k)=0;
		}
		return;
	}
	inline void update(reg int k,reg int l,reg int r,reg int L,reg int R,reg int val){
		if(L<=l&&r<=R){
			Or(k,val);
			return;
		}
		pushdown(k);
		if(L<=mid)
			update(lson,l,mid,L,R,val);
		if(R>mid)
			update(rson,mid+1,r,L,R,val);
		pushup(k);
		return;
	}
	inline int query(reg int k,reg int l,reg int r,reg int L,reg int R){
		if(L<=l&&r<=R)
			return sum(k);
		pushdown(k);
		if(L<=mid&&mid<R)
			return query(lson,l,mid,L,R)&query(rson,mid+1,r,L,R);
		else if(L<=mid)
			return query(lson,l,mid,L,R);
		else
			return query(rson,mid+1,r,L,R);
	}
	inline void print(reg int k,reg int l,reg int r){
		if(l==r){
			printf("%d ",sum(k));
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

int n,m;
int l[MAXM],r[MAXM],q[MAXM];

int main(void){
	n=read(),m=read();
	for(reg int i=1;i<=m;++i){
		l[i]=read(),r[i]=read(),q[i]=read();
		SegmentTree::update(1,1,n,l[i],r[i],q[i]);
	}
	for(reg int i=1;i<=m;++i)
		if(SegmentTree::query(1,1,n,l[i],r[i])!=q[i])
			puts("NO"),exit(0);
	puts("YES");
	SegmentTree::print(1,1,n);
	putchar('\n');
	return 0;
}