#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++)
static char buf[100000],*p1=buf,*p2=buf;
#define flush() (fwrite(wbuf,1,wp1,stdout),wp1=0)
#define putchar(c) (wp1==wp2&&(flush(),0),wbuf[wp1++]=c)
static char wbuf[1<<21];int wp1;const int wp2=1<<21;
inline int read(void){
	reg char ch=getchar();
	reg int res=0;
	while(!isdigit(ch))ch=getchar();
	while(isdigit(ch))res=10*res+(ch^'0'),ch=getchar();
	return res;
}

inline ll readll(void){
	reg char ch=getchar();
	reg ll res=0;
	while(!isdigit(ch))ch=getchar();
	while(isdigit(ch))res=10*res+(ch^'0'),ch=getchar();
	return res;
}

inline void writeln(reg int x){
	static char buf[32];
	reg int p=-1;
	if(x==0) putchar('0');
	else while(x) buf[++p]=(x%10)^'0',x/=10;
	while(~p) putchar(buf[p--]);
	putchar('\n');
	return;
}

const int mod=2333;

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

int binom[mod][mod];
int F[mod][mod];

inline int Lucas(reg ll n,reg ll m){
	if(m<0||n<m)
		return 0;
	else if(!n||!m)
		return 1;
	else
		return 1ll*Lucas(n/mod,m/mod)*binom[n%mod][m%mod]%mod;
}

inline int f(reg ll n,reg ll k){
	if(k<0)
		return 0;
	else if(!n||!k)
		return 1;
	else if(n<mod&&k<mod)
		return F[n][k];
	else
		return add(1ll*f(n%mod,mod-1)*f(n/mod,k/mod-1)%mod,1ll*Lucas(n/mod,k/mod)*f(n%mod,k%mod)%mod);
}

int main(void){
	binom[0][0]=1;
	for(reg int i=1;i<mod;++i){
		binom[i][0]=1;
		for(reg int j=1;j<=i;++j)
			binom[i][j]=add(binom[i-1][j-1],binom[i-1][j]);
	}
	for(reg int i=0;i<mod;++i){
		F[i][0]=1;
		for(reg int j=1;j<mod;++j)
			F[i][j]=add(F[i][j-1],binom[i][j]);
	}
	reg int t=read();
	while(t--){
		reg ll n=readll(),k=readll();
		writeln(f(n,k));
	}
	flush();
	return 0;
}