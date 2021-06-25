#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++)
static char buf[1<<21],*p1=buf,*p2=buf;
inline int read(void){
	reg char ch=getchar();
	reg int res=0;
	while(!isdigit(ch))ch=getchar();
	while(isdigit(ch))res=10*res+(ch^'0'),ch=getchar();
	return res;
}

const int MAXN=1e3+5;
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
int p[MAXN];

int main(void){
	n=read();
	for(reg int i=1;i<=n;++i){
		reg int a=read(),b=read();
		p[i]=1ll*a*fpow(b,mod-2)%mod;
	}
	reg int ans=0;
	for(reg int i=1;i<=n;++i){
		reg int sum=1;
		for(reg int j=1;j<=n;++j)
			if(i!=j)
				sum=add(sum,1ll*p[j]*fpow(add(p[i],p[j]),mod-2)%mod);
		ans=add(ans,1ll*p[i]*sum%mod);
	}
	printf("%d\n",ans);
	return 0;
}