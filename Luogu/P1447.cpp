#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;

bool st;

const int MAXN=1e5+5;

int n,m;
bool vis[MAXN];
int tot,prime[MAXN];
int phi[MAXN];
ll Sphi[MAXN];

inline void init(reg int n){
	phi[1]=1;
	for(reg int i=2;i<=n;++i){
		if(!vis[i]){
			prime[++tot]=i;
			phi[i]=i-1;
		}
		for(reg int j=1;j<=tot&&i*prime[j]<=n;++j){
			vis[i*prime[j]]=true;
			if(!(i%prime[j])){
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

bool ed;

int main(void){
	scanf("%d%d",&n,&m);
	init(min(n,m));
	reg ll ans=0;
	for(reg int l=1,r;l<=min(n,m);l=r+1){
		r=min(n/(n/l),m/(m/l));
		ans+=(Sphi[r]-Sphi[l-1])*(n/l)*(m/l);
	}
	ans=ans*2-1ll*n*m;
	printf("%lld\n",ans);
	fprintf(stderr,"%.3lf s\n",1.0*clock()/CLOCKS_PER_SEC);
	fprintf(stderr,"%.3lf MiB\n",(&ed-&st)/1048576.0);
	return 0;
}