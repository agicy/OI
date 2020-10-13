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

const int MAXN=30;
const int MAXM=5e5+5;

namespace SegmentTree{
	#define lson ( (k) << 1 )
	#define rson ( (k) << 1 | 1 )
	#define mid ( ( (l) + (r) ) >> 1 )
	struct Node{
		int f,l;
		ll k;
		inline Node(reg int f=0,reg int l=0,reg ll k=0):f(f),l(l),k(k){
			return;
		}
		inline Node operator+(const Node& a)const{
			if(l>a.f)
				return Node(f,l-a.f+a.l,((k>>a.f)<<a.l)+a.k);
			else
				return Node(f+a.f-l,a.l,a.k);
		}
	};
	Node unit[MAXM<<2];
	inline void pushup(reg int k){
		unit[k]=unit[lson]+unit[rson];
		return;
	}
	inline void build(reg int k,reg int l,reg int r,reg int a[]){
		if(l==r){
			switch(a[l]){
				case 1:{
					unit[k]=Node(0,1,0);
					break;
				}
				case 2:{
					unit[k]=Node(0,1,1);
					break;
				}
				case 3:{
					unit[k]=Node(1,0,0);
					break;
				}
			}
			return;
		}
		build(lson,l,mid,a),build(rson,mid+1,r,a);
		pushup(k);
		return;
	}
	inline void update(reg int k,reg int l,reg int r,reg int pos,reg int val){
		if(l==r){
			switch(val){
				case 1:{
					unit[k]=Node(0,1,0);
					break;
				}
				case 2:{
					unit[k]=Node(0,1,1);
					break;
				}
				case 3:{
					unit[k]=Node(1,0,0);
					break;
				}
			}
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
		if(L<=mid&&mid<R)
			return query(lson,l,mid,L,R)+query(rson,mid+1,r,L,R);
		else if(L<=mid)
			return query(lson,l,mid,L,R);
		else
			return query(rson,mid+1,r,L,R);
	}
}

int n,m,q;
int op[MAXM];

int main(void){
	n=read(),m=read(),q=read();
	for(reg int i=1;i<=m;++i)
		op[i]=read();
	SegmentTree::build(1,1,m,op);
	while(q--){
		static int type,l,r,x,y;
		static ll s;
		type=read();
		switch(type){
			case 1:{
				s=read(),l=read(),r=read();
				SegmentTree::Node ans=SegmentTree::query(1,1,m,l,r);
				printf("%lld\n",(max(1ll,s>>ans.f)<<ans.l)+ans.k);
				break;
			}
			case 2:{
				x=read(),y=read();
				SegmentTree::update(1,1,m,x,y);
				break;
			}
		}
	}
	return 0;
}