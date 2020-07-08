#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
const int p=998244353;
const int g=3;
const int invg=332748118;
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++)
static char buf[100000],*p1=buf,*p2=buf;
inline int read(void){
	reg char ch=getchar();
	reg int res=0;
	while(ch<'0'||'9'<ch)ch=getchar();
	while('0'<=ch&&ch<='9')res=10*res+ch-'0',ch=getchar();
	return res;
}

inline int pow(reg int x,reg int exp,reg int mod){
	reg int res=1;
	while(exp){
		if(exp&1)
			res=1ll*res*x%mod;
		x=1ll*x*x%mod;
		exp>>=1;
	}
	return res;
}

inline int inv(reg int x,reg int mod){
	return pow(x,mod-2,mod);
}

const int MAXN=100000+5;

int n;
int a[MAXN<<2],b[MAXN<<2];
int r[MAXN<<2];

inline void NTT(reg int a[],reg int limit,reg int type){
	for(reg int i=0;i<limit;++i)
		if(i<r[i])
			swap(a[i],a[r[i]]);
	for(reg int i=1;i<limit;i<<=1){
		reg int w=pow(type==1?g:invg,(p-1)/(i<<1),p);
		for(reg int j=0;j<limit;j+=(i<<1)){
			reg int e=1;
			for(reg int k=0;k<i;++k,e=1ll*e*w%p){
				reg int x=a[j+k],y=1ll*e*a[j+k+i]%p;
				a[j+k]=(x+y)%p,a[j+k+i]=(x-y+p)%p;
			}
		}
	}
	if(type==-1){
		reg int inv=pow(limit,p-2,p);
		for(reg int i=0;i<limit;++i)
			a[i]=1ll*a[i]*inv%p;
	}
	return;
}

inline void Work(reg int deg,reg int a[],reg int b[]){
	if(deg==1){
		b[0]=inv(a[0],p);
		return;
	}
	Work((deg+1)>>1,a,b);
	reg int limit=1,l=0;
	while(limit<=(deg<<1))
		limit<<=1,++l;
	for(reg int i=1;i<limit;++i)
		r[i]=(r[i>>1]>>1)|((i&1)<<(l-1));
	static int c[MAXN<<2];
	for(reg int i=0;i<deg;++i)
		c[i]=a[i];
	for(reg int i=deg;i<limit;++i)
		c[i]=0;
	NTT(c,limit,1),NTT(b,limit,1);
	for(reg int i=0;i<limit;++i)
		b[i]=1ll*(2ll-1ll*c[i]*b[i]%p+p)%p*b[i]%p;
	NTT(b,limit,-1);
	for(reg int i=deg;i<limit;++i)
		b[i]=0;
	return;
}

int main(void){
	n=read();
	for(reg int i=0;i<n;++i)
		a[i]=read();
	Work(n,a,b);
	for(reg int i=0;i<n;++i)
		printf("%d%c",b[i],i==n-1?'\n':' ');
	return 0;
}