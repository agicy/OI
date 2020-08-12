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

const int p=1e9+7;
const int MAXK=1e6+5;

inline int add(reg int a,reg int b,reg int p){
	reg int sum=a+b;
	return sum>=p?sum-p:sum;
}

inline int mul(reg int a,reg int b,reg int p){
	return 1ll*a*b%p;
}

inline int pow(reg int x,reg int exp,reg int mod){
	reg int res=1;
	while(exp){
		if(exp&1)
			res=mul(res,x,mod);
		x=mul(x,x,mod);
		exp>>=1;
	}
	return res;
}

int n,k;
int pl[MAXK],pr[MAXK],fac[MAXK];

int main(void){
	n=read(),k=read();
	pl[0]=pr[k+3]=fac[0]=1;
	for(reg int i=1;i<=k+2;++i)
		pl[i]=mul(pl[i-1],add(n,p-i,p),p);
	for(reg int i=k+2;i>=1;--i)
		pr[i]=mul(pr[i+1],add(n,p-i,p),p);
	for(reg int i=1;i<=k+2;++i)
		fac[i]=mul(fac[i-1],i,p);
	reg int ans=0,sum=0;
	for(reg int i=1;i<=k+2;++i){
		sum=add(sum,pow(i,k,p),p);
		ans=add(ans,mul(mul(sum,mul(pl[i-1],pr[i+1],p),p),pow(mul(mul(fac[i-1],((k-i)&1)?p-1:1,p),fac[k+2-i],p),p-2,p),p),p);
	}
	printf("%d\n",ans);
	return 0;
}