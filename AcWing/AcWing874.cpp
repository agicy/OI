#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

const int MAXSIZE=1e6+5;

bool vis[MAXSIZE];
int tot,prime[MAXSIZE];
int phi[MAXSIZE];

inline void Init(int n){
	phi[1]=1;
	for(int i=2;i<=n;++i){
		if(!vis[i]){
			prime[++tot]=i;
			phi[i]=i-1;
		}
		for(int j=1;j<=tot&&i*prime[j]<=n;++j){
			vis[i*prime[j]]=true;
			if(i%prime[j]==0){
				phi[i*prime[j]]=phi[i]*prime[j];
				break;
			}
			phi[i*prime[j]]=phi[i]*(prime[j]-1);
		}
	}
	return;
}

int n;

int main(void){
	Init(1e6);
	scanf("%d",&n);
	ll sum=0;
	for(int i=1;i<=n;++i)
		sum+=phi[i];
	printf("%lld\n",sum);
	return 0;
}