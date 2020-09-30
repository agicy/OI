#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;

const int MAXSIZE=1e6+5;

ll n;
bool vis[MAXSIZE];
int tot,prime[MAXSIZE];

inline void Init(reg int n){
	for(reg int i=2;i<=n;++i){
		if(!vis[i])
			prime[++tot]=i;
		for(reg int j=1;j<=tot&&i*prime[j]<=n;++j){
			vis[i*prime[j]]=true;
			if(i%prime[j]==0)
				break;
		}
	}
	return;
}

int main(void){
	Init(1e6);
	int T;
	scanf("%d",&T);
	while(T--){
		scanf("%lld",&n);
		reg ll ans=1;
		for(reg int i=1;i<=tot;++i)
			while(n%prime[i]==0){
				ans=prime[i];
				n/=prime[i];
			}
		if(n>ans)
			ans=n;
		printf("%lld\n",ans);
	}
	return 0;
}