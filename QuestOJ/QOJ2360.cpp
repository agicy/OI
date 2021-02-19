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

const int mod=998244353;

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

inline int gcd(reg int a,reg int b){
	return b?gcd(b,a%b):a;
}

int main(void){
	reg int n=read(),tmp=n;
	reg int d=0;
	while(tmp--)
		d=gcd(d,read());
	if(d==1)
		puts("0");
	else
		printf("%d\n",fpow(n,n));
	return 0;
}