#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;

const int mod=1e9+7;

inline int add(reg int a,reg int b){
	a+=b;
	return a>=mod?a-mod:a;
}

inline int sub(reg int a,reg int b){
	a-=b;
	return a<0?a+mod:a;
}

const int MAXM=100;
const int MAXSIZE=MAXM;

struct Matrix{
	int n,m,unit[MAXSIZE][MAXSIZE];
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
	inline Matrix operator^(reg ll exp){
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

ll n;
int m;

int main(void){
	scanf("%lld%d",&n,&m);
	Matrix f(m,m);
	for(reg int i=0;i<m;++i)
		f.unit[i][i+1]=1;
	f.unit[0][0]=1,f.unit[m-1][0]=1;
	Matrix A(1,m);
	A.unit[0][0]=1;
	Matrix res=A*(f^n);
	printf("%d\n",res.unit[0][0]);
	return 0;
}