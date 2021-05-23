#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;

const int MAXN=2e3+5;

int n,mod;
int f[MAXN*3][MAXN*6];

inline int add(reg int a,reg int b){
	a+=b;
	return a>=mod?a-mod:a;
}

inline int sub(reg int a,reg int b){
	a-=b;
	return a<0?a+mod:a;
}

int main(void){
	scanf("%d%d",&n,&mod);
	n*=3;
	reg int Delta=n;
	f[0][Delta]=1;
	for(reg int i=0;i<n;++i)
		for(reg int j=-i;j<=i;++j)
			if(f[i][j+Delta]){
				f[i+1][j+1+Delta]=add(f[i+1][j+1+Delta],f[i][j+Delta]);
				f[i+2][j-1+Delta]=add(f[i+2][j-1+Delta],1ll*f[i][j+Delta]*(i+1)%mod);
				f[i+3][j+Delta]=add(f[i+3][j+Delta],1ll*f[i][j+Delta]*(i+1)%mod*(i+2)%mod);
			}
	reg int ans=0;
	for(reg int i=0;i<=n;++i)
		ans=add(ans,f[n][i+Delta]);
	printf("%d\n",ans);
	return 0;
}