#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;

const int MAXSIZE=1e7+1;

int n;
bitset<MAXSIZE> vis;
int tot,prime[664580];
int phi[MAXSIZE];
ll Sphi[MAXSIZE];

inline void Init(reg int n){
	phi[1]=1;
	for(reg int i=2;i<=n;++i){
		if(!vis[i]){
			phi[i]=i-1;
			prime[++tot]=i;
		}
		for(reg int j=1;j<=tot&&i*prime[j]<=n;++j){
			vis[i*prime[j]]=true;
			if(i%prime[j]==0){
				phi[i*prime[j]]=phi[i]*prime[j];
				break;
			}
			phi[i*prime[j]]=phi[i]*(prime[j]-1);
		}
	}
	for(reg int i=1;i<=n;++i)
		Sphi[i]=Sphi[i-1]+phi[i];
	return;
}

map<int,ll> M;

inline ll GetSphi(int n){
	if(n<MAXSIZE)
		return Sphi[n];
	if(M.count(n))
		return M[n];
	reg ll ans=1ll*n*(n+1)/2;
	for(reg int l=2,r;l<=n;l=r+1){
		r=n/(n/l);
		ans-=(r-l+1)*GetSphi(n/l);
	}
	return M[n]=ans;
}

int main(void){
	Init(1e7);
	scanf("%d",&n);
	printf("%lld\n",GetSphi(n));
	return 0;
}