#include<bits/stdc++.h>
using namespace std;
#define reg register
#define MOD 2009

const int MAXN=10+5;

int n,t;
int c[MAXN][MAXN];

const int MAXSIZE=90;

struct Matrix{
	int unit[MAXSIZE][MAXSIZE];
	inline Matrix(void){
		memset(unit,0,sizeof(unit));
		return;
	}
	inline int* operator[](reg int i){
		return unit[i];
	}
	inline Matrix operator~(void){
		for(reg int i=0;i<MAXSIZE;++i)
			for(reg int j=0;j<MAXSIZE;++j)
				unit[i][j]=(i==j);
		return *this;
	}
	inline Matrix operator*(Matrix& a){
		Matrix res;
		for(reg int i=0;i<MAXSIZE;++i)
			for(reg int j=0;j<MAXSIZE;++j)
				for(reg int k=0;k<MAXSIZE;++k)
					res[i][j]=(res[i][j]+unit[i][k]*a[k][j]%MOD)%MOD;
		return res;
	}
	inline Matrix operator^(reg int exp){
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

int main(void){
	scanf("%d%d",&n,&t);
	for(reg int i=1;i<=n;++i){
		for(reg int j=1;j<=8;++j)
			ans[i+j*n-1][i+(j-1)*n-1]=1;
		for(reg int j=1;j<=n;++j){
			static int x;
			scanf("%1d",&x);
			if(x)
				ans[i-1][j+(x-1)*n-1]=1;
		}
	}
	ans=ans^t;
	printf("%d\n",ans[0][n-1]);
	return 0;
}