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

const int MAXN=100+5;
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

struct Matrix{
	int n,m;
	int unit[MAXN][MAXN];
	inline Matrix(reg int n=0,reg int m=0,reg int x=0):n(n),m(m){
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
};

int n,k;
int a[MAXN];

int main(void){
	n=read(),k=read();
	reg int cnt0=0;
	for(reg int i=1;i<=n;++i){
		a[i]=read();
		if(!a[i])
			++cnt0;
	}
	reg int cnt=0;
	for(reg int i=1;i<=cnt0;++i)
		if(!a[i])
			++cnt;
	Matrix A(1,cnt0+1,0),f(cnt0+1,cnt0+1);
	A.unit[0][cnt]=1;
	reg int Inv=fpow(n*(n-1)/2,mod-2);
	for(reg int i=0;i<=cnt0;++i){
		if(i)
			f.unit[i-1][i]=1ll*(cnt0-i+1)*(cnt0-i+1)%mod*Inv%mod;
		f.unit[i][i]=add(1ll*add(1ll*i*(cnt0-i)%mod,1ll*(cnt0-i)*(n-(cnt0<<1)+i)%mod)*Inv%mod,1ll*add(1ll*(n-cnt0)*(n-cnt0-1)/2%mod*Inv%mod,1ll*cnt0*(cnt0-1)/2%mod*Inv%mod));
		if(i!=cnt0)
			f.unit[i+1][i]=1ll*(i+1)*(n-(cnt0<<1)+i+1)%mod*Inv%mod;
	}
	Matrix res=A*(f^k);
	printf("%d\n",res.unit[0][cnt0]);
	return 0;
}