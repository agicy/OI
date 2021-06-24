#pragma GCC optimize("Ofast")
#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;

const int MAXN=5e5+5;

int n;
bool vis[MAXN<<1];
ll ans;

inline void insert(int x){
	ans+=x;
	vis[x]=true;
	return;
}

inline void erase(int x){
	assert(vis[x]);
	ans-=x;
	vis[x]=false;
	return;
}

int main(void){
	scanf("%d",&n);
	for(reg int i=n;i<=2*n-1;++i)
		insert(i);
	for(reg int i=n-1;i>=1;--i){
		reg int cnt=0,pos=-1;
		for(reg int j=i+i;j<=(n<<1);j+=i)
			if(vis[j]){
				if(cnt){
					++cnt;
					break;
				}
				else
					++cnt,pos=j;
			}
		if(cnt==1)
			erase(pos),insert(i);
	}
	printf("%lld\n",ans);
	return 0;
}