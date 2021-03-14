#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;

inline int max(reg int a,reg int b){
	return a>b?a:b;
}

inline int add(reg int a,reg int b,reg int mod){
	a+=b;
	return a>=mod?a-mod:a;
}

const int MAXN=1e7+5;

int n,A,B,C;
int a[MAXN];

int main(void){
	const int mod=100000001;
	scanf("%d%d%d%d%d",&n,&A,&B,&C,&a[1]);
	A%=mod,B%=mod;
	reg double ans=0;
	for(reg int i=2;i<=n;++i){
		a[i]=add(1ll*a[i-1]*A%mod,B,mod);
		ans+=1.0/max(a[i-1]%C+1,a[i]%C+1);
	}
	ans+=1.0/max(a[1]%C+1,a[n]%C+1);
	printf("%.3lf\n",ans);
	return 0;
}