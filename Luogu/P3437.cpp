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

inline int max(reg int a,reg int b){
	return a>b?a:b;
}

const int MAXD=1e3+5;
const int MAXS=1e3+5;

int d,s,n;

namespace SegmentTree{
	namespace SegmentTree{
		const int MAXSIZE=MAXS*4e3;
		#define mid ( ( (l) + (r) ) >> 1 )
		struct Node{
			int lson,rson;
			int Max,tag;
			#define lson(x) unit[(x)].lson
			#define rson(x) unit[(x)].rson
			#define Max(x) unit[(x)].Max
			#define tag(x) unit[(x)].tag
		};
		int tot;
		Node unit[MAXSIZE];
		inline void update(reg int& p,reg int l,reg int r,reg int L,reg int R,reg int val){
			if(!p)
				p=++tot;
			Max(p)=max(Max(p),val);
			if(L<=l&&r<=R){
				tag(p)=max(tag(p),val);
				return;
			}
			if(L<=mid)
				update(lson(p),l,mid,L,R,val);
			if(R>mid)
				update(rson(p),mid+1,r,L,R,val);
			return;
		}
		inline int query(reg int p,reg int l,reg int r,reg int L,reg int R){
			if(!p)
				return 0;
			if(L<=l&&r<=R)
				return Max(p);
			reg int res=tag(p);
			if(L<=mid&&mid<R)
				res=max(res,max(query(lson(p),l,mid,L,R),query(rson(p),mid+1,r,L,R)));
			else if(L<=mid)
				res=max(res,query(lson(p),l,mid,L,R));
			else
				res=max(res,query(rson(p),mid+1,r,L,R));
			return res;
		}
		#undef lson
		#undef rson
		#undef mid
		#undef Max
		#undef tag
	};
	#define lson ( (k) << 1 )
	#define rson ( (k) << 1 | 1 )
	#define mid ( ( (l) + (r) ) >> 1 )
	struct Node{
		int Max,tag;
		#define Max(x) unit[(x)].Max
		#define tag(x) unit[(x)].tag
	};
	Node unit[MAXD<<2];
	inline void update(reg int k,reg int l,reg int r,reg int Lx,reg int Rx,reg int Ly,reg int Ry,reg int val){
		SegmentTree::update(Max(k),0,s,Ly,Ry,val);
		if(Lx<=l&&r<=Rx){
			SegmentTree::update(tag(k),0,s,Ly,Ry,val);
			return;
		}
		if(Lx<=mid)
			update(lson,l,mid,Lx,Rx,Ly,Ry,val);
		if(Rx>mid)
			update(rson,mid+1,r,Lx,Rx,Ly,Ry,val);
		return;
	}
	inline int query(reg int k,reg int l,reg int r,reg int Lx,reg int Rx,reg int Ly,reg int Ry){
		if(Lx<=l&&r<=Rx)
			return SegmentTree::query(Max(k),0,s,Ly,Ry);
		reg int res=SegmentTree::query(tag(k),0,s,Ly,Ry);
		if(Lx<=mid&&mid<Rx)
			res=max(res,max(query(lson,l,mid,Lx,Rx,Ly,Ry),query(rson,mid+1,r,Lx,Rx,Ly,Ry)));
		else if(Lx<=mid)
			res=max(res,query(lson,l,mid,Lx,Rx,Ly,Ry));
		else
			res=max(res,query(rson,mid+1,r,Lx,Rx,Ly,Ry));
		return res;
	}
	#undef lson
	#undef rson
	#undef mid
	#undef Max
	#undef tag
}

int main(void){
	d=read(),s=read(),n=read();
	for(reg int i=1;i<=n;++i){
		static int _d,_s,w,x,y;
		_d=read(),_s=read(),w=read(),x=read(),y=read();
		reg int res=SegmentTree::query(1,0,d,x,x+_d-1,y,y+_s-1);
		SegmentTree::update(1,0,d,x,x+_d-1,y,y+_s-1,res+w);
	}
	printf("%d\n",SegmentTree::query(1,0,d,0,d,0,s));
	return 0;
}