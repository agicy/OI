#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;

const int MAXN=100000+5;

int n, m;
pair<int,int> a[MAXN],b[MAXN];

int main(void){
	while(scanf("%d%d",&n,&m)!=EOF){
		for(reg int i=1;i<=n;++i)
			scanf("%d%d",&a[i].first,&a[i].second);
		for(reg int i=1;i<=m;++i)
			scanf("%d%d",&b[i].first,&b[i].second);
		sort(a+1,a+n+1);
		sort(b+1,b+m+1);
		static multiset<int> S;
		S.clear();
		ll cnt=0,ans=0;
		for(reg int i=m,j=n;i>=1;--i){
			while(j>=1&&b[i].first<=a[j].first)
				S.insert(a[j--].second);
			static multiset<int>::iterator it;
			it=S.lower_bound(b[i].second);
			if(it!=S.end()){
				++cnt;
				ans+=500*b[i].first+2*b[i].second;
				S.erase(it);
			}
		}
		printf("%lld %lld\n",cnt,ans);
	}
	return 0;
}
