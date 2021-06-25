#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++)
static char buf[1<<21],*p1=buf,*p2=buf;
#define flush() (fwrite(wbuf,1,wp1,stdout),wp1=0)
#define putchar(c) (wp1==wp2&&(flush(),0),wbuf[wp1++]=c)
static char wbuf[1<<21];int wp1;const int wp2=1<<21;
inline int read(void){
	reg char ch=getchar();
	reg int res=0;
	while(!isdigit(ch)) ch=getchar();
	while(isdigit(ch)) res=10*res+(ch^'0'),ch=getchar();
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

const int MAXP=1e5+5;

int n,m,p;
int fac[MAXP],invfac[MAXP];

inline int binom(reg int n,reg int m){
	if(m<0||n<m)
		return 0;
	else
		return 1ll*fac[n]*invfac[m]%p*invfac[n-m]%p;
}

inline int lucas(reg int n,reg int m){
	if(m<0||n<m)
		return 0;
	else if(!n||!m)
		return 1;
	else
		return 1ll*binom(n%p,m%p)*lucas(n/p,m/p)%p;
}

int main(void){
	reg int T=read();
	while(T--){
		n=read(),m=read(),p=read();
		fac[0]=1;
		for(reg int i=1;i<p;++i)
			fac[i]=1ll*fac[i-1]*i%p;
		invfac[p-1]=p-1;
		for(reg int i=p-2;i>=0;--i)
			invfac[i]=1ll*invfac[i+1]*(i+1)%p;
		writeln(lucas(n+m,n));
	}
	flush();
	return 0;
}