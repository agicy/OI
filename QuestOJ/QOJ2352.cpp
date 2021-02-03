#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
typedef unsigned long long ull;
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++)
static char buf[100000],*p1=buf,*p2=buf;
inline int read(void){
	reg char ch=getchar();
	reg int res=0;
	while(!isdigit(ch))ch=getchar();
	while(isdigit(ch))res=10*res+(ch^'0'),ch=getchar();
	return res;
}

const int MAXN=1e5+5;
const int mod=998244353;
const int tot=64;
const int p[]={2,3,5,7,11,13,17,19,23,29,31,37,41,43,47,53,59,61,67,71,73,79,83,89,97,101,103,107,109,113,127,131,137,139,149,151,157,163,167,173,179,181,191,193,197,199,211,223,227,229,233,239,241,251,257,263,269,271,277,281,283,293,307,311};
//const int ip[]={9980997,6653998,11977196,8555140,5444180,1535538,10568114,14708837,3471651,11701858,17386252,1618540,16066970,2321162,18263100,16948862,12518538,15380552,10725847,1686929,13399146,17182475,12025297,15924736,13582387,395287,6395590,15857658,16299242,6359573,3300802,18742940,6702567,10914471,16210746,11765678,5340151,18247466,7769638,8077107,11932588,6506948,1985748,6619521,5877135,4413707,9744480,10115270,14597757,16475182,18334191,5011379,18885205,7555336,621385,11309266,12170137,12006660,18304499,11153142,6348337,9878802,9688394,3530256};//
int ip[tot];

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
		int pod;
		ull S;
		#define pod(x) unit[(x)].pod
		#define S(x) unit[(x)].S
	};
	inline Node operator+(const Node& a,const Node& b){
		Node res;
		res.pod=1ll*a.pod*b.pod%mod;
		res.S=a.S|b.S;
		return res;
	}
	Node unit[MAXN<<2];
	inline void pushup(reg int k){
		unit[k]=unit[lson]+unit[rson];
		return;
	}
	inline void build(reg int k,reg int l,reg int r,reg int a[]){
		if(l==r){
			pod(k)=a[l];
			S(k)=0;
			for(reg int i=0;i<tot;++i)
				if(!(a[l]%p[i]))
					S(k)|=(1ull<<i);
			return;
		}
		build(lson,l,mid,a),build(rson,mid+1,r,a);
		pushup(k);
		return;
	}
	inline void update(reg int k,reg int l,reg int r,reg int pos,reg int val,reg ull s){
		if(l==r){
			pod(k)=val;
			S(k)=s;
			return;
		}
		if(pos<=mid)
			update(lson,l,mid,pos,val,s);
		else
			update(rson,mid+1,r,pos,val,s);
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
	#undef lson
	#undef rson
	#undef mid
}

int n;
int a[MAXN];

inline int query(reg int l,reg int r){
	SegmentTree::Node s=SegmentTree::query(1,1,n,l,r);
	reg int res=s.pod;
	for(reg int i=0;i<tot;++i)
		if((s.S>>i)&1)
			res=1ll*res*ip[i]%mod*(p[i]-1)%mod;
	return res;
}

int main(void){
	for(reg int i=0;i<tot;++i)
		ip[i]=fpow(p[i],mod-2);
	n=read();
	for(reg int i=1;i<=n;++i)
		a[i]=read();
	reg int m=read();
	SegmentTree::build(1,1,n,a);
	while(m--){
		static int opt,l,r,pos,v;
		opt=read();
		switch(opt){
			case 1:{
				l=read(),r=read();
				printf("%d\n",query(l,r));
				break;
			}
			case 2:{
				pos=read(),v=read();
				reg ull S=0;
				for(reg int i=0;i<tot;++i)
					if(!(v%p[i]))
						S|=(1ull<<i);
				SegmentTree::update(1,1,n,pos,v,S);
				break;
			}
		}
	}
	return 0;
}