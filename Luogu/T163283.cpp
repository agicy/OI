#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;

const int MAXN=1e5+5;

int n,p;

inline int add(reg int a,reg int b){
	reg ll sum=0ll+a+b;
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

int fac[MAXN<<1];
int invfac[MAXN<<1];

int main(void){
	scanf("%d%d",&n,&p);
	--n;
	fac[0]=1;
	for(reg int i=1;i<=(n<<1);++i)
		fac[i]=1ll*fac[i-1]*i%p;
	invfac[n<<1]=fpow(fac[n<<1],p-2);
	for(reg int i=(n<<1)-1;i>=0;--i)
		invfac[i]=1ll*invfac[i+1]*(i+1)%p;
	reg int ans=0;
	for(reg int i=0;i<=n;++i)
		ans=add(ans,1ll*fac[n+i]*invfac[i+1]%p*invfac[i]%p*invfac[n-i]%p);
	printf("%d\n",ans);
	return 0;
}