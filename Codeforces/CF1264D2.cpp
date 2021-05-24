#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++)
static char buf[1<<21],*p1=buf,*p2=buf;

inline char* read(reg char *s){
	*s=getchar();
	while(*s!='('&&*s!=')'&&*s!='?')*s=getchar();
	while(*s=='('||*s==')'||*s=='?')*(++s)=getchar();
	*s='\0';
	return s;
}

const int MAXN=1e6+5;
const int mod=998244353;

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
char s[MAXN];
int fac[MAXN],invfac[MAXN];

inline int binom(reg int n,reg int m){
	if(m<0||n<m)
		return 0;
	else
		return 1ll*fac[n]*invfac[m]%mod*invfac[n-m]%mod;
}

int main(void){
	n=read(s+1)-(s+1);
	fac[0]=1;
	for(reg int i=1;i<=n;++i)
		fac[i]=1ll*fac[i-1]*i%mod;
	invfac[n]=fpow(fac[n],mod-2);
	for(reg int i=n-1;i>=0;--i)
		invfac[i]=1ll*invfac[i+1]*(i+1)%mod;
	reg int l=0,r=0,x=0,y=0;
	for(reg int i=1;i<=n;++i){
		if(s[i]==')')
			++r;
		if(s[i]=='?')
			++y;
	}
	reg int ans=0;
	for(reg int i=1;i<n;++i){
		switch(s[i]){
			case '(':{
				++l;
				break;
			}
			case ')':{
				--r;
				break;
			}
			case '?':{
				++x,--y;
				break;
			}
		}
		reg int d=sub(add(y,r),l);
		ans=add(ans,add(1ll*l*binom(x+y,d)%mod,1ll*x*binom(x+y-1,d-1)%mod));
	}
	printf("%d\n",ans);
	return 0;
}