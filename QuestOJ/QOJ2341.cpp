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

const int MAXN=1e5+5;

namespace SegmenetTree{
	#define lson ( (k) << 1 )
	#define rson ( (k) << 1 | 1 )
	#define mid ( ( (l) + (r) ) >> 1 )
	struct Node{
		ll Max;
		ll a,b;
		inline ll getVal(reg ll x){
			return a*x+b;
		}
		#define Max(x) unit[(x)].Max
		#define a(x) unit[(x)].a
		#define b(x) unit[(x)].b
	};
	Node unit[MAXN<<2];
	inline void pushup(reg int k){
		Max(k)=max(Max(k),max(Max(lson),Max(rson)));
		return;
	}
	inline void build(reg int k,reg int l,reg int r){
		Max(k)=0;
		if(l==r)
			return;
		build(lson,l,mid),build(rson,mid+1,r);
		pushup(k);
		return;
	}
	inline void update(reg int k,reg int l,reg int r,reg int L,reg int R,reg ll ai,reg ll bi){
		if(L<=l&&r<=R){
			ll lval=unit[k].getVal(l),rval=unit[k].getVal(r);
			ll nlval=ai*l+bi,nrval=ai*r+bi;
			if(nlval<=lval&&nrval<=rval)
				return;
			if(nlval>=lval&&nrval>=rval){
				a(k)=ai,b(k)=bi;
				Max(k)=max(Max(k),max(nlval,nrval));
				return;
			}
			reg double p=1.0*(b(k)-bi)/(ai-a(k));
			if(lval>nlval)
				if(p<=(double)mid){
					update(lson,l,mid,L,R,a(k),b(k));
					a(k)=ai,b(k)=bi;
				}
				else
					update(rson,mid+1,r,L,R,ai,bi);
			else
				if(p<=(double)mid)
					update(lson,l,mid,L,R,ai,bi);
				else{
					update(rson,mid+1,r,L,R,a(k),b(k));
					a(k)=ai,b(k)=bi;
				}
			Max(k)=max(Max(k),max(nlval,nrval));
			pushup(k);
			return;
		}
		if(L<=mid)
			update(lson,l,mid,L,R,ai,bi);
		if(R>mid)
			update(rson,mid+1,r,L,R,ai,bi);
		pushup(k);
		return;
	}
	inline ll query(reg int k,reg int l,reg int r,reg int L,reg int R){
		if(L<=l&&r<=R)
			return Max(k);
		ll res=0;
		reg ll lef=max(l,L),rig=min(r,R);
		res=max(res,max(unit[k].getVal(lef),unit[k].getVal(rig)));
		if(L<=mid)
			res=max(res,query(lson,l,mid,L,R));
		if(R>mid)
			res=max(res,query(rson,mid+1,r,L,R));
		return res;
	}
	#undef lson
	#undef rson
	#undef mid
}

int n;
int c[MAXN];
ll f[MAXN];

int main(void){
	n=read();
	for(reg int i=1;i<=n;++i)
		c[i]=read();
	f[1]=1ll*c[1]*c[1];
	SegmenetTree::build(1,1,1e5);
	SegmenetTree::update(1,1,1e5,1,1e5,2ll*c[1],f[1]);
	for(reg int i=2;i<=n;++i){
		f[i]=max(1ll*c[i]*c[i],SegmenetTree::query(1,1,1e5,c[i],c[i]));
		SegmenetTree::update(1,1,1e5,1,1e5,2ll*c[i],f[i]);
	}
	reg ll ans=0;
	for(reg int i=1;i<=n;++i)
		ans=max(ans,f[i]+1ll*c[i]*c[i]);
	printf("%lld\n",ans);
	return 0;
}