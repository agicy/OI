#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
#define getchar()(p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++)
static char buf[100000],*p1=buf,*p2=buf;
inline int read(void){
	bool f=false;
	char ch=getchar();
	int res=0;
	while(!isdigit(ch))f|=(ch=='-'),ch=getchar();
	while(isdigit(ch))res=10*res+ch-'0',ch=getchar();
	return f?-res:res;
}

const int MAXN=2e5+5;
const int p=998244353;
const int inf=0x3f3f3f3f;

inline int add(int a,int b){
	int sum=a+b;
	return sum>=p?sum-p:sum;
}

namespace SegmentTree{
	#define lson ( (k) << 1 )
	#define rson ( (k) << 1 | 1 )
	#define mid ( ( (l) + (r) ) >> 1 )
	int T[MAXN<<2];
	struct Node{
		int Max,cMax,sum;
		inline Node(int Max=0,int cMax=0,int sum=0):Max(Max),cMax(cMax),sum(sum){
			return;
		}
		#define Max(x) unit[(x)].Max
		#define cMax(x) unit[(x)].cMax
		#define sum(x) unit[(x)].sum
	};
	#define tag(x) T[x]
	Node unit[MAXN<<2];
	inline Node merge(Node a,Node b){
		if(a.Max==b.Max){
			a.cMax=max(a.cMax,b.cMax);
			a.sum=add(a.sum,b.sum);
		}
		else{
			if(a.Max<b.Max)
				swap(a,b);
			a.cMax=max(a.cMax,b.Max);
		}
		return a;
	}
	inline void pushup(int k){
		unit[k]=merge(unit[lson],unit[rson]);
		return;
	}
	inline void build(int k,int l,int r){
		tag(k)=inf;
		if(l==r)
			return;
		build(lson,l,mid),build(rson,mid+1,r);
		return;
	}
	inline void getMin(int k,int val){
		Max(k)=min(Max(k),val);
		tag(k)=min(tag(k),val);
		return;
	}
	inline void pushdown(int k){
		if(tag(k)<inf){
			getMin(lson,tag(k));
			getMin(rson,tag(k));
			tag(k)=inf;
		}
		return;
	}
	inline void update(int k,int l,int r,int pos,int val){
		if(l==r){
			Max(k)=inf,sum(k)=val;
			return;
		}
		pushdown(k);
		if(pos<=mid)
			update(lson,l,mid,pos,val);
		else
			update(rson,mid+1,r,pos,val);
		pushup(k);
		return;
	}
	inline void update(int k,int l,int r,int L,int R,int val){
		if(L<=l&&r<=R&&val>cMax(k)){
			getMin(k,val);
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
	inline Node query(int k,int l,int r,int L,int R){
		if(L<=l&&r<=R)
			return unit[k];
		pushdown(k);
		if(L<=mid&&mid<R){
			Node lef=query(lson,l,mid,L,R),rig=query(rson,mid+1,r,L,R);
			return merge(lef,rig);
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

int n;
int f[MAXN];

int main(void){
	n=read();
	SegmentTree::build(1,1,n);
	for(int i=1;i<=n;++i){
		static int v;
		static SegmentTree::Node res;
		v=read();
		SegmentTree::update(1,1,n,1,v,v);
		res=SegmentTree::query(1,1,n,1,v);
		int x=(res.Max==v)?res.sum:0;
		if(!x)x=1;
		SegmentTree::update(1,1,n,v,x);
	}
	printf("%d\n",SegmentTree::unit[1].sum);
	return 0;
}