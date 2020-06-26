#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
#define MOD 1000000007

const int MAXK=500+5;
const int MAXSIZE=500+5;

struct Matrix{
	int n,m;
	int unit[MAXK][MAXK];
	inline Matrix(reg int n,reg int m,reg int x=0):n(n),m(m){
		for(reg int i=0;i<n;++i)
			for(reg int j=0;j<m;++j)
				unit[i][j]=((i==j)?x:0);
		return;
	}
	inline Matrix operator*(const Matrix& a){
		Matrix res(n,a.m);
		reg int r;
		for(reg int i=0;i<n;++i)
			for(reg int k=0;k<m;++k){
				r=unit[i][k];
				for(reg int j=0;j<a.m;++j)
					res.unit[i][j]=(res.unit[i][j]+1ll*r*a.unit[k][j]%MOD)%MOD;
			}
		return res;
	}
	inline Matrix operator^(reg ll exp){
		Matrix res(n,m,1),x=*this;
		while(exp){
			if(exp&1)
				res=res*x;
			x=x*x;
			exp>>=1;
		}
		return res;
	}
};

char str[256];
ll n;
int K;
int C[MAXK][MAXK];

int main(void){
	scanf("%lld%d",&n,&K);
	C[1][0]=C[1][1]=1;
	for(reg int i=2;i<=K;++i){
		C[i][0]=C[i][i]=1;
		for(reg int j=1;j<=i;++j)
			C[i][j]=(C[i-1][j-1]+C[i-1][j])%MOD;
	}
	Matrix T(K+2,K+2);
	T.unit[0][0]=2,T.unit[1][0]=1;
	for(reg int i=1;i<=K;++i)
		for(reg int j=i;j<=K+1;++j)
			T.unit[j][i]=C[K-i+1][j-i];
	T.unit[K+1][K+1]=1;
	Matrix ans(1,K+2);
	for(reg int i=1;i<=K+1;++i)
		ans.unit[0][i]=1;
	Matrix X=T^(n-1);
	ans=ans*X;
	reg int ans1=ans.unit[0][0];
	ans=ans*T;
	reg int ans2=ans.unit[0][0];
	printf("%d\n",(ans2-ans1+MOD)%MOD);
	return 0;
}