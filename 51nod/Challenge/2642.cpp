#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;

const int MAXSIZE=1e4+5;

bool vis[MAXSIZE];
int tot,prime[MAXSIZE];
int d[MAXSIZE],c[MAXSIZE];

inline void Init(reg int n){
	vis[1]=true;
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

int s;

int main(void){
	scanf("%d",&s);
	Init(s);
	int ans=0;
	for(reg int i=1;i<=tot;++i)
		if(!vis[s-prime[i]])
			ans=max(ans,prime[i]*(s-prime[i]));
	printf("%d\n",ans);
	return 0;
}