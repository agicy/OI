#include<bits/stdc++.h>
using namespace std;
#define reg register

const int MAXN=55+5;
const int MAXSIZE=100+5;

int n;
int cnt[MAXN],a[MAXN][MAXSIZE];

int main(void){
	scanf("%d",&n);
	reg int m=(n*(n+2)+(n&1)-2)/2;
	printf("%d\n",m);
	for(reg int i=1;i<=m;++i)
		for(reg int j=1;j<=n;++j){
			int x=a[j][cnt[j]];
			if(!x||((int)sqrt(x+i))*((int)sqrt(x+i))==x+i){
				a[j][++cnt[j]]=i;
				break;
			}
	}
	for(reg int i=1;i<=n;++i)
		for(reg int j=1;j<=cnt[i];++j)
			printf("%d%c",a[i][j],j==cnt[i]?'\n':' ');
	return 0;
}
