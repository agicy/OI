#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
#define getchar()(p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++)
static char buf[100000],*p1=buf,*p2=buf;
inline int read(void){
	reg bool f=false;
	reg char ch=getchar();
	reg int res=0;
	while(!isdigit(ch))f|=(ch=='-'),ch=getchar();
	while(isdigit(ch))res=10*res+(ch^'0'),ch=getchar();
	return f?-res:res;
}

inline ll readll(void){
	reg bool f=false;
	reg char ch=getchar();
	reg ll res=0;
	while(!isdigit(ch))f|=(ch=='-'),ch=getchar();
	while(isdigit(ch))res=10*res+(ch^'0'),ch=getchar();
	return f?-res:res;
}

const int mod=998244353;

inline int add(reg int a,reg int b){
	a+=b;
	return a>=mod?a-mod:a;
}

inline int sub(reg int a,reg int b){
	a-=b;
	return a<0?a+mod:a;
}

inline int fpow(reg int x,reg int exp){
	reg int res=1;
	while(exp){
		if(exp&1)
			res=1ll*res*x%mod;
		x=1ll*x*x%mod;
		exp>>=1;
	}
	return res;
}

ll n;
int m;

namespace Subtask1{
	const int MAXN=5e6+5;
	int fac[MAXN],invfac[MAXN];
	int f[MAXN];
	inline void Init(reg int n){
		fac[0]=1;
		for(reg int i=1;i<=n;++i)
			fac[i]=1ll*fac[i-1]*i%mod;
		invfac[n]=fpow(fac[n],mod-2);
		for(reg int i=n-1;i>=0;--i)
			invfac[i]=1ll*(i+1)*invfac[i+1]%mod;
		return;
	}
	inline int binom(reg int n,reg int m){
		return 1ll*fac[n]*invfac[m]%mod*invfac[n-m]%mod;
	}
	inline void Solve(void){
		f[0]=1;
		for(reg int i=1;i<=n;++i){
			if(i-m>=0)
				f[i]=add(f[i],f[i-m]);
			if(i-(m-1)>=0)
				f[i]=add(f[i],f[i-(m-1)]);
		}
		reg int sum=0;
		Init(n);
		for(reg int i=0;i<=n;++i)
			sum=add(sum,1ll*f[i]*binom(n,i)%mod);
		printf("%d\n",sum);
		return;
	}
}

namespace Subtask3{
	const int MAXSIZE=20+5;
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
		inline void print(void)const{
			for(reg int i=0;i<n;++i)
				for(reg int j=0;j<m;++j)
					printf("%d%c",unit[i][j],j==m-1?'\n':' ');
			return;
		}
	};
	inline void Solve(void){
		Matrix f(m,m,0);
		f.unit[m-1][0]=f.unit[m-2][0]=1;
		for(reg int i=0;i<m-1;++i)
			f.unit[i][i+1]=1;
		for(reg int i=0;i<m;++i)
			++f.unit[i][i];
		Matrix A(1,m,0);
		A.unit[0][0]=1;
		Matrix res=A*(f^n);
		reg int ans=res.unit[0][0];
		printf("%d\n",ans);
		return;
	}
}

int main(void){
	n=readll(),m=read();
	if(n<=5e6&&m<=1e3)
		//puts("S1"),
		Subtask1::Solve();
	else if(m<=20)
		//puts("S3"),
		Subtask3::Solve();
	return 0;
}