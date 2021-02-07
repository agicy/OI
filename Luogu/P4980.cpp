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

const int mod=1e9+7;

inline int add(reg int a,reg int b){
	a+=b;
	return a>=mod?a-mod:a;
}

inline int phi(reg int x){
	reg int res=x;
	for(reg int i=2;i*i<=x;++i)
		if(!(x%i)){
			res=res/i*(i-1);
			while(!(x%i))
				x/=i;
		}
	if(x>1)
		res=res/x*(x-1);
	return res;
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

int main(void){
	reg int T=read();
	while(T--){
		reg int n=read();
		reg int ans=0;
		for(reg int i=1;i*i<=n;++i)
			if(!(n%i)){
				ans=add(ans,1ll*fpow(n,i)*phi(n/i)%mod);
				if(i*i!=n)
					ans=add(ans,1ll*fpow(n,n/i)*phi(i)%mod);
			}
		ans=1ll*ans*fpow(n,mod-2)%mod;
		printf("%d\n",ans);
	}
	return 0;
}