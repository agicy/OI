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

const int MAXN=100+5;
const int MAXM=2500+5;
const int MAXSIZE=105;

int n,m,k;
int u[MAXM],v[MAXM],t[MAXM];

struct Matrix{
	ll unit[MAXSIZE][MAXSIZE];
	inline Matrix(void){
		memset(unit,0X3F,sizeof(unit));
		return;
	}
	inline Matrix(reg int x){
		for(reg int i=1;i<=n;++i)
			for(reg int j=1;j<=n;++j)
				unit[i][j]=((i==j)?x:0);
		return;
	}
	inline ll* operator[](reg int i){
		return unit[i];
	}
	inline Matrix operator*(const Matrix& a){
		Matrix res;
		for(reg int k=1;k<=n;++k)
			for(reg int i=1;i<=n;++i)
				for(reg int j=1;j<=n;++j)
					res.unit[i][j]=min(res.unit[i][j],unit[i][k]+a.unit[k][j]);
		return res;
	}
	inline Matrix pow(const Matrix& f,reg int exp){
		Matrix res=f,x=*this;
		while(exp){
			if(exp&1)
				res=res*x;
			x=x*x;
			exp>>=1;
		}
		return res;
	}
};

Matrix f;

int main(void){
	n=read(),m=read(),k=read();
	for(reg int i=1;i<=n;++i)
		f[i][i]=0;
	for(reg int i=1;i<=m;++i){
		u[i]=read(),v[i]=read(),t[i]=read();
		f[u[i]][v[i]]=t[i];
	}
	for(reg int k=1;k<=n;++k)
		for(reg int i=1;i<=n;++i)
			for(reg int j=1;j<=n;++j)
				f[i][j]=min(f[i][j],f[i][k]+f[k][j]);
	if(k==0)
		printf("%lld\n",f[1][n]);
	else{
		Matrix M;
		for(reg int k=1;k<=m;++k)
			for(reg int i=1;i<=n;++i)
				for(reg int j=1;j<=n;++j)
					M[i][j]=min(M[i][j],min(f[i][j],f[i][u[k]]+f[v[k]][j]-t[k]));
		M=M.pow(f,k);
		printf("%lld\n",M[1][n]);
	}
	return 0;
}