#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
#define getchar()(p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++)
static char buf[1<<21],*p1=buf,*p2=buf;
inline int read(void){
	reg char ch=getchar();
	reg int res=0;
	while(!isdigit(ch))ch=getchar();
	while(isdigit(ch))res=10*res+(ch^'0'),ch=getchar();
	return res;
}

inline int max(reg int a,reg int b){
	return a>b?a:b;
}

inline int min(reg int a,reg int b){
	return a<b?a:b;
}

const int MAXN=2e5+5;
const int MAXA=2e3+5;
const int MAXB=2e3+5;
const int mod=1e9+7;

int n;
int a[MAXN],b[MAXN];
int fac[(MAXA+MAXB)<<1],invfac[(MAXA+MAXB)<<1];
int f[MAXA<<1][MAXB<<1];

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

inline int binom(reg int n,reg int m){
	if(m<0||n<m)
		return 0;
	else
		return 1ll*fac[n]*invfac[m]%mod*invfac[n-m]%mod;
}

inline void Init(reg int n){
	fac[0]=1;
	for(reg int i=1;i<=n;++i)
		fac[i]=1ll*fac[i-1]*i%mod;
	invfac[n]=fpow(fac[n],mod-2);
	for(reg int i=n-1;i>=0;--i)
		invfac[i]=1ll*invfac[i+1]*(i+1)%mod;
	return;
}

int main(void){
	n=read();
	reg int Maxa=0,Maxb=0;
	for(reg int i=1;i<=n;++i){
		a[i]=read(),b[i]=read();
		Maxa=max(Maxa,a[i]),Maxb=max(Maxb,b[i]);
	}
	++Maxa,++Maxb;
	for(reg int i=1;i<=n;++i)
		++f[Maxa-a[i]][Maxb-b[i]];
	Init((Maxa+Maxb)<<1);
	for(reg int i=1;i<=(Maxa<<1);++i)
		for(reg int j=1;j<=(Maxb<<1);++j)
			f[i][j]=add(f[i][j],add(f[i-1][j],f[i][j-1]));
	reg int ans=0;
	for(reg int i=1;i<=n;++i)
		ans=add(ans,sub(f[Maxa+a[i]][Maxb+b[i]],binom(2*a[i]+2*b[i],2*a[i])));
	ans=1ll*ans*fpow(2,mod-2)%mod;
	printf("%d\n",ans);
	return 0;
}