#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++)
static char buf[100000],*p1=buf,*p2=buf;
inline ll read(void){
	reg char ch=getchar();
	reg ll res=0;
	while(ch<'0'||'9'<ch)ch=getchar();
	while('0'<=ch&&ch<='9')res=10ll*res+ch-'0',ch=getchar();
	return res;
}

const int MAXSIZE=2;

ll mod,a,c,x0,n,g;

inline ll add(reg ll a,reg ll b,reg ll mod){
	reg ll sum=a+b;
	return sum>=mod?sum-mod:sum;
}

inline ll mul(reg ll a,reg ll b,reg ll mod){
	reg ll res=0;
	while(b){
		if(b&1)
			res=add(res,a,mod);
		a=add(a,a,mod);
		b>>=1;
	}
	return res;
}

struct Matrix{
	int n,m;
	ll unit[MAXSIZE][MAXSIZE];
	inline Matrix(reg int N,reg int M,reg ll x=0){
		n=N,m=M;
		for(reg int i=0;i<n;++i)
			for(reg int j=0;j<m;++j)
				unit[i][j]=(i==j)?x:0;
		return;
	}
	inline Matrix operator*(const Matrix& a){
		Matrix res(n,a.m);
		reg ll r;
		for(reg int i=0;i<n;++i)
			for(reg int k=0;k<m;++k){
				r=unit[i][k];
				for(reg int j=0;j<a.m;++j)
					res.unit[i][j]=add(res.unit[i][j],mul(r,a.unit[k][j],mod),mod);
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
	inline ll* operator[](reg int i){
		return unit[i];
	}
};

int main(void){
	mod=read(),a=read(),c=read(),x0=read(),n=read(),g=read();
	a%=mod,c%=mod,x0%=mod;
	Matrix A(1,2,0);
	A[0][0]=x0,A[0][1]=1;
	Matrix f(2,2,0);
	f[0][0]=a,f[1][0]=c,f[1][1]=1;
	Matrix ans=A*(f^n);
	printf("%lld\n",ans[0][0]%g);
	return 0;
}