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

inline int gcd(reg int a,reg int b){
	return b==0?a:gcd(b,a%b);
}

inline ll f(reg ll x){
	return (x*(x-1))>>1;
}

int m,d,w;

int main(void){
	reg int t=read();
	while(t--){
		m=read(),d=read(),w=read();
		reg int k=gcd(d-1,w);
		reg int w1=w/k,lim=min(d,m);
		printf("%lld\n",1ll*(lim%w1)*f(lim/w1+1)+1ll*(w1-lim%w1)*f(lim/w1));
	}
	return 0;
}