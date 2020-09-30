#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;

const int MAXN=100+5;

int n;
int x[MAXN],y[MAXN];
int cnt[MAXN];

int main(void){
	scanf("%d",&n);
	for(reg int i=1;i<=n;++i)
		scanf("%d%d",&x[i],&y[i]);
	int ans=0;
	for(reg int i=1;i<=n;++i){
		for(reg int j=1;j<=n;++j)
			if(x[j]<x[i]&&y[j]<y[i])
				++cnt[i];
		if(cnt[i]>=cnt[ans])
			ans=i;
	}
	for(reg int i=1;i<=n;++i)
		printf("%d\n",cnt[i]);
	printf("%d\n",ans);
	return 0;
}