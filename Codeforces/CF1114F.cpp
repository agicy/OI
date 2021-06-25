#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
typedef unsigned long long ull;
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++)
static char buf[1<<21],*p1=buf,*p2=buf;
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

const int MAXN=4e5+5;
const int MAXQ=2e5+5;
const int prime[]={2,3,5,7,11,13,17,19,23,29,31,37,41,43,47,53,59,61,67,71,73,79,83,89,97,101,103,107,109,113,127,131,137,139,149,151,157,163,167,173,179,181,191,193,197,199,211,223,227,229,233,239,241,251,257,263,269,271,277,281,283,293};
const int invprime[]={500000004,333333336,400000003,142857144,818181824,153846155,352941179,157894738,739130440,758620695,129032259,621621626,658536590,395348840,404255322,56603774,50847458,688524595,686567169,98591550,410958907,202531647,84337350,415730340,268041239,940594066,572815538,224299067,9174312,893805316,480314964,190839696,58394161,604316551,530201346,483443712,343949047,116564418,5988024,791907520,435754193,933701664,439790579,694300523,969543154,507537692,90047394,125560539,35242291,711790398,90128756,280334730,406639007,912350604,70038911,836501907,743494429,450184505,252707583,718861215,650176683,522184304};
const int tot=sizeof(prime)/sizeof(int);
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

inline ull getS(reg int x){
	reg ull S=0;
	for(reg int i=0;i<tot;++i)
		if(!(x%prime[i]))
			S|=(1ull<<i);
	return S;
}

namespace SegmentTree{
	#define lson ( (k) << 1 )
	#define rson ( (k) << 1 | 1 )
	#define mid ( ( (l) + (r) ) >> 1 )
	struct Data{
		int pod;
		ull S;
		inline Data(reg int pod=1,reg ull S=0):pod(pod),S(S){
			return;
		}
	};
	inline Data operator+(const Data& a,const Data& b){
		return Data(1ll*a.pod*b.pod%mod,a.S|b.S);
	}
	struct Node{
		Data val;
		int tPod;
		ull tS;
		#define val(x) unit[(x)].val
		#define tPod(x) unit[(x)].tPod
		#define tS(x) unit[(x)].tS
	};
	Node unit[MAXN<<2];
	inline void pushup(reg int k){
		val(k)=val(lson)+val(rson);
		return;
	}
	inline void build(reg int k,reg int l,reg int r,reg int a[]){
		tPod(k)=1,tS(k)=0;
		if(l==r){
			val(k)=Data(a[l],getS(a[l]));
			return;
		}
		build(lson,l,mid,a),build(rson,mid+1,r,a);
		pushup(k);
		return;
	}
	inline void Mul(reg int k,reg int l,reg int r,reg int Val){
		val(k).pod=1ll*val(k).pod*fpow(Val,r-l+1)%mod;
		tPod(k)=1ll*tPod(k)*Val%mod;
		return;
	}
	inline void Or(reg int k,reg ull Val){
		val(k).S|=Val;
		tS(k)|=Val;
		return;
	}
	inline void pushdown(reg int k,reg int l,reg int r){
		if(tPod(k)!=1){
			Mul(lson,l,mid,tPod(k)),Mul(rson,mid+1,r,tPod(k));
			tPod(k)=1;
		}
		if(tS(k)){
			Or(lson,tS(k)),Or(rson,tS(k));
			tS(k)=0;
		}
		return;
	}
	inline void update(reg int k,reg int l,reg int r,reg int L,reg int R,reg int Val,reg ull S){
		if(L<=l&&r<=R){
			Mul(k,l,r,Val),Or(k,S);
			return;
		}
		pushdown(k,l,r);
		if(L<=mid)
			update(lson,l,mid,L,R,Val,S);
		if(R>mid)
			update(rson,mid+1,r,L,R,Val,S);
		pushup(k);
		return;
	}
	inline Data query(reg int k,reg int l,reg int r,reg int L,reg int R){
		if(L<=l&&r<=R)
			return val(k);
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

int n,q;
int a[MAXN];

int main(void){
	n=read(),q=read();
	for(reg int i=1;i<=n;++i)
		a[i]=read();
	SegmentTree::build(1,1,n,a);
	while(q--){
		static char opt;
		static int l,r,x;
		do
			opt=getchar();
		while(!isalpha(opt));
		switch(opt){
			case 'M':{
				l=read(),r=read(),x=read();
				SegmentTree::update(1,1,n,l,r,x,getS(x));
				break;
			}
			case 'T':{
				l=read(),r=read();
				SegmentTree::Data res=SegmentTree::query(1,1,n,l,r);
				reg int ans=res.pod;
				for(reg int i=0;i<tot;++i)
					if((res.S>>i)&1)
						ans=1ll*ans*invprime[i]%mod*(prime[i]-1)%mod;
				writeln(ans);
				break;
			}
		}
	}
	flush();
	return 0;
}