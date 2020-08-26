#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;

const int MAXSIZE=1e6+5;

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

int n;

int main(void){
	Init(1e6);
	while(scanf("%d",&n)!=EOF&&n!=0){
		reg bool flag=true;
		for(reg int i=1;i<=tot;++i)
			if(n-prime[i]>=2&&!vis[n-prime[i]]){
				flag=false;
				printf("%d = %d + %d\n",n,prime[i],n-prime[i]);
				break;
			}
		if(flag)
			puts("Goldbach's conjecture is wrong.");
	}
	return 0;
}