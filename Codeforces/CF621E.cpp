#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
#define MOD 1000000007
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++)
static char buf[100000],*p1=buf,*p2=buf;
inline int read(void){
	reg char ch=getchar();
	reg int res=0;
	while(ch<'0'||'9'<ch)ch=getchar();
	while('0'<=ch&&ch<='9')res=10*res+ch-'0',ch=getchar();
	return res;
}

const int MAXSIZE=100;

struct Matrix{
	ll unit[MAXSIZE][MAXSIZE];
	inline Matrix(void){
		memset(unit,0,sizeof(unit));
		return;
	}
	inline Matrix(reg ll x){
		for(reg int i=0;i<MAXSIZE;++i)
			for(reg int j=0;j<MAXSIZE;++j)
				unit[i][j]=(i==j)?x:0;
		return;
	}
	inline ll* operator[](reg int i){
		return unit[i];
	}
	inline Matrix operator*(Matrix &a){
		Matrix res;
		for(reg int i=0;i<MAXSIZE;++i)
			for(reg int j=0;j<MAXSIZE;++j)
				for(reg int k=0;k<MAXSIZE;++k)
					res[i][j]=(res[i][j]+unit[i][k]*a[k][j]%MOD)%MOD;
		return res;
	}
	inline Matrix operator^(reg ll exp){
		Matrix res(1),x=*this;
		while(exp){
			if(exp&1)
				res=res*x;
			x=x*x;
			exp>>=1;
		}
		return res;
	}
};

int n,b,K,x;
int T[10];
Matrix ans;

int main(void){
	n=read(),b=read(),K=read(),x=read();
	for(reg int i=1;i<=n;++i)
		++T[read()];
	for(reg int i=0;i<x;++i)
		for(reg int j=0;j<10;++j)
			ans[i][(10*i+j)%x]+=T[j];
	ans=ans^b;
	printf("%lld\n",ans[0][K]);
	return 0;
}