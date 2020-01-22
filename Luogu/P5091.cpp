#include<cstdio>
#define reg register
typedef long long ll;
inline int read(reg ll mod){
	reg bool flag=false;
	reg char ch=getchar();
	reg int res=0;
	while(ch<'0'||'9'<ch)ch=getchar();
	while('0'<=ch&&ch<='9')res=10*res+ch-'0',flag|=(res>=mod),res%=mod,ch=getchar();
	return res+(flag?mod:0);
}

ll a,m,b;

inline ll phi(reg ll);
inline ll pow(reg ll,reg ll,reg ll);

int main(void){
	scanf("%lld%lld",&a,&m);
	b=read(phi(m));
	printf("%lld\n",pow(a,b,m));
	return 0;
}

inline ll phi(reg ll n){
	reg ll i,ans=n;
	for(i=2;i*i<=n;++i)
		if(n%i==0){
			ans=ans/i*(i-1);
			while(n%i==0)
				n/=i;
		}
	if(n>1)
		ans=ans/n*(n-1);
	return ans;
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
