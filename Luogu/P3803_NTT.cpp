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

const int MAXN=2097152*4;
const int p=998244353;
const int g=3;
const int invg=332748118;

int n,m;
int limit,L;
int r[MAXN];
ll a[MAXN],b[MAXN];

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

inline void NTT(reg ll a[],reg int f){
	for(reg int i=0;i<limit;++i)
		if(i<r[i])
			swap(a[i],a[r[i]]);
	for(reg int i=1;i<limit;i<<=1){
		reg ll w=pow(f==1?g:invg,(p-1)/(i<<1),p);
		for(reg int j=0;j<limit;j+=(i<<1)){
			reg ll e=1;
			for(reg int k=0;k<i;++k,e=(e*w)%p){
				reg ll x=a[j+k],y=e*a[j+k+i]%p;
				a[j+k]=(x+y)%p,a[j+k+i]=(x-y+p)%p;
			}
		}
	}
	return;
}

int main(void){
	n=read(),m=read();
	for(reg int i=0;i<=n;++i)
		a[i]=read();
	for(reg int i=0;i<=m;++i)
		b[i]=read();
	limit=1;
	while(limit<=n+m)
		limit<<=1,++L;
	for(reg int i=0;i<limit;++i)
		r[i]=(r[i>>1]>>1)|((i&1)<<(L-1));
	NTT(a,1),NTT(b,1);
	for(reg int i=0;i<limit;++i)
		a[i]=a[i]*b[i]%p;
	NTT(a,-1);
	reg ll inv=pow(limit,p-2,p);
	for(reg int i=0;i<=n+m;++i)
		printf("%lld%c",a[i]*inv%p,i==n+m?'\n':' ');
	return 0;
}