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

const int MAXN=2e3+5;
const int p=998244353;

inline int pow(reg int x,reg int exp,reg int mod){
	reg int res=1;
	while(exp){
		if(exp&1)
			res=1ll*res*x%mod;
		x=1ll*x*x%mod;
		exp>>=1;
	}
	return res;
}

inline int inv(reg int x,reg int mod){
	return pow(x,mod-2,mod);
}

inline int add(reg int a,reg int b){
	reg int sum=a+b;
	return sum>=p?sum-p:sum;
}

inline int mul(reg int a,reg int b){
	return 1ll*a*b%p;
}

int n,k;
int x[MAXN],y[MAXN];

inline int GetVal(reg int n,reg int k){
	reg int res=0;
	for(reg int i=1;i<=n;++i){
		reg int up=1,dw=1;
		for(reg int j=1;j<=n;++j)
			if(i!=j){
				up=mul(up,add(k,p-x[j]));
				dw=mul(dw,add(x[i],p-x[j]));
			}
		res=add(res,mul(y[i],mul(up,inv(dw,p))));
	}
	return res;
}

int main(void){
	n=read(),k=read();
	for(reg int i=1;i<=n;++i)
		x[i]=read(),y[i]=read();
	printf("%d\n",GetVal(n,k));
	return 0;
}