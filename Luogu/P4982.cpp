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

const int mod=1e9+7;
const int MAXN=1e7+5;
const int MAXM=7;
const int MAXK=300+5;
const int MAXSIZE=1<<MAXM;

inline int add(reg int a,reg int b){
	reg int sum=a+b;
	return sum>=mod?sum-mod:sum;
}

struct Matrix{
	int n,m,unit[MAXSIZE][MAXSIZE];
	inline Matrix(void){
		n=m=0;
		return;
	}
	inline Matrix(reg int N,reg int M,reg int x=0){
		n=N,m=M;
		for(reg int i=0;i<MAXSIZE;++i)
			for(reg int j=0;j<MAXSIZE;++j)
				unit[i][j]=(i==j)?x:0;
		return;
	}
	inline Matrix operator*(const Matrix& a){
		Matrix res(n,a.m,0);
		reg int r;
		for(reg int i=0;i<n;++i)
			for(reg int k=0;k<m;++k){
				r=unit[i][k];
				if(r)
					for(reg int j=0;j<a.m;++j)
						if(a.unit[k][j])
							res.unit[i][j]=add(res.unit[i][j],1ll*r*a.unit[k][j]%mod);
			}
		return res;
	}
	inline Matrix operator^(reg int exp){
		Matrix res(n,n,1),x=*this;
		while(exp){
			if(exp&1)
				res=res*x;
			x=x*x;
			exp>>=1;
		}
		return res;
	}
	inline int sum(void){
		reg int res=0;
		for(reg int i=0;i<n;++i)
			for(reg int j=0;j<m;++j)
				res=add(res,unit[i][j]);
		return res;
	}
	inline int* operator[](reg int i){
		return unit[i];
	}
};

int n,m,K;
int p[MAXK],U[MAXK];
Matrix c,r;

int main(void){
	n=read(),m=read(),K=read();
	for(reg int i=1;i<=K;++i){
		p[i]=read();
		for(reg int j=1;j<=p[i];++j){
			static int x;
			x=read();
			U[i]|=(1<<(x-1));
		}
	}
	p[K+1]=p[1],U[K+1]=U[1];
	reg int size=(1<<m);
	Matrix start=Matrix(1,size,0);
	for(reg int S=U[1];S;S=U[1]&(S-1))
		++start[0][S];
	--n;
	reg int chunk=n/K,remain=n-chunk*K;
	Matrix tmp(size,size,1);
	for(reg int i=2;i<=remain+1;++i){
		static Matrix f;
		f=Matrix(size,size,0);
		for(reg int pre=U[i-1];pre;pre=U[i-1]&(pre-1))
			for(reg int S=U[i];S;S=U[i]&(S-1))
				if(!(S&pre))
					++f[pre][S];
		tmp=tmp*f;
	}
	r=tmp;
	for(reg int i=remain+2;i<=K+1;++i){
		static Matrix f;
		f=Matrix(size,size,0);
		for(reg int pre=U[i-1];pre;pre=U[i-1]&(pre-1))
			for(reg int S=U[i];S;S=U[i]&(S-1))
				if(!(S&pre))
					++f[pre][S];
		tmp=tmp*f;
	}
	c=tmp;
	Matrix ans=start*(c^chunk);
	if(remain)
		ans=ans*r;
	printf("%d\n",ans.sum());
	return 0;
}
