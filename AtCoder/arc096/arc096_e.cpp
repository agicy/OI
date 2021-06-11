#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;

inline int add(reg int a,reg int b,reg int mod){
	a+=b;
	return a>=mod?a-mod:a;
}

inline int sub(reg int a,reg int b,reg int mod){
	a-=b;
	return a<0?a+mod:a;
}

const int MAXN=3e3+5;

int n,mod;

inline int fpow(reg int x,reg int exp,reg int mod){
	reg int res=1;
	while(exp){
		if(exp&1)
			res=1ll*res*x%mod;
		x=1ll*x*x%mod;
		exp>>=1;
	}
	return res;
}

int binom[MAXN][MAXN],strling2[MAXN][MAXN];

int main(void){
	scanf("%d%d",&n,&mod);
	binom[0][0]=1;
	for(reg int i=1;i<=n;++i){
		binom[i][0]=1;
		for(reg int j=1;j<=i;++j)
			binom[i][j]=add(binom[i-1][j-1],binom[i-1][j],mod);
	}
	strling2[0][0]=1;
	for(reg int i=1;i<=n+1;++i){
		strling2[i][0]=0;
		for(reg int j=1;j<=i;++j)
			strling2[i][j]=add(strling2[i-1][j-1],1ll*j*strling2[i-1][j]%mod,mod);
	}
	reg int ans=0;
	for(reg int i=0;i<=n;++i){
		reg int sum=0,pod=1,bas=fpow(2,n-i,mod);
		for(reg int j=0;j<=i;++j){
			sum=add(sum,1ll*strling2[i+1][j+1]*pod%mod,mod);
			pod=1ll*pod*bas%mod;
		}
		if(i&1)
			ans=sub(ans,1ll*binom[n][i]*fpow(2,fpow(2,n-i,mod-1),mod)%mod*sum%mod,mod);
		else
			ans=add(ans,1ll*binom[n][i]*fpow(2,fpow(2,n-i,mod-1),mod)%mod*sum%mod,mod);
	}
	printf("%d\n",ans);
	return 0;
}