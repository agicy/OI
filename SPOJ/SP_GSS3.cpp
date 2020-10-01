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

const int MAXN=5e4+5;

int n,q;
int a[MAXN];

namespace SegmentTree{
	#define lson ( (k) << 1 )
	#define rson ( (k) << 1 | 1 )
	#define mid ( ( (l) + (r) ) >> 1 )
	struct Node{
		int sum,lMax,rMax,Max;
		inline Node operator+(const Node& a)const{
			Node res;
			res.sum=sum+a.sum;
			res.lMax=max(lMax,sum+a.lMax);
			res.rMax=max(a.rMax,a.sum+rMax);
			res.Max=max(max(Max,a.Max),rMax+a.lMax);
			return res;
		}
		#define sum(x) unit[(x)].sum
		#define lMax(x) unit[(x)].lMax
		#define rMax(x) unit[(x)].rMax
		#define Max(x) unit[(x)].Max
	};
	Node unit[MAXN<<2];
	inline void pushup(reg int k){
		unit[k]=unit[lson]+unit[rson];
		return;
	}
	inline void build(reg int k,reg int l,reg int r,reg int a[]){
		if(l==r){
			sum(k)=lMax(k)=rMax(k)=Max(k)=a[l];
			return;
		}
		build(lson,l,mid,a),build(rson,mid+1,r,a);
		pushup(k);
		return;
	}
	inline void update(reg int k,reg int l,reg int r,reg int pos,reg int val){
		if(l==r){
			sum(k)=lMax(k)=rMax(k)=Max(k)=val;
			return;
		}
		if(pos<=mid)
			update(lson,l,mid,pos,val);
		else
			update(rson,mid+1,r,pos,val);
		pushup(k);
		return;
	}
	inline Node query(reg int k,reg int l,reg int r,reg int L,reg int R){
		if(L<=l&&r<=R)
			return unit[k];
		if(L<=mid&&mid<R){
			Node left=query(lson,l,mid,L,R),right=query(rson,mid+1,r,L,R);
			return left+right;
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

int main(void){
	n=read();
	for(reg int i=1;i<=n;++i)
		a[i]=read();
	SegmentTree::build(1,1,n,a);
	q=read();
	while(q--){
		static int opt,x,y;
		opt=read(),x=read(),y=read();
		switch(opt){
			case 0:{
				SegmentTree::update(1,1,n,x,y);
				break;
			}
			case 1:{
				SegmentTree::Node ans=SegmentTree::query(1,1,n,x,y);
				printf("%d\n",ans.Max);
				break;
			}
		}
	}
	return 0;
}