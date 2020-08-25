#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;

const int MAXN=1e6+5;

int n;
bool vis[MAXN];
int tot,prime[MAXN];

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
	scanf("%d",&n);
	Init(n);
	printf("%d\n",tot);
	return 0;
}