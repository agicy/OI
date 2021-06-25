#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++)
static char buf[1<<21],*p1=buf,*p2=buf;
#define flush() (fwrite(wbuf,1,wp1,stdout),wp1=0)
#define putchar(c) (wp1==wp2&&(flush(),0),wbuf[wp1++]=c)
static char wbuf[1<<21];int wp1;const int wp2=1<<21;
inline int read(void){
	reg bool f=false;
	reg char ch=getchar();
	reg int res=0;
	while(!isdigit(ch))f|=(ch=='-'),ch=getchar();
	while(isdigit(ch))res=10*res+(ch^'0'),ch=getchar();
	return f?-res:res;
}

inline void writeln(reg int x){
	static char buf[32];
	reg int p=-1;
	if(x<0) x=-x,putchar('-');
	if(x==0) putchar('0');
	else while(x) buf[++p]=(x%10)^'0',x/=10;
	while(~p) putchar(buf[p--]);
	putchar('\n');
	return;
}

inline int max(reg int a,reg int b){
	return a>b?a:b;
}

const int MAXT=1e5+5;
const int inf=0x7fffffff;

int t;
int a[MAXT];

namespace SegmentTree{
	#define lson ( (k) << 1 )
	#define rson ( (k) << 1 | 1 )
	#define mid ( ( (l) + (r) ) >> 1 )
	struct Node{
		int Max,hMax;
		int tAdd,thAdd;
		int tCov,thCov;
		#define Max(x) unit[(x)].Max
		#define hMax(x) unit[(x)].hMax
		#define tAdd(x) unit[(x)].tAdd
		#define thAdd(x) unit[(x)].thAdd
		#define tCov(x) unit[(x)].tCov
		#define thCov(x) unit[(x)].thCov
	};
	Node unit[MAXT<<2];
	inline void pushup(reg int k){
		Max(k)=max(Max(lson),Max(rson));
		hMax(k)=max(hMax(lson),hMax(rson));
		return;
	}
	inline void build(reg int k,reg int l,reg int r,reg int a[]){
		tCov(k)=inf,thCov(k)=-inf;
		if(l==r){
			Max(k)=hMax(k)=a[l];
			return;
		}
		build(lson,l,mid,a),build(rson,mid+1,r,a);
		pushup(k);
		return;
	}
	inline void cover(reg int k,reg int val,reg int hval){
		Max(k)=val,hMax(k)=max(hMax(k),hval);
		tCov(k)=val,thCov(k)=max(thCov(k),hval);
		return;
	}
	inline void add(reg int k,reg int val,reg int hval){
		if(tCov(k)!=inf)
			cover(k,tCov(k)+val,tCov(k)+hval);
		else{
			thAdd(k)=max(thAdd(k),tAdd(k)+hval);
			tAdd(k)+=val;
			Max(k)+=val;
			hMax(k)=max(hMax(k),Max(k)-tAdd(k)+thAdd(k));
		}
		return;
	}
	inline void pushdown(int k){
		if(tAdd(k)||thAdd(k)){
			add(lson,tAdd(k),thAdd(k)),add(rson,tAdd(k),thAdd(k));
			tAdd(k)=thAdd(k)=0;
		}
		if(tCov(k)!=inf){
			cover(lson,tCov(k),thCov(k)),cover(rson,tCov(k),thCov(k));
			tCov(k)=inf;
		}
		return;
	}
	inline void updateAdd(reg int k,reg int l,reg int r,reg int L,reg int R,reg int val){
		if(L<=l&&r<=R){
			add(k,val,max(val,0));
			return;
		}
		pushdown(k);
		if(L<=mid)
			updateAdd(lson,l,mid,L,R,val);
		if(R>mid)
			updateAdd(rson,mid+1,r,L,R,val);
		pushup(k);
		return;
	}
	inline void updateCov(reg int k,reg int l,reg int r,reg int L,reg int R,reg int val){
		if(L<=l&&r<=R){
			cover(k,val,val);
			return;
		}
		pushdown(k);
		if(L<=mid)
			updateCov(lson,l,mid,L,R,val);
		if(R>mid)
			updateCov(rson,mid+1,r,L,R,val);
		pushup(k);
		return;
	}
	inline int queryMax(reg int k,reg int l,reg int r,reg int L,reg int R){
		if(L<=l&&r<=R)
			return Max(k);
		pushdown(k);
		if(L<=mid&&mid<R)
			return max(queryMax(lson,l,mid,L,R),queryMax(rson,mid+1,r,L,R));
		else if(L<=mid)
			return queryMax(lson,l,mid,L,R);
		else
			return queryMax(rson,mid+1,r,L,R);
	}
	inline int queryhMax(reg int k,reg int l,reg int r,reg int L,reg int R){
		if(L<=l&&r<=R)
			return hMax(k);
		pushdown(k);
		if(L<=mid&&mid<R)
			return max(queryhMax(lson,l,mid,L,R),queryhMax(rson,mid+1,r,L,R));
		else if(L<=mid)
			return queryhMax(lson,l,mid,L,R);
		else
			return queryhMax(rson,mid+1,r,L,R);
	}
	#undef lson
	#undef rson
	#undef mid
}

int main(void){
	t=read();
	for(reg int i=1;i<=t;++i)
		a[i]=read();
	SegmentTree::build(1,1,t,a);
	reg int e=read();
	while(e--){
		static char opt;
		static int x,y;
		do
			opt=getchar();
		while(!isalpha(opt));
		x=read(),y=read();
		switch(opt){
			case 'Q':{
				writeln(SegmentTree::queryMax(1,1,t,x,y));
				break;
			}
			case 'A':{
				writeln(SegmentTree::queryhMax(1,1,t,x,y));
				break;
			}
			case 'P':{
				SegmentTree::updateAdd(1,1,t,x,y,read());
				break;
			}
			case 'C':{
				SegmentTree::updateCov(1,1,t,x,y,read());
				break;
			}
		}
	}
	flush();
	return 0;
}