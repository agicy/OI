#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++)
static char buf[100000],*p1=buf,*p2=buf;
inline int read(void){
	reg bool f=false;
	reg char ch=getchar();
	reg int res=0;
	while(!isdigit(ch))f|=(ch=='-'),ch=getchar();
	while(isdigit(ch))res=10*res+(ch^'0'),ch=getchar();
	return f?-res:res;
}

const int MAXN=1e5+5;
const int MAXLOG2A=31;
const int p=998244353;

inline int add(reg int a,reg int b){
	reg int sum=a+b;
	return sum>=p?sum-p:sum;
}

inline int mul(reg int a,reg int b){
	return 1ll*a*b%p;
}

inline int fpow(reg int x,reg int exp){
	reg int res=1;
	while(exp){
		if(exp&1)
			res=mul(res,x);
		x=mul(x,x);
		exp>>=1;
	}
	return res;
}

int n,k;
int cnt[MAXLOG2A];
int fac[MAXN],invfac[MAXN];

inline int binom(reg int n,reg int m){
	if(m<0||n<m)
		return 0;
	else
		return mul(fac[n],mul(invfac[m],invfac[n-m]));
}

int main(void){
	freopen("card.in","r",stdin);
	freopen("card.out","w",stdout);

	n=read(),k=read();
	fac[0]=1;
	for(reg int i=1;i<=n;++i)
		fac[i]=mul(fac[i-1],i);
	invfac[n]=fpow(fac[n],p-2);
	for(reg int i=n-1;i>=0;--i)
		invfac[i]=mul(invfac[i+1],i+1);
	for(reg int i=1;i<=n;++i){
		static int a;
		a=read();
		for(reg int j=0;j<MAXLOG2A;++j)
			if((a>>j)&1)
				++cnt[j];
	}
	reg int ans=0;
	for(reg int i=1;i<=k;i+=2)
		for(reg int j=0;j<MAXLOG2A;++j)
			ans=add(ans,mul(mul(binom(cnt[j],i),binom(n-cnt[j],k-i)),(1<<j)%p));
	printf("%d\n",ans);

	fclose(stdin);
	fclose(stdout);
	return 0;
}