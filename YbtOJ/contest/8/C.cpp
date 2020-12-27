#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;

const int MAXN=200+5;
const int MAXK=6+5;

int n,k,f[MAXN][MAXK];

int main(void){
	scanf("%d%d",&n,&k);
	for(reg int i=1;i<=n;++i)
		f[i][1]=f[i][0]=1;
	for(reg int i=2;i<=n;++i)
		for(reg int j=2;j<=k;++j)
			if(i>j)
				f[i][j]=f[i-1][j-1]+f[i-j][j];
			else
				f[i][j]=f[i-1][j-1];
	printf("%d\n",f[n][k]);
	return 0;
}