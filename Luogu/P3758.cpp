#include<bits/stdc++.h>
using namespace std;
#define reg register
#define MOD 2017
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++)
static char buf[100000],*p1=buf,*p2=buf;
inline int read(void){
	reg char ch=getchar();
	reg int res=0;
	while(ch<'0'||'9'<ch)ch=getchar();
	while('0'<=ch&&ch<='9')res=res*10+ch-'0',ch=getchar();
	return res;
}

const int MAXSIZE=30+5;

struct Matrix{
	int unit[MAXSIZE][MAXSIZE];
	inline Matrix(reg int x=0){
		for(reg int i=0;i<MAXSIZE;++i)
			for(reg int j=0;j<MAXSIZE;++j)
				unit[i][j]=(i==j?x:0);
		return;
	}
	inline int* operator[](reg int i){
		return unit[i];
	}
	inline Matrix operator*(Matrix& a)const{
		Matrix res;
		reg int r;
		for(reg int i=0;i<MAXSIZE;++i)
			for(reg int k=0;k<MAXSIZE;++k){
				r=unit[i][k];
				for(reg int j=0;j<MAXSIZE;++j)
					res[i][j]=(res[i][j]+r*a[k][j]%MOD)%MOD;
			}
		return res;
	}
	inline Matrix operator^(reg int exp){
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

int n,m;

int main(void){
	n=read(),m=read();
	Matrix G;
	for(reg int i=1;i<=m;++i){
		static int u,v;
		u=read(),v=read();
		G[u][v]=G[v][u]=1;
	}
	for(reg int i=1;i<=n;++i)
		G[i][0]=G[i][i]=1;
	G[0][0]=1;
	reg int t=read();
	G=G^t;
	int ans=0;
	for(reg int i=0;i<=n;++i)
		ans=(ans+G[1][i])%MOD;
	printf("%d\n",ans);
	return 0;
}