#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++)
static char buf[100000],*p1=buf,*p2=buf;
inline int read(void){
	reg char ch=getchar();
	reg int res=0;
	while(!isdigit(ch))ch=getchar();
	while(isdigit(ch))res=10*res+(ch^'0'),ch=getchar();
	return res;
}

const int MAXN=50;
const int mod=30011;

inline int add(reg int a,reg int b){
	a+=b;
	return a>=mod?a-mod:a;
}

const int MAXSIZE=2*MAXN;

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
	inline Matrix operator^(reg int exp)const{
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

int n,m;

int main(void){
	n=read(),m=read();
	Matrix f(2*n,2*n);
	for(reg int i=0;i<n;++i){
		f.unit[i+n][i]=f.unit[i][i+n]=1;
		if(i!=0)
			f.unit[i-1][i]=1;
		f.unit[i][i]=1;
		if(i!=n-1)
			f.unit[i+1][i]=1;
	}
	Matrix a(1,2*n);
	a.unit[0][0]=1,a.unit[0][n>1?1:0]=1;
	Matrix res=a*(f^(m-2));
	printf("%d\n",res.unit[0][n-1]);
	return 0;
}