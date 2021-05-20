#pragma GCC optimize("Ofast")
#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;

const int MAXM=1e7+5;
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

int n,m;

int main(void){
	scanf("%d%d",&n,&m);
	reg bool* vis=new bool[m+1]();
	reg int tot=0,*prime=new int[664579];
	for(reg int i=2;i<=m;++i){
		if(!vis[i])
			prime[tot++]=i;
		for(reg int j=0;j<tot&&i*prime[j]<=m;++j){
			vis[i*prime[j]]=true;
			if(!(i%prime[j]))
				break;
		}
	}
	delete[] vis;
	reg int *f=new int[m+1];
	f[0]=1;
	for(reg int i=1;i<=m;++i)
		f[i]=1ll*f[i-1]*n%mod;
	for(reg int i=0;i<tot;++i)
		for(reg int j=m/prime[i];j>=1;--j)
			f[j*prime[i]]=sub(f[j*prime[i]],f[j]);
	delete[] prime;
	reg int *fac=new int[m+1];
	fac[0]=1;
	for(reg int i=1;i<=m;++i)
		fac[i]=1ll*fac[i-1]*i%mod;
	reg int *inv=new int[m+1];
	inv[m]=fpow(fac[m],mod-2);
	for(reg int i=m-1;i>=0;--i)
		inv[i]=1ll*inv[i+1]*(i+1)%mod;
	for(reg int i=1;i<=m;++i)
		inv[i]=1ll*inv[i]*fac[i-1]%mod;
	delete[] fac;
	reg int ans=0;
	for(reg int i=1;i<=m;++i)
		ans=add(ans,1ll*f[i]*inv[i]%mod);
	delete[] inv,f;
	printf("%d\n",ans);
	fprintf(stderr,"%.3lf s\n",1.0*clock()/CLOCKS_PER_SEC);
	return 0;
}