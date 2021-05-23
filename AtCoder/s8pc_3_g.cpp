#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;

const int mod=998244353;

inline int add(reg int a,reg int b){
	a+=b;
	return a>=mod?a-mod:a;
}

inline int sub(reg int a,reg int b){
	a-=b;
	return a<0?a+mod:a;
}

const int MAXN=2e5+5;
const int MAXSIZE=2;

struct Matrix{
	int n,m;
	int unit[MAXSIZE][MAXSIZE];
	inline Matrix(reg int n,reg int m,reg int x=0):n(n),m(m){
		for(reg int i=0;i<n;++i)
			for(reg int j=0;j<m;++j)
				unit[i][j]=(i==j)?x:0;
		return;
	}
	inline Matrix operator*(const Matrix& a)const{
		Matrix res(n,a.m,0);
		for(reg int i=0;i<n;++i)
			for(reg int k=0;k<m;++k){
				reg int r=unit[i][k];
				for(reg int j=0;j<a.m;++j)
					res.unit[i][j]=add(res.unit[i][j],1ll*r*a.unit[k][j]%mod);
			}
		return res;
	}
	inline Matrix operator^(reg ll exp)const{
		Matrix res(n,n,1),x=*this;
		while(exp){
			if(exp&1)
				res=res*x;
			x=x*x;
			exp>>=1;
		}
		return res;
	}
};

inline int getFib(reg ll x){
	Matrix bas(1,2),fib(2,2);
	bas.unit[0][0]=1,bas.unit[0][1]=0;
	fib.unit[0][0]=1,fib.unit[0][1]=1;
	fib.unit[1][0]=1,fib.unit[1][1]=0;
	return (bas*(fib^(x-1))).unit[0][0];
}

int n;
ll m;
int fib[MAXN<<1],inv[MAXN];

int main(void){
	scanf("%d%lld",&n,&m);
	fib[1]=1;
	for(reg int i=2;i<=(n<<1);++i)
		fib[i]=add(fib[i-1],fib[i-2]);
	inv[1]=1;
	for(reg int i=2;i<=n;++i)
		inv[i]=1ll*(mod-mod/i)*inv[mod%i]%mod;
	reg int ans=getFib(m+((n-1)<<1));
	m%=mod;
	reg int binom=1;
	for(reg int i=1;i<n;++i){
		ans=sub(ans,1ll*binom*fib[(n-i)<<1]%mod);
		binom=1ll*binom*(m++)%mod*inv[i]%mod;
	}
	printf("%d\n",ans);
	return 0;
}