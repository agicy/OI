#pragma GCC optimize("Ofast")
#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
typedef __uint128_t uint128_t;

bool st;

#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++)
static char buf[1<<21],*p1=buf,*p2=buf;
#define flush() (fwrite(wbuf,1,wp1,stdout),wp1=0)
#define putchar(c) (wp1==wp2&&(flush(),0),wbuf[wp1++]=c)
static char wbuf[1<<21];int wp1;const int wp2=1<<21;
inline int32_t read_int32(void){
	reg char ch=getchar();
	reg int32_t res=0;
	while(!isdigit(ch)) ch=getchar();
	while(isdigit(ch)) res=10*res+(ch^'0'),ch=getchar();
	return res;
}

inline char* read(reg char* s){
	*s=getchar();
	while(!isalnum(*s)) *s=getchar();
	while(isalnum(*s)) *(++s)=getchar();
	*s='\0';
	return s;
}

inline uint128_t read_uint128(void){
	static char buf[64];
	read(buf);
	reg uint128_t res=0;
	for(reg int32_t i=0;buf[i];++i)
		res=res<<4|(buf[i]<='9'?buf[i]-'0':buf[i]-'a'+10);
	return res;
}

inline void writeln_uint128(reg uint128_t x){
	static char buf[64];
	reg int32_t p=-1;
	if(!x) putchar('0');
	else while(x) buf[++p]=((x&15)>=10?(x&15)-10+'a':(x&15)+'0'),x>>=4;
	while(~p) putchar(buf[p--]);
	putchar('\n');
	return;
}

const int MAXN=3e5+5;

int32_t n,q;
int32_t lg[MAXN];
uint128_t a[MAXN];

namespace SegmentTree{
	#define lson ( (k) << 1 )
	#define rson ( (k) << 1 | 1 )
	#define mid ( ( (l) + (r) ) >> 1 )
	const int MAXSIZE=2e6;
	uint128_t pool[MAXSIZE],*buf=pool;
	struct Data{
		uint128_t *dat;
		uint32_t len;
		inline uint128_t getSum(void)const{
			reg uint128_t res=0;
			for(reg uint32_t i=0;i<len;++i)
				res+=dat[i]<<i;
			return res;
		}
		inline uint128_t getVal(reg uint32_t i)const{
			if(i>=len)
				return 0;
			else
				return dat[i];
		}
	};
	inline void merge(Data& x,const Data& l,const Data& r){
		x.dat[0]=l.getVal(0)^r.getVal(0);
		reg uint128_t w=l.getVal(0)&r.getVal(0);
		for(reg uint32_t i=1;i<x.len;++i){
			x.dat[i]=l.getVal(i)^r.getVal(i)^w;
			w=(l.getVal(i)&r.getVal(i))|(l.getVal(i)&w)|(r.getVal(i)&w);
		}
		return;
	}
	struct Node{
		Data dat;
		uint128_t tAnd;
		bool any;
		#define dat(x) unit[(x)].dat
		#define tAnd(x) unit[(x)].tAnd
		#define any(x) unit[(x)].any
	};
	const uint128_t U=-1;
	Node unit[MAXN<<2];
	inline void pushup(reg int k){
		merge(dat(k),dat(lson),dat(rson));
		any(k)=any(lson)||any(rson);
		return;
	}
	inline void build(reg int k,reg int l,reg int r,reg uint128_t a[]){
		dat(k).len=(lg[r-l+1]+1);
		dat(k).dat=buf,buf+=dat(k).len;
		tAnd(k)=U;
		if(l==r){
			dat(k).dat[0]=a[l];
			any(k)=a[l];
			return;
		}
		build(lson,l,mid,a),build(rson,mid+1,r,a);
		pushup(k);
		return;
	}
	inline void And(reg int k,reg uint128_t v){
		for(reg uint32_t i=0;i<dat(k).len;++i)
			dat(k).dat[i]&=v;
		tAnd(k)&=v;
		return;
	}
	inline void pushdown(reg int k){
		if(tAnd(k)!=U){
			And(lson,tAnd(k)),And(rson,tAnd(k));
			tAnd(k)=U;
		}
		return;
	}
	inline void updateAnd(reg int k,reg int l,reg int r,reg int L,reg int R,reg uint128_t v){
		if(!any(k))
			return;
		if(L<=l&&r<=R){
			And(k,v);
			return;
		}
		pushdown(k);
		if(L<=mid)
			updateAnd(lson,l,mid,L,R,v);
		if(R>mid)
			updateAnd(rson,mid+1,r,L,R,v);
		pushup(k);
		return;
	}
	inline void updateDiv(reg int k,reg int l,reg int r,reg int L,reg int R,reg uint128_t v){
		if(!any(k))
			return;
		if(l==r){
			dat(k).dat[0]/=v;
			any(k)=dat(k).dat[0];
			return;
		}
		pushdown(k);
		if(L<=mid)
			updateDiv(lson,l,mid,L,R,v);
		if(R>mid)
			updateDiv(rson,mid+1,r,L,R,v);
		pushup(k);
		return;
	}
	inline uint128_t query(reg int k,reg int l,reg int r,reg int L,reg int R){
		if(!any(k))
			return 0;
		if(L<=l&&r<=R)
			return dat(k).getSum();
		pushdown(k);
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
	#undef dat
	#undef tAnd
	#undef any
}

bool ed;

int main(void){
	n=read_int32(),q=read_int32();
	for(reg int i=1;i<=n;++i)
		a[i]=read_uint128();
	lg[0]=-1;
	for(reg int i=1;i<=n;++i)
		lg[i]=lg[i>>1]+1;
	SegmentTree::build(1,1,n,a);
	while(q--){
		static int32_t l,r;
		static uint128_t v;
		switch(read_int32()){
			case 1:{
				l=read_int32(),r=read_int32(),v=read_uint128();
				if(v!=1) SegmentTree::updateDiv(1,1,n,l,r,v);
				break;
			}
			case 2:{
				l=read_int32(),r=read_int32(),v=read_uint128();
				SegmentTree::updateAnd(1,1,n,l,r,v);
				break;
			}
			case 3:{
				l=read_int32(),r=read_int32();
				writeln_uint128(SegmentTree::query(1,1,n,l,r));
				break;
			}
		}
	}
	flush();
	fprintf(stderr,"%.3lf s\n",1.0*clock()/CLOCKS_PER_SEC);
	fprintf(stderr,"%.3lf MiB\n",(&ed-&st)/1048576.0);
	return 0;
}