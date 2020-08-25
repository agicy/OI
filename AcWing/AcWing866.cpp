#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;

const int MAXSIZE=1e5+5;

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
	Init(1e5);
	scanf("%d",&n);
	for(reg int i=1;i<=n;++i){
		static int x;
		scanf("%d",&x);
		for(reg int j=1;j<=tot;++j)
			if(x%prime[j]==0){
				reg int cnt=0;
				while(x%prime[j]==0)
					++cnt,x/=prime[j];
				printf("%d %d\n",prime[j],cnt);
			}
		if(x>1)
			printf("%d %d\n",x,1);
		puts("");
	}
	return 0;
}