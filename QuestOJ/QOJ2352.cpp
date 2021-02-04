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
const int ip[]={499122177,332748118,598946612,855638017,272248460,460728163,939524097,105078353,217009642,481911067,128805723,242816194,97389693,510729669,191153174,828731161,727534020,654586461,432075914,702988981,382888245,404352143,60135202,392568004,699800165,889524671,38766771,802327237,622757945,150178354,322267862,922042494,276885295,854612072,442175351,323933598,953736643,202098550,436358310,957852963,117112466,193030676,789187944,920660595,719546691,837722648,738038479,528218985,386984595,357449943,844009174,54297810,981675982,616445716,42726412,918536629,924025442,7367117,918961408,497345941,567905798,705244304,877934773,38517467};

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