#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++)
static char buf[100000],*p1=buf,*p2=buf;
inline int read(void){
	reg bool f=false;
	reg char ch=getchar();
	reg int res=0;
	while(ch<'0'||'9'<ch)f|=(ch=='-'),ch=getchar();
	while('0'<=ch&&ch<='9')res=10*res+ch-'0',ch=getchar();
	return f?-res:res;
}

int n,r;
double R;

inline ll gcd(reg ll a,reg ll b){
	return b==0?a:gcd(b,a%b);
}

inline ll S(reg int n,reg ll a,reg ll b,reg ll c){
	if(!n)
		return 0;
	reg ll G=gcd(a,gcd(b,c));
	a/=G,b/=G,c/=G;
	reg ll k=(a*R+b)/c;
	reg ll sum=(k*n*(n+1)>>1);
	b-=k*c,k=(a*R+b)/c*n;
	return sum+n*k-S(k,a*c,-b*c,a*a*r-b*b);
}

int main(void){
	reg int T=read();
	while(T--){
		n=read(),r=read();
		R=sqrt(r);
		reg ll T=floor(R);
		if(T*T==r)
			printf("%d\n",T&1?(n&1?-1:0):n);
		else
			printf("%lld\n",n-2*S(n,1,0,1)+4*S(n,1,0,2));
	}
	return 0;
}