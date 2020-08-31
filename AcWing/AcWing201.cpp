#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

const int MAXSIZE=1e3+5;

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

int n,c;

int main(void){
	Init(1e3);
	scanf("%d",&c);
	for(int C=1;C<=c;++C){
		scanf("%d",&n);
		int sum=0;
		for(int i=1;i<=n;++i)
			sum+=phi[i];
		printf("%d %d %d\n",C,n,sum*2+1);
	}
	return 0;
}