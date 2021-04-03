#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;

const int MAXN=150+5;
const int MAXM=150+5;
const int MAXK=20+5;
const int mod=12345678;

int n,m,K;
int f[MAXN][MAXM][MAXK][MAXK];

inline int add(reg int a,reg int b){
	reg int sum=a+b;
	return sum>=mod?sum-mod:sum;
}

int main(void){
	scanf("%d%d%d",&n,&m,&K);
	f[0][1][0][1]=f[1][0][1][0]=1;
	for(reg int i=0;i<=n;++i)
		for(reg int j=0;j<=m;++j)
			for(reg int k=0;k<=K;++k)
				for(reg int l=0;l<=K;++l){
					f[i+1][j][k+1][max(l-1,0)]=add(f[i+1][j][k+1][max(l-1,0)],f[i][j][k][l]);
					f[i][j+1][max(k-1,0)][l+1]=add(f[i][j+1][max(k-1,0)][l+1],f[i][j][k][l]);
				}
	reg int ans=0;
	for(reg int i=0;i<=K;++i)
		for(reg int j=0;j<=K;++j)
			ans=add(ans,f[n][m][i][j]);
	printf("%d\n",ans);
	return 0;
}