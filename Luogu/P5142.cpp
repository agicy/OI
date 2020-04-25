#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
#define MOD 1000000007ll
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++)
static char buf[100000],*p1=buf,*p2=buf;
inline int read(void){
	reg bool f=false;
	reg char ch=getchar();
	reg int res=0;
	while(ch<'0'||'9'<ch)f|=(ch=='-'),ch=getchar();
	while('0'<=ch&&ch<='9')res=10*res+ch-'0',ch=getchar();
	return f?-res:res;
}

const int MAXN=100000+5;

inline void Read(void);
inline void Work(void);

int main(void){
	Read();
	Work();
	return 0;
}

inline ll pow(reg ll x,reg ll exp,reg ll mod){
	reg ll res=1;
	while(exp){
		if(exp&1)
			res=res*x%mod;
		x=x*x%mod;
		exp>>=1;
	}
	return res;
}

inline ll inv(reg ll x,reg ll mod){
	return pow(x,mod-2,mod);
}

int n,m;
ll b[MAXN];

inline void Read(void){
	n=read(),m=read();
	for(reg int i=1;i<=n;++i)
		b[i]=read();
	return;
}

struct SegmentTree{
	#define lson ( (k) << 1 )
	#define rson ( (k) << 1 | 1 )
	#define mid ( ( (l) + (r) ) >> 1 )
	struct Node{
		ll sum,sum2;
	};
	Node unit[MAXN<<2];
	inline void pushup(reg int k){
		unit[k].sum=(unit[lson].sum+unit[rson].sum)%MOD;
		unit[k].sum2=(unit[lson].sum2+unit[rson].sum2)%MOD;
		return;
	}
	inline void Build(reg int k,reg int l,reg int r,reg ll a[]){
		if(l==r){
			unit[k].sum=a[l];
			unit[k].sum2=a[l]*a[l]%MOD;
			return;
		}
		Build(lson,l,mid,a);
		Build(rson,mid+1,r,a);
		pushup(k);
		return;
	}
	inline void Update(reg int k,reg int l,reg int r,reg int pos,reg ll val){
		if(l==r&&l==pos){
			unit[k].sum=val;
			unit[k].sum2=val*val%MOD;
			return;
		}
		if(pos<=mid)
			Update(lson,l,mid,pos,val);
		else
			Update(rson,mid+1,r,pos,val);
		pushup(k);
		return;
	}
	inline ll QuerySum(reg int k,reg int l,reg int r,reg int L,reg int R){
		if(L<=l&&r<=R)
			return unit[k].sum;
		reg ll res=0;
		if(L<=mid)
			res=(res+QuerySum(lson,l,mid,L,R))%MOD;
		if(R>mid)
			res=(res+QuerySum(rson,mid+1,r,L,R))%MOD;
		return res;
	}
	inline ll QuerySum2(reg int k,reg int l,reg int r,reg int L,reg int R){
		if(L<=l&&r<=R)
			return unit[k].sum2;
		reg ll res=0;
		if(L<=mid)
			res=(res+QuerySum2(lson,l,mid,L,R))%MOD;
		if(R>mid)
			res=(res+QuerySum2(rson,mid+1,r,L,R))%MOD;
		return res;
	}
	#undef lson
	#undef rson
	#undef mid
};

SegmentTree T;

inline void Work(void){
	T.Build(1,1,n,b);
	while(m--){
		static ll c,a,b;
		c=read(),a=read(),b=read();
		switch(c){
			case 1:{
				T.Update(1,1,n,a,b);
				break;
			}
			case 2:{
				reg ll sum2=T.QuerySum2(1,1,n,a,b);
				reg ll sum=T.QuerySum(1,1,n,a,b);
				reg ll len=b-a+1;
				reg ll bar=sum*inv(len,MOD)%MOD;
				reg ll ans=(((sum2-2*bar%MOD*sum%MOD)%MOD+MOD)*inv(len,MOD)%MOD+bar*bar%MOD)%MOD;
				printf("%lld\n",ans);
				break;
			}
			default:break;
		}
	}
	return;
}
