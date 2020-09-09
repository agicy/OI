#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++)
static char buf[100000],*p1=buf,*p2=buf;
inline int read(void){
	reg bool f=false;
	reg char ch=getchar();
	reg int res=0;
	while(ch<'0'||'9'<ch)f|=(ch=='-'),ch=getchar();
	while('0'<=ch&&ch<='9')res=10*res+ch-'0',ch=getchar();
	return f?-res:res;
}

const int MAXM=2e5+5;

struct Operation{
	int k,v;
	inline Operation(reg int k=0,reg int v=0):k(k),v(v){
		return;
	}
	inline void Read(void){
		k=read(),v=read();
		return;
	}
};

namespace SegmentTree{
	#define lson ( (k) << 1 )
	#define rson ( (k) << 1 | 1 )
	#define mid ( ( (l) + (r) ) >> 1 )
	struct Node{
		int add,del;
		int sum;
		#define add(x) unit[(x)].add
		#define del(x) unit[(x)].del
		#define sum(x) unit[(x)].sum
	};
	Node unit[MAXM<<2];
	inline int query(reg int k,reg int val){
		if(add(k)<=val)
			return 0;
		if(add(rson)>=val)
			return sum(k)-sum(rson)+query(rson,val);
		else
			return query(lson,val-add(rson)+del(rson));
	}
	inline void pushup(reg int k){
		del(k)=del(lson)+max(del(rson)-add(lson),0);
		add(k)=max(add(lson)-del(rson),0)+add(rson);
		sum(k)=sum(rson)+(del(rson)?query(lson,del(rson)):sum(lson));
		return;
	}
	inline void build(reg int k,reg int l,reg int r,reg Operation a[]){
		if(l==r){
			if(a[l].k==1)
				del(k)=a[l].v,add(k)=sum(k)=0;
			else
				del(k)=0,add(k)=1,sum(k)=a[l].v;
			return;
		}
		build(lson,l,mid,a),build(rson,mid+1,r,a);
		pushup(k);
		return;
	}
	inline void update(reg int k,reg int l,reg int r,reg int pos,reg int K,reg int V){
		if(l==r){
			if(K==1)
				del(k)=V,add(k)=sum(k)=0;
			else
				del(k)=0,add(k)=1,sum(k)=V;
			return;
		}
		if(pos<=mid)
			update(lson,l,mid,pos,K,V);
		else
			update(rson,mid+1,r,pos,K,V);
		pushup(k);
		return;
	}
	#undef lson
	#undef rson
	#undef mid
}

int m,q;
Operation O[MAXM];

int main(void){
	m=read(),q=read();
	for(reg int i=1;i<=m;++i)
		O[i].Read();
	SegmentTree::build(1,1,m,O);
	while(q--){
		static int c,k,v;
		c=read(),k=read(),v=read();
		SegmentTree::update(1,1,m,c,k,v);
		printf("%d\n",SegmentTree::unit[1].sum);
	}
	return 0;
}