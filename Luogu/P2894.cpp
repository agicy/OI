#include<bits/stdc++.h>
using namespace std;
#define reg register
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

const int MAXN=50000+5;

struct SegmentTree{
	#define lson ( (k) << 1 )
	#define rson ( (k) << 1 | 1 )
	#define mid ( ( (l) + (r) ) >> 1 )
	struct Node{
		int Max,lMax,rMax;
		int len;
		int tag;
	};
	Node unit[MAXN<<3];
	inline void pushup(reg int k){
		if(unit[lson].Max==unit[lson].len)
			unit[k].lMax=unit[lson].len+unit[rson].lMax;
		else
			unit[k].lMax=unit[lson].lMax;
		if(unit[rson].Max==unit[rson].len)
			unit[k].rMax=unit[rson].len+unit[lson].rMax;
		else
			unit[k].rMax=unit[rson].rMax;
		unit[k].Max=max(max(unit[lson].Max,unit[rson].Max),unit[lson].rMax+unit[rson].lMax);
		return;
	}
	inline void Set0(reg int k){
		unit[k].tag=1;
		unit[k].Max=unit[k].lMax=unit[k].rMax=0;
		return;
	}
	inline void Set1(reg int k){
		unit[k].tag=2;
		unit[k].Max=unit[k].lMax=unit[k].rMax=unit[k].len;
		return;
	}
	void pushdown(reg int k){
		switch(unit[k].tag){
			case 0:break;
			case 1:{
				Set0(lson);
				Set0(rson);
				break;
			}
			case 2:{
				Set1(lson);
				Set1(rson);
				break;
			}
			default:break;
		}
		unit[k].tag=0;
		return;
	}
	inline void Build(reg int k,reg int l,reg int r){
		unit[k].Max=unit[k].len=unit[k].lMax=unit[k].rMax=r-l+1;
		unit[k].tag=0;
		if(l==r)
			return;
		Build(lson,l,mid);
		Build(rson,mid+1,r);
		return;
	}
	inline void Update(reg int k,reg int l,reg int r,reg int L,reg int R,reg int tag){
		pushdown(k);
		if(L<=l&&r<=R){
			switch(tag){
				case 1:{
					Set0(k);
					break;
				}
				case 2:{
					Set1(k);
					break;
				}
				default:break;
			}
			return;
		}
		if(L<=mid)
			Update(lson,l,mid,L,R,tag);
		if(R>mid)
			Update(rson,mid+1,r,L,R,tag);
		pushup(k);
		return;
	}
	inline int Query(reg int k,reg int l,reg int r,reg int len){
		pushdown(k);
		if(l==r)
			return l;
		if(unit[lson].Max>=len)
			return Query(lson,l,mid,len);
		if(unit[lson].rMax+unit[rson].lMax>=len)
			return mid-unit[lson].rMax+1;
		else
			return Query(rson,mid+1,r,len);
	}
	#undef lson
	#undef rson
	#undef mid
};

int n,m;
SegmentTree T;

int main(void){
	n=read();m=read();
	T.Build(1,1,n);
	for(reg int i=1;i<=m;++i){
		static int opt,x,y;
		opt=read();
		switch(opt){
			case 1:{
				x=read();
				if(T.unit[1].Max>=x){
					reg int l=T.Query(1,1,n,x);
					printf("%d\n",l);
					T.Update(1,1,n,l,l+x-1,1);
				}
				else
					puts("0");
				break;
			}
			case 2:{
				x=read(),y=read();
				T.Update(1,1,n,x,x+y-1,2);
				break;
			}
			default:break;
		}
	}
	return 0;
}
