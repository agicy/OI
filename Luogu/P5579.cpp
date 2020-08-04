#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++)
static char buf[100000],*p1=buf,*p2=buf;
inline ll read(void){
	reg char ch=getchar();
	reg ll res=0;
	while(ch<'0'||'9'<ch)ch=getchar();
	while('0'<=ch&&ch<='9')res=10ll*res+ch-'0',ch=getchar();
	return res;
}

const int MAXN=5e5+5;
const int MAXM=5e5+5;

int n,m;
int a[MAXN];
ll suma[MAXN];

namespace SegmentTree{
	#define lson ( (k) << 1 )
	#define rson ( (k) << 1 | 1 )
	#define mid ( ( (l) + (r) ) >> 1 )
	struct Node{
		ll sum,Max;
		ll taga,tags;
		#define sum(k) unit[(k)].sum
		#define Max(k) unit[(k)].Max
		#define taga(k) unit[(k)].taga
		#define tags(k) unit[(k)].tags
	};
	Node unit[MAXN<<2];
	inline void build(reg int k,reg int l,reg int r){
		tags(k)=-1;
		if(l==r)
			return;
		build(lson,l,mid);
		build(rson,mid+1,r);
		return;
	}
	inline void pushup(reg int k){
		sum(k)=sum(lson)+sum(rson);
		Max(k)=Max(rson);
		return;
	}
	inline void set(reg int k,reg int l,reg int r,reg ll val){
		tags(k)=val;
		sum(k)=1ll*(r-l+1)*val;
		Max(k)=val;
		taga(k)=0;
		return;
	}
	inline void add(reg int k,reg int l,reg int r,reg ll val){
		taga(k)+=val;
		sum(k)+=1ll*(suma[r]-suma[l-1])*val;
		Max(k)+=a[r]*val;
		return;
	}
	inline void pushdown(reg int k,reg int l,reg int r){
		if(tags(k)!=-1){
			set(lson,l,mid,tags(k));
			set(rson,mid+1,r,tags(k));
			tags(k)=-1;
		}
		if(taga(k)){
			add(lson,l,mid,taga(k));
			add(rson,mid+1,r,taga(k));
			taga(k)=0;
		}
		return;
	}
	inline int find(reg int k,reg int l,reg int r,reg ll val){
		if(l==r)
			return sum(k)<val?n+1:l;
		pushdown(k,l,r);
		if(Max(lson)>=val)
			return find(lson,l,mid,val);
		else
			return find(rson,mid+1,r,val);
	}
	inline ll query(reg int k,reg int l,reg int r,reg int L,reg int R,reg ll val){
		if(L<=l&&r<=R){
			reg ll tmp=sum(k);
			set(k,l,r,val);
			return tmp-sum(k);
		}
		pushdown(k,l,r);
		reg ll res=0;
		if(L<=mid)
			res+=query(lson,l,mid,L,R,val);
		if(R>mid)
			res+=query(rson,mid+1,r,L,R,val);
		pushup(k);
		return res;
	}
	#undef lson
	#undef rson
	#undef mid
}

using namespace SegmentTree;

int main(void){
	n=read(),m=read();
	for(reg int i=1;i<=n;++i)
		a[i]=read();
	sort(a+1,a+n+1);
	for(reg int i=1;i<=n;++i)
		suma[i]=suma[i-1]+a[i];
	build(1,1,n);
	reg ll lastd=0;
	while(m--){
		static ll d,b;
		d=read(),b=read();
		add(1,1,n,d-lastd);
		lastd=d;
		reg int pos=find(1,1,n,b);
		if(pos>n)
			puts("0");
		else
			printf("%lld\n",query(1,1,n,pos,n,b));
	}
	return 0;
}