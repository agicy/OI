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

int main(void){
	reg int t=read();
	while(t--){
		reg int n=read();
		reg int x=read();
		reg ll sum0=0,sum1=0;
		for(reg int i=1;i<=n;++i){
			static ll a;
			a=read();
			sum0+=a,sum1+=(a+x-1)/x;
		}
		printf("%lld %lld\n",(sum0+x-1)/x,sum1);
	}
	return 0;
}