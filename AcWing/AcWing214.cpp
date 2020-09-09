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

const int MAXN=20+5;
const int p=1e9+7;

int n;
ll m,a[MAXN];

inline int fpow(reg int x,reg int exp){
	reg int res=1;
	while(exp){
		if(exp&1)
			res=1ll*res*x%p;
		x=1ll*x*x%p;
		exp>>=1;
	}
	return res;
}

inline int binom(reg ll n,reg ll m){
	if(m>n)
		return 0;
	reg int up=1,dn=1;
	for(reg ll i=n;i>n-m;--i)
		up=1ll*up*(i%p)%p;
	for(reg ll i=1;i<=m;++i)
		dn=1ll*dn*(i%p)%p;
	return 1ll*up*fpow(dn,p-2)%p;
}

int main(void){
	n=read(),m=read();
	for(reg int i=0;i<n;++i)
		a[i]=read();
	reg int ans=0;
	for(reg int i=0;i<(1<<n);++i){
		reg int sign=1;
		reg ll dn=m+n-1,up=n-1;
		for(reg int j=0;j<n;++j)
			if((i>>j)&1){
				sign=-sign;
				dn-=a[j]+1;
			}
		ans=((ans+1ll*binom(dn,up)*sign%p)%p+p)%p;
	}
	printf("%d\n",ans);
	return 0;
}