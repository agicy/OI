#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

const int MAXN=400+5;

int n,k;
int a[MAXN<<1][MAXN<<1];
int sum[MAXN<<1][MAXN<<1];

int main(void){
	scanf("%d%d",&n,&k);
	for(int i=1;i<=n;++i)
		for(int j=1;j<=n;++j)
			scanf("%d",&a[i+j-1][n-i+j]);
	for(int i=1;i<=2*n;++i)
		for(int j=1;j<=2*n;++j)
			sum[i][j]=sum[i-1][j]+sum[i][j-1]-sum[i-1][j-1]+a[i][j];
	int ans=0;
	for(int i=1;i<=n;++i)
		for(int j=1;j<=n;++j){
			int x=i+j-1,y=n-i+j;
			int xl=max(0,x-k-1),yl=max(0,y-k-1),xr=min(2*n,x+k),yr=min(2*n,y+k);
			ans=max(ans,sum[xr][yr]-sum[xl][yr]-sum[xr][yl]+sum[xl][yl]);
		}
	printf("%d\n",ans);
	return 0;
}