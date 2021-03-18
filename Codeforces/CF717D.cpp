#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;

const int MAXX=128;
const int MAXSIZE=128;

int n,x;
double p[MAXX];

struct Matrix{
	int n,m;
	double unit[MAXSIZE][MAXSIZE];
	inline Matrix(reg int n,reg int m,reg double x=0):n(n),m(m){
		for(reg int i=0;i<n;++i)
			for(reg int j=0;j<m;++j)
				unit[i][j]=(i==j)?x:0;
		return;
	}
	inline Matrix operator*(const Matrix& a)const{
		Matrix res(n,a.m,0);
		for(reg int i=0;i<n;++i)
			for(reg int k=0;k<m;++k){
				reg double r=unit[i][k];
				for(reg int j=0;j<a.m;++j)
					res.unit[i][j]+=r*a.unit[k][j];
			}
		return res;
	}
	inline Matrix operator^(reg int exp){
		Matrix res=Matrix(n,n,1),x=*this;
		while(exp){
			if(exp&1)
				res=res*x;
			x=x*x;
			exp>>=1;
		}
		return res;
	}
};

int main(void){
	scanf("%d%d",&n,&x);
	for(reg int i=0;i<=x;++i)
		scanf("%lf",&p[i]);
	Matrix f(128,128);
	for(reg int i=0;i<128;++i)
		for(reg int j=0;j<128;++j)
			f.unit[i][j]=p[i^j];
	Matrix A(1,128);
	A.unit[0][0]=1.0;
	Matrix res=A*(f^n);
	printf("%.8lf\n",1.0-res.unit[0][0]);
	return 0;
}