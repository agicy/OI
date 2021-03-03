#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++)
static char buf[100000],*p1=buf,*p2=buf;
#define flush() (fwrite(wbuf,1,wp1,stdout),wp1=0)
#define putchar(c) (wp1==wp2&&(flush(),0),wbuf[wp1++]=c)
static char wbuf[1<<21];int wp1;const int wp2=1<<21;
inline int read(void){
	reg char ch=getchar();
	reg int res=0;
	while(!isdigit(ch))ch=getchar();
	while(isdigit(ch))res=10*res+(ch^'0'),ch=getchar();
	return res;
}

inline void writeln(reg int x){
	static char buf[32];
	reg int p=-1;
	if(x==0) putchar('0');
	else while(x) buf[++p]=(x%10)^'0',x/=10;
	while(~p) putchar(buf[p--]);
	putchar('\n');
	return;
}

inline int min(reg int a,reg int b){
	return a<b?a:b;
}

const int MAXN=2e5+5;

namespace SegmentTree{
	#define lson ( (k) << 1 )
	#define rson ( (k) << 1 | 1 )
	#define mid ( ( (l) + (r) ) >> 1 )
	struct Data{
		int len,sum,lMax,rMax,Max;
		inline Data(reg int len=0,reg int sum=0,reg int lMax=0,reg int rMax=0,reg int Max=0):len(len),sum(sum),lMax(lMax),rMax(rMax),Max(Max){
			return;
		}
	};
	inline Data operator+(const Data& a,const Data& b){
		Data res;
		res.len=a.len+b.len;
		res.sum=a.sum+b.sum;
		res.lMax=(a.sum==a.len)?a.sum+b.lMax:a.lMax;
		res.rMax=(b.sum==b.len)?b.sum+a.rMax:b.rMax;
		res.Max=max(a.rMax+b.lMax,max(a.Max,b.Max));
		return res;
	}
	struct Node{
		int cnt1;
		int tCov;
		Data dat;
		#define cnt1(x) unit[(x)].cnt1
		#define tCov(x) unit[(x)].tCov
		#define dat(x) unit[(x)].dat
	};
	Node unit[MAXN<<2];
	inline void pushup(reg int k){
		dat(k)=dat(lson)+dat(rson);
		cnt1(k)=cnt1(lson)+cnt1(rson);
		return;
	}
	inline void build(reg int k,reg int l,reg int r){
		tCov(k)=-1;
		if(l==r){
			cnt1(k)=1;
			dat(k)=Data(1,0,0,0,0);
			return;
		}
		build(lson,l,mid),build(rson,mid+1,r);
		pushup(k);
		return;
	}
	inline void cov0(reg int k,reg int l,reg int r){
		tCov(k)=0;
		cnt1(k)=0;
		dat(k)=Data(r-l+1,r-l+1,r-l+1,r-l+1,r-l+1);
		return;
	}
	inline void cov1(reg int k,reg int l,reg int r){
		tCov(k)=1;
		cnt1(k)=r-l+1;
		dat(k)=Data(r-l+1,0,0,0,0);
		return;
	}
	inline void pushdown(reg int k,reg int l,reg int r){
		switch(tCov(k)){
			case -1:{
				break;
			}
			case 0:{
				cov0(lson,l,mid),cov0(rson,mid+1,r);
				tCov(k)=-1;
				break;
			}
			case 1:{
				cov1(lson,l,mid),cov1(rson,mid+1,r);
				tCov(k)=-1;
				break;
			}
		}
		return;
	}
	inline void update0(reg int k,reg int l,reg int r,reg int L,reg int R){
		if(L<=l&&r<=R){
			cov0(k,l,r);
			return;
		}
		pushdown(k,l,r);
		if(L<=mid)
			update0(lson,l,mid,L,R);
		if(R>mid)
			update0(rson,mid+1,r,L,R);
		pushup(k);
		return;
	}
	inline void update1(reg int k,reg int l,reg int r,reg int L,reg int R){
		if(L<=l&&r<=R){
			cov1(k,l,r);
			return;
		}
		pushdown(k,l,r);
		if(L<=mid)
			update1(lson,l,mid,L,R);
		if(R>mid)
			update1(rson,mid+1,r,L,R);
		pushup(k);
		return;
	}
	inline int queryCnt0(reg int k,reg int l,reg int r,reg int L,reg int R){
		if(L<=l&&r<=R)
			return dat(k).sum;
		pushdown(k,l,r);
		if(L<=mid&&mid<R)
			return queryCnt0(lson,l,mid,L,R)+queryCnt0(rson,mid+1,r,L,R);
		else if(L<=mid)
			return queryCnt0(lson,l,mid,L,R);
		else
			return queryCnt0(rson,mid+1,r,L,R);
	}
	inline int queryCnt1(reg int k,reg int l,reg int r,reg int L,reg int R){
		if(L<=l&&r<=R)
			return cnt1(k);
		pushdown(k,l,r);
		if(L<=mid&&mid<R)
			return queryCnt1(lson,l,mid,L,R)+queryCnt1(rson,mid+1,r,L,R);
		else if(L<=mid)
			return queryCnt1(lson,l,mid,L,R);
		else
			return queryCnt1(rson,mid+1,r,L,R);
	}
	inline Data query(reg int k,reg int l,reg int r,reg int L,reg int R){
		if(L<=l&&r<=R)
			return dat(k);
		pushdown(k,l,r);
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

int main(void){
	n=read(),m=read();
	SegmentTree::build(1,1,n);
	while(m--){
		static int opt,l0,r0,l1,r1;
		opt=read();
		switch(opt){
			case 0:{
				l0=read(),r0=read();
				SegmentTree::update0(1,1,n,l0,r0);
				break;
			}
			case 1:{
				l0=read(),r0=read(),l1=read(),r1=read();
				reg int cnt=SegmentTree::queryCnt1(1,1,n,l0,r0);
				SegmentTree::update0(1,1,n,l0,r0);
				cnt=min(cnt,SegmentTree::queryCnt0(1,1,n,l1,r1));
				if(cnt==0)
					break;
				reg int l=l1,r=r1,mid;
				while(l<r){
					mid=(l+r)>>1;
					if(SegmentTree::queryCnt0(1,1,n,l1,mid+1)<=cnt)
						l=mid+1;
					else
						r=mid;
				}
				SegmentTree::update1(1,1,n,l1,l);
				break;
			}
			case 2:{
				l0=read(),r0=read();
				reg int res=SegmentTree::query(1,1,n,l0,r0).Max;
				writeln(res);
				break;
			}
		}
	}
	flush();
	return 0;
}