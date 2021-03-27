#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;

const int MAXN=50+5;

int n;
string a[MAXN];
ll f[MAXN][MAXN],dp[MAXN];

inline bool check(reg int i,reg int j){
	if(a[i].size()>a[j].size())
		return a[i].find(a[j])!=0;
	else
		return a[j].find(a[i])!=0;
}

int main(){
	scanf("%d",&n);
	for(reg int i=1;i<=n;++i)
		cin>>a[i];
	sort(a+1,a+n+1);
	for(reg int i=1;i<=n;++i){
		dp[i]=1;
		for(reg int j=1;j<=n;++j)
			f[i][j]=check(i,j);
	}
	for(reg int i=1;i<=n;++i)
		for(reg int j=i;j<=n;++j)
			dp[j]+=f[i][j]?dp[i]:0;
	reg ll ans=0;
	for(reg int i=1;i<=n;++i)
		ans+=dp[i];
	printf("%lld\n",ans+1);
	return 0;
}