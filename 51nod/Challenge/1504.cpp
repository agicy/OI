#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;

const int MAXN=100+5;
const int MAXM=100+5;

int n,m;
int a[MAXN][MAXM];

int main(void){
	scanf("%d%d",&n,&m);
	for(reg int i=1;i<=n;++i)
		for(reg int j=1;j<=m;++j)
			scanf("%d",&a[i][j]);
	printf("%d %d\n",m,n);
	for(reg int i=1;i<=m;++i)
		for(reg int j=1;j<=n;++j)
			printf("%d%c",a[j][i],j==n?'\n':' ');
	return 0;
}