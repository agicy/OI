#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
typedef unsigned long long ull;
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++)
static char buf[1<<21],*p1=buf,*p2=buf;
inline int read(void){
	reg char ch=getchar();
	reg int res=0;
	while(!isdigit(ch))ch=getchar();
	while(isdigit(ch))res=10*res+(ch^'0'),ch=getchar();
	return res;
}

inline ll readll(void){
	reg char ch=getchar();
	reg ll res=0;
	while(!isdigit(ch))ch=getchar();
	while(isdigit(ch))res=10*res+(ch^'0'),ch=getchar();
	return res;
}

const int MAXK=100;
const int MAXSIZE=MAXK;

struct Matrix{
	int n,m;
	ull unit[MAXSIZE][MAXSIZE];
	inline Matrix(reg int n,reg int m,reg ull x=0):n(n),m(m){
		for(reg int i=0;i<n;++i)
			for(reg int j=0;j<m;++j)
				unit[i][j]=(i==j)?x:0;
		return;
	}
	inline Matrix operator*(const Matrix& a)const{
		Matrix res(n,a.m,0);
		for(reg int i=0;i<n;++i)
			for(reg int k=0;k<m;++k){
				reg ull r=unit[i][k];
				for(reg int j=0;j<a.m;++j)
					res.unit[i][j]|=r&a.unit[k][j];
			}
		return res;
	}
	inline Matrix operator^(reg int exp){
		Matrix res(n,n,-1),x=*this;
		while(exp){
			if(exp&1)
				res=res*x;
			x=x*x;
			exp>>=1;
		}
		return res;
	}
};

int n,k;

int main(void){
	n=read(),k=read();
	Matrix A(1,k,0);
	for(reg int i=0;i<k;++i)
		A.unit[0][i]=readll();
	Matrix f(k,k,0);
	for(reg int i=0;i<k;++i)
		f.unit[i][k-1]=readll();
	for(reg int i=1;i<k;++i)
		f.unit[i][i-1]=-1ull;
	Matrix res=A*(f^n);
	printf("%lld\n",res.unit[0][0]);
	return 0;
}