#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++)
static char buf[100000],*p1=buf,*p2=buf;
inline int read(void){
	bool f=false;
	char ch=getchar();
	int res=0;
	while(ch<'0'||'9'<ch)f|=(ch=='-'),ch=getchar();
	while('0'<=ch&&ch<='9')res=10*res+ch-'0',ch=getchar();
	return f?-res:res;
}

ll a,b,c,k;

inline ll mul(ll a,ll b,ll mod){
	ll res=0;
	while(b){
		if(b&1)
			res=(res+a)%mod;
		a=(a+a)%mod;
		b>>=1;
	}
	return res;
}

inline ll fpow(ll x,ll exp,ll mod){
	ll res=1;
	while(exp){
		if(exp&1)
			res=mul(res,x,mod);
		x=mul(x,x,mod);
		exp>>=1;
	}
	return res;
}

int main(void){
	int T=read();
	while(T--){
		a=read(),b=read(),c=read(),k=read();
		if(!c)
			puts("0");
		else
			printf("%lld\n",mul(c,fpow(2,k,a+b+c),a+b+c));
	}
	return 0;
}