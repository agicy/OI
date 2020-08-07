#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++)
static char buf[100000],*p1=buf,*p2=buf;
inline int read(void){
	reg char ch=getchar();
	reg int res=0;
	while(ch<'0'||'9'<ch)ch=getchar();
	while('0'<=ch&&ch<='9')res=10*res+ch-'0',ch=getchar();
	return res;
}

const int MAXSIZE=30;

int n,k,m;

inline int add(reg int a,reg int b){
	reg int sum=a+b;
	return sum>=m?sum-m:sum;
}

inline int mul(reg int a,reg int b){
	return a*b%m;
}

struct Matrix{
	int n,m,unit[MAXSIZE][MAXSIZE];
	inline Matrix(reg int N,reg int M,reg int x=0){
		n=N,m=M;
		for(reg int i=0;i<n;++i)
			for(reg int j=0;j<m;++j)
				unit[i][j]=(i==j)?x:0;
		return;
	}
	inline Matrix operator+(const Matrix& a){
		Matrix res=a;
		for(reg int i=0;i<n;++i)
			for(reg int j=0;j<m;++j)
				res.unit[i][j]=add(res.unit[i][j],unit[i][j]);
		return res;
	}
	inline Matrix operator*(const Matrix& a){
		Matrix res(n,a.m);
		reg int r;
		for(reg int i=0;i<n;++i)
			for(reg int k=0;k<m;++k){
				r=unit[i][k];
				for(reg int j=0;j<a.m;++j)
					res.unit[i][j]=add(res.unit[i][j],mul(r,a.unit[k][j]));
			}
		return res;
	}
	inline Matrix operator^(reg int exp){
		Matrix res(n,m,1),x=*this;
		while(exp){
			if(exp&1)
				res=res*x;
			x=x*x;
			exp>>=1;
		}
		return res;
	}
	inline int* operator[](reg int i){
		return unit[i];
	}
	inline void Print(void){
		for(reg int i=0;i<n;++i)
			for(reg int j=0;j<m;++j)
				printf("%d%c",unit[i][j],j==m-1?'\n':' ');
		return;
	}
};

inline Matrix Calc(Matrix a,reg int k){
	if(k==1)
		return a;
	Matrix c(n,n,1);
	c=c+(a^(k>>1));
	c=c*Calc(a,k>>1);
	if(k&1)
		c=c+(a^k);
	return c;
}

int main(void){
	n=read(),k=read(),m=read();
	Matrix A(n,n,0);
	for(reg int i=0;i<n;++i)
		for(reg int j=0;j<n;++j)
			A[i][j]=read();
	Matrix ans=Calc(A,k);
	ans.Print();
	return 0;
}