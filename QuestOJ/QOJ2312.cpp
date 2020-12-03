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
	while(isdigit(ch))res=10*res+ch-'0',ch=getchar();
	return res;
}

const int p=1e9+7;

inline int add(reg int a,reg int b){
	reg int sum=a+b;
	return sum>=p?sum-p:sum;
}

inline int fpow(reg int x,reg int exp){
	reg int res=1;
	while(exp){
		if(exp&1)
			res=1ll*res*x%p;
		x=1ll*x*x%p;
		exp>>=1;
	}
	return res;
}

const int N=4e3;

int a,b,c,d;
int fac[N+5],invfac[N+5];

inline int binom(reg int n,reg int m){
	if(m<0||n<m)
		return 0;
	else
		return 1ll*fac[n]*invfac[m]%p*invfac[n-m]%p;
}

int main(void){
	a=read(),b=read(),c=read(),d=read();
	fac[0]=1;
	for(reg int i=1;i<=N;++i)
		fac[i]=1ll*fac[i-1]*i%p;
	invfac[N]=fpow(fac[N],p-2);
	for(reg int i=N-1;i>=0;--i)
		invfac[i]=1ll*invfac[i+1]*(i+1)%p;
	reg int lenS=a+b;
	reg int ans=0;
	if(c==0||d==0)
		ans=add(ans,binom(a+b,b));
	for(reg int i=c;i<=lenS;++i){
		if(lenS-i-a+c-d<0)
			break;
		ans=add(ans,1ll*binom(i-1,c-1)*binom(lenS-i,a-c)%p);
	}
	ans=1ll*ans*binom(c+d,c)%p;
	printf("%d\n",ans);
	return 0;
}