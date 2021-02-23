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

inline int max(reg int a,reg int b){
	return a>b?a:b;
}

const int MAXN=1e5+5;
const int mod=1e9+7;

inline int fpow(reg int x,reg int exp){
	reg int res=1;
	while(exp){
		if(exp&1)
			res=1ll*res*x%mod;
		x=1ll*x*x%mod;
		exp>>=1;
	}
	return res;
}

namespace SegmentTree{
	#define lson ( (k) << 1 )
	#define rson ( (k) << 1 | 1 )
	#define mid ( ( (l) + (r) ) >> 1 )
	struct Node{
		int C;
		int tCov;
		int pod;
		int Maxb,Minb;
		int Maxa;
		#define C(x) unit[(x)].C
		#define tCov(x) unit[(x)].tCov
		#define pod(x) unit[(x)].pod
		#define Maxb(x) unit[(x)].Maxb
		#define Minb(x) unit[(x)].Minb
		#define Maxa(x) unit[(x)].Maxa
	};
	Node unit[MAXN<<2];
	inline void build(reg int k,reg int l,reg int r,reg int a[],reg int b[],reg int c[]){
		tCov(k)=-1;
		if(l==r){
			C(k)=c[l];
			pod(k)=min(C(k),b[l]);
			Maxb(k)=Minb(k)=b[l];
			Maxa(k)=a[l];
			return;
		}
		build(lson,l,mid,a,b,c),build(rson,mid+1,r,a,b,c);
		Maxa(k)=max(Maxa(lson),Maxa(rson));
		Maxb(k)=max(Maxb(lson),Maxb(rson));
		Minb(k)=min(Minb(lson),Minb(rson));
		pod(k)=1ll*pod(lson)*pod(rson);
		return;
	}
	inline void cov(reg int k,reg int l,reg int r,reg int val){
		if(l==r){
			C(k)=val;
			pod(k)=min(C(k),Minb(k));
			return;
		}
		if(val<=Minb(k)){
			C(k)=val;
			tCov(k)=val;
			pod(k)=fpow(val,r-l+1);
		}
		else if(val<=Maxb(k)){
			cov(lson,l,mid,val),cov(rson,mid+1,r,val);
			pod(k)=1ll*pod(lson)*pod(rson);
		}
		else{
			C(k)=val;
			tCov(k)=val;
		}
		return;
	}
	inline void pushdown(reg int k,reg int l,reg int r){
		if(tCov(k)!=-1){
			cov(lson,l,mid,tCov(k));
			cov(rson,mid+1,r,tCov(k));
			tCov(k)=-1;
		}
		return;
	}
	inline int queryA(reg int k,reg int l,reg int r,reg int L,reg int R,reg int val){
		if(Maxa(k)<=val)
			return r+1;
		if(l==r)
			return l;
		if(L<=mid&&Maxa(lson)>val)
			return queryA(lson,l,mid,L,R,val);
		else
			return queryA(rson,mid+1,r,L,R,val);
	}
	inline void updateC(reg int k,reg int l,reg int r,reg int L,reg int R,reg int val){
		if(L<=l&&r<=R){
			cov(k,l,r,val);
			return;
		}
		pushdown(k,l,r);
		if(L<=mid)
			updateC(lson,l,mid,L,R,val);
		if(R>mid)
			updateC(rson,mid+1,r,L,R,val);
		pod(k)=1ll*pod(lson)*pod(rson)%mod;
		return;
	}
	inline void updateB(reg int k,reg int l,reg int r,reg int pos,reg int val){
		if(l==r){
			Maxb(k)=Minb(k)=val;
			pod(k)=min(C(k),val);
			return;
		}
		pushdown(k,l,r);
		if(pos<=mid)
			updateB(lson,l,mid,pos,val);
		else
			updateB(rson,mid+1,r,pos,val);
		Maxb(k)=max(Maxb(lson),Maxb(rson));
		Minb(k)=min(Minb(lson),Minb(rson));
		pod(k)=1ll*pod(lson)*pod(rson);
		return;
	}
	inline void updateA(reg int k,reg int l,reg int r,reg int pos,reg int val){
		if(l==r){
			Maxa(k)=val;
			return;
		}
		pushdown(k,l,r);
		if(pos<=mid)
			updateA(lson,l,mid,pos,val);
		else
			updateA(rson,mid+1,r,pos,val);
		Maxa(k)=max(Maxa(lson),Maxa(rson));
		return;
	}
	#undef lson
	#undef rson
	#undef mid
}

int n,q;
int a[MAXN],b[MAXN];
int c[MAXN];

int main(void){
	n=read(),q=read();
	for(reg int i=1;i<=n;++i)
		a[i]=read();
	for(reg int i=1;i<=n;++i)
		c[i]=max(c[i-1],a[i]);
	for(reg int i=1;i<=n;++i)
		b[i]=read();
	SegmentTree::build(1,1,n,a,b,c);
	while(q--){
		static int opt,x,y;
		opt=read(),x=read(),y=read();
		switch(opt){
			case 0:{
				reg int pos=SegmentTree::queryA(1,1,n,x+1,n,y);
				SegmentTree::updateC(1,1,n,x,pos-1,y);
				SegmentTree::updateA(1,1,n,x,y);
				break;
			}
			case 1:{
				SegmentTree::updateB(1,1,n,x,y);
				break;
			}
		}
		writeln(SegmentTree::pod(1));
	}
	flush();
	return 0;
}