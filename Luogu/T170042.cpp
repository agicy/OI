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

const int MAXN=1e6+5;
const int mod=998244353;

inline int add(reg int a,reg int b){
	a+=b;
	return a>=mod?a-mod:a;
}

inline int sub(reg int a,reg int b){
	a-=b;
	return a<0?a+mod:a;
}

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

int n,k;
int fac[MAXN],invfac[MAXN];

inline void Init(reg int n){
	fac[0]=1;
	for(reg int i=1;i<=n;++i)
		fac[i]=1ll*fac[i-1]*i%mod;
	invfac[n]=fpow(fac[n],mod-2);
	for(reg int i=n-1;i>=0;--i)
		invfac[i]=1ll*invfac[i+1]*(i+1)%mod;
	return;
}

int f[MAXN];

int main(void){
	Init(1e6);
	reg int T=read();
	while(T--){
		n=read(),k=read();
		for(reg int i=0;i<=n;++i)
			f[i]=0;
		f[0]=1;
		reg int ptr=1,sum=0;
		for(reg int i=1;i<=n;++i){
			sum=add(sum,1ll*f[i-1]*invfac[i-1]%mod);
			if(i-k+1>ptr){
				sum=sub(sum,1ll*f[ptr-1]*invfac[ptr-1]%mod);
				++ptr;
			}
			f[i]=1ll*sum*fac[i-1]%mod;
		}
		reg int ans=0;
		for(reg int i=1;i<=n;++i)
			ans=add(ans,1ll*f[i-1]*fac[n-1]%mod*invfac[i-1]%mod);
		ans=1ll*ans*invfac[n]%mod;
		printf("%d\n",ans);
	}
	return 0;
}