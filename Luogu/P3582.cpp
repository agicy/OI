#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++)
static char buf[100000],*p1=buf,*p2=buf;
inline int read(void){
	reg char ch=getchar();
	reg int res=0;
	while(ch<'0'||'9'<ch)ch=getchar();
	while('0'<=ch&&ch<='9')res=10*res+ch-'0',ch=getchar();
	return res;
}

const int MAXN=1e6+5;
const int MAXM=1e6+5;

int n,m;
int f[MAXN];
int las[MAXM];
int pre[MAXN];
ll w[MAXM];

namespace SegmentTree{
	#define lson ( (k) << 1 )
	#define rson ( (k) << 1 | 1 )
	#define mid ( ( (l) + (r) ) >> 1 )
	struct Node{
		ll sum;
		ll lMax,rMax,Max;
		#define sum(x) unit[(x)].sum
		#define Max(x) unit[(x)].Max
		#define lMax(x) unit[(x)].lMax
		#define rMax(x) unit[(x)].rMax
	};
	Node unit[MAXN<<2];
	inline void pushup(reg int k){
		sum(k)=sum(lson)+sum(rson);
		lMax(k)=max(lMax(lson),sum(lson)+lMax(rson));
		rMax(k)=max(rMax(rson),sum(rson)+rMax(lson));
		Max(k)=max(max(lMax(k),rMax(k)),rMax(lson)+lMax(rson));
		return;
	}
	inline void update(reg int k,reg int l,reg int r,reg int pos,reg ll val){
		if(l==r){
			sum(k)=lMax(k)=rMax(k)=Max(k)=val;
			return;
		}
		if(pos<=mid)
			update(lson,l,mid,pos,val);
		else
			update(rson,mid+1,r,pos,val);
		pushup(k);
		return;
	}
	#undef lson
	#undef rson
	#undef mid
}

int main(void){
	n=read(),m=read();
	for(reg int i=1;i<=n;++i)
		f[i]=read();
	for(reg int i=1;i<=m;++i)
		w[i]=read();
	ll ans=0;
	for(reg int i=1;i<=n;++i){
		pre[i]=las[f[i]];
		las[f[i]]=i;
		if(pre[i])
			SegmentTree::update(1,1,n,pre[i],-w[f[i]]);
		if(pre[pre[i]])
			SegmentTree::update(1,1,n,pre[pre[i]],0);
		SegmentTree::update(1,1,n,i,w[f[i]]);
		ans=max(ans,SegmentTree::unit[1].Max);
	}
	printf("%lld\n",ans);
	return 0;
}
