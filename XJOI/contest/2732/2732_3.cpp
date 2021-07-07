#pragma GCC optimize("Ofast")
#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;

bool st;

inline int max(reg int a,reg int b){
	return a>b?a:b;
}

const int MAXN=3.5e3+5;

int n,mod;

inline int add(reg int a,reg int b){
	a+=b;
	return a>=mod?a-mod:a;
}

int f[MAXN][MAXN];

bool ed;

int main(void){
	scanf("%d%d",&n,&mod);
	f[0][0]=1;
	for(reg int i=1;i<=n;++i){
		f[0][i]=f[i-1][0];
		f[i][0]=add(f[i-1][0],f[i-1][0]);
	}
	for(reg int sum=2;sum<n*2;++sum)
		for(reg int i=max(1,sum-n),j=sum-i;i<=n&&1<=j;++i,--j)
			f[i][j]=add(add(f[i-1][j],f[i-1][j]),1ll*(i+1)*f[j-1][i]%mod);
	printf("%d\n",add(f[n-1][n],f[n-1][n]));
	fprintf(stderr,"%.3lf s\n",1.0*clock()/CLOCKS_PER_SEC);
	fprintf(stderr,"%.3lf MiB\n",(&ed-&st)/1048576.0);
	return 0;
}