#include"hexagon.h"
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

const int MAXN=2e5+5;
const int mod=1e9+7;

inline int add(int a,int b){
	a+=b;
	return a>=mod?a-mod:a;
}

inline int sub(int a,int b){
	a-=b;
	return a<0?a+mod:a;
}

inline int fpow(int x,int exp){
	int res=1;
	while(exp){
		if(exp&1)
			res=1ll*res*x%mod;
		x=1ll*x*x%mod;
		exp>>=1;
	}
	return res;
}

const int inv2=fpow(2,mod-2);
const int inv6=fpow(6,mod-2);

inline int getSum1(int x){
	return 1ll*x*(x+1)%mod*inv2%mod;
}

inline int getSum2(int x){
	return 1ll*x*(x+1)%mod*add(2ll*x%mod,1)%mod*inv6%mod;
}

int n,a,b,d[MAXN],l[MAXN];

int draw_territory(int N,int A,int B,std::vector<int> D,std::vector<int> L) {
	n=N,a=A,b=B;
	for(int i=1;i<=n;++i)
		d[i]=D[i-1],l[i]=L[i-1];
	int len=l[1];
	int ans1=getSum1(len+1),ans2=add(getSum2(len),getSum1(len));
	return add(1ll*ans1*a%mod,1ll*ans2*b%mod);
}