#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
#define int ll

const int MAXN=100000+5;
const int MAXM=1e6+5;
const int M=1e6;

int n;
ll h[MAXN],w[MAXN];
ll K[MAXN],b[MAXN];
ll dp[MAXN];

inline ll GetY(reg int id,reg int x){
	return 1ll*K[id]*x+b[id];
}

namespace SegmentTree{
	#define lson ( (k) << 1 )
	#define rson ( (k) << 1 | 1 )
	#define mid ( ( (l) + (r) ) >> 1 )
	int id[MAXM<<2];
	inline void Update(reg int k,reg int l,reg int r,int i){
		if(GetY(id[k],l)<=GetY(i,l)&&GetY(id[k],r)<=GetY(i,r))
			return;
		if(GetY(id[k],l)>=GetY(i,l)&&GetY(id[k],r)>=GetY(i,r)){
			id[k]=i;
			return;
		}
		reg int &a=id[k],&b=i;
		if(K[a]<K[b]){
			if(GetY(a,mid)>GetY(b,mid)){
				swap(a,b);
				Update(rson,mid+1,r,i);
			}
			else
				Update(lson,l,mid,i);
		}
		else{
			if(GetY(a,mid)>GetY(b,mid)){
				swap(a,b);
				Update(lson,l,mid,i);
			}
			else
				Update(rson,mid+1,r,i);
		}
		return;
	}
	inline ll Query(reg int k,reg int l,reg int r,reg ll pos){
		if(l==r)
			return GetY(id[k],pos);
		ll res=GetY(id[k],pos);
		if(pos<=mid)
			return min(res,Query(lson,l,mid,pos));
		else
			return min(res,Query(rson,mid+1,r,pos));
	}
	#undef lson
	#undef rson
	#undef mid
}

using namespace SegmentTree;

signed main(void){
	scanf("%lld",&n);
	for(reg int i=1;i<=n;++i)
		scanf("%lld",&h[i]);
	for(reg int i=1;i<=n;++i){
		scanf("%lld",&w[i]);
		w[i]+=w[i-1];
	}
	b[0]=1e18;
	K[1]=-2*h[1],b[1]=h[1]*h[1]-w[1];
	Update(1,0,M,1);
	for(reg int i=2;i<=n;++i){
		dp[i]=h[i]*h[i]+w[i-1]+Query(1,0,M,h[i]);
		K[i]=-2*h[i],b[i]=dp[i]+h[i]*h[i]-w[i];
		Update(1,0,M,i);
	}
	printf("%lld\n",dp[n]);
	return 0;
}