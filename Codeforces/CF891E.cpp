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

const int MAXN=5e3+5;
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

int n,k;
int f[MAXN];

int main(void){
	n=read(),k=read();
	f[0]=1;
	for(reg int i=1;i<=n;++i){
		reg int a=read();
		for(reg int j=i;j>=1;--j)
			f[j]=sub(1ll*f[j]*a%mod,f[j-1]);
		f[0]=1ll*f[0]*a%mod;
	}
	reg int inv=fpow(n,mod-2);
	reg int res=0;
	for(reg int i=0,tmp=1;i<=n;tmp=1ll*tmp*inv%mod*sub(k,i)%mod,++i)
		res=add(res,1ll*tmp*f[i]%mod);
	printf("%d\n",sub(f[0],res));
	return 0;
}