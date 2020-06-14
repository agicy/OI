#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++)
static char buf[100000],*p1=buf,*p2=buf;
inline ll read(void){
	reg bool f=false;
	reg char ch=getchar();
	reg ll res=0;
	while(ch<'0'||'9'<ch)f|=(ch=='-'),ch=getchar();
	while('0'<=ch&&ch<='9')res=10*res+ch-'0',ch=getchar();
	return f?-res:res;
}

const int MAXSIZE=3;

ll n,m;

struct Matrix{
	ll unit[MAXSIZE][MAXSIZE];
	inline Matrix(void){
		memset(unit,0,sizeof(unit));
		return;
	}
	inline Matrix operator~(void){
		for(reg int i=0;i<MAXSIZE;++i)
			for(reg int j=0;j<MAXSIZE;++j)
				unit[i][j]=(i==j);
		return *this;
	}
	inline ll* operator[](reg int i){
		return unit[i];
	}
	inline Matrix operator*(Matrix& a){
		Matrix res;
		for(reg int i=0;i<MAXSIZE;++i)
			for(reg int j=0;j<MAXSIZE;++j)
				for(reg int k=0;k<MAXSIZE;++k)
					res[i][j]=(res[i][j]+unit[i][k]*a[k][j]%m)%m;
		return res;
	}
	inline Matrix operator^(reg ll exp){
		Matrix res,x=*this;
		~res;
		while(exp){
			if(exp&1)
				res=res*x;
			x=x*x;
			exp>>=1;
		}
		return res;
	}
};

Matrix ans;

inline void Calc(reg ll p,reg ll exp){
	Matrix x;
	x[0][0]=p%m,x[0][1]=x[0][2]=x[1][1]=x[1][2]=x[2][2]=1;
	ans=(x^exp)*ans;
	return;
}

int main(void){
	n=read(),m=read();
	~ans;
	reg ll r=10;
	while(r<=n)
		Calc(r,r-(r/10)),r*=10;
	Calc(r,n-r/10+1);
	printf("%lld\n",ans[0][2]);
	return 0;
}