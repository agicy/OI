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

const int MAXN=5e5+50;
const int mod=1e9+7;

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

int n;
int a[MAXN],b[MAXN];
int f[MAXN],g[MAXN];

int main(void){
	n=read();
	reg int inv100=fpow(100,mod-2);
	for(reg int i=1;i<=n;++i)
		a[i]=1ll*read()*inv100%mod,b[i]=1ll*read()*inv100%mod;
	for(reg int i=n;i>=1;--i){
		f[i]=1ll*a[i]*fpow(sub(1,1ll*b[i]*g[i+1]%mod),mod-2)%mod;
		g[i]=add(b[i],1ll*a[i]*f[i]%mod*g[i+1]%mod);
	}
	for(reg int i=2;i<=n;i++)
		f[i]=1ll*f[i]*f[i-1]%mod;
	printf("%d\n",f[n]);
	return 0;
}