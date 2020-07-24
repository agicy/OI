#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef unsigned long long ull;

const ull p=7528443412579576937ull;

ull b,d,n;

inline ull add(reg ull a,reg ull b){
	reg ull sum=a+b;
	return sum>=p?sum-p:sum;
}

inline ull mul(reg ull a,reg ull b){
	reg ull res=0;
	while(b){
		if(b&1)
			res=add(res,a);
		a=add(a,a);
		b>>=1;
	}
	return res;
}

inline ull pow(reg ull x,reg ull exp){
	reg ull res=1;
	while(exp){
		if(exp&1)
			res=mul(res,x);
		x=mul(x,x);
		exp>>=1;
	}
	return res;
}

const int MAXSIZE=2;

struct Matrix{
	ull unit[MAXSIZE][MAXSIZE];
	inline Matrix(reg ull x=0){
		for(reg int i=0;i<MAXSIZE;++i)
			for(reg int j=0;j<MAXSIZE;++j)
				unit[i][j]=(i==j)?x:0;
		return;
	}
	inline Matrix operator*(const Matrix& a){
		Matrix res(0);
		reg ull r;
		for(reg int i=0;i<MAXSIZE;++i)
			for(reg int k=0;k<MAXSIZE;++k){
				r=unit[i][k];
				for(reg int j=0;j<MAXSIZE;++j)
					res.unit[i][j]=add(res.unit[i][j],mul(r,a.unit[k][j]));
			}
		return res;
	}
	inline Matrix operator^(reg ull exp){
		Matrix res(1),x=*this;
		while(exp){
			if(exp&1)
				res=res*x;
			x=x*x;
			exp>>=1;
		}
		return res;
	}
	inline ull* operator[](reg int i){
		return unit[i];
	}
};

Matrix f,base;

int main(void){
	scanf("%llu%llu%llu",&b,&d,&n);
	if(n==0)
		puts("1");
	else{
		reg ull A=b,B=add(d>>2,p-mul((b+1ull)>>1ull,(b-1ull)>>1ull));
		f[0][0]=A,f[0][1]=1,f[1][0]=B;
		base[0][0]=b,base[0][1]=2;
		Matrix ans(0);
		ans=base*(f^(n-1));
		if((!(n&1))&&d!=mul(b,b))
			printf("%llu\n",add(ans[0][0],p-1));
		else
			printf("%llu\n",ans[0][0]%p);
	}
	return 0;
}
