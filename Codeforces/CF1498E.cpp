#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;

const int MAXN=500+5;

int n;
pair<int,int> a[MAXN];

int main(void){
	scanf("%d",&n);
	for(reg int i=1;i<=n;++i)
		scanf("%d",&a[i].first),a[i].second=i;
	sort(a+1,a+n+1);
	reg int sum=0;
	pair<int,int> Min(n,0),Max(-1,0);
	pair<int,pair<int,int>/**/> ans;
	for(reg int i=1;i<=n;++i){
		sum+=a[i].first;
		Min=min(Min,a[i]),Max=max(Max,a[i]);
		if(sum==(i*(i-1)>>1)){
			if(Min.second!=Max.second)
				ans=max(ans,make_pair(Max.first-Min.first,make_pair(Min.second,Max.second)));
			Min.first=n,Max.first=-1;
		}
	}
	if(ans.second.first)
		printf("! %d %d\n",ans.second.first,ans.second.second);
	else
		puts("! 0 0");
	fflush(stdout);
	return 0;
}