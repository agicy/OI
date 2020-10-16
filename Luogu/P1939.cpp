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

const int p=1e9+7;
const int MAXSIZE=3;

inline int add(reg int a,reg int b){
	reg int sum=a+b;
	return sum>=p?sum-p:sum;
}

inline int mul(reg int a,reg int b){
	return 1ll*a*b%p;
}

int n;

struct Matrix{
	int unit[MAXSIZE][MAXSIZE];
	inline Matrix(reg int x=0){
		for(reg int i=0;i<MAXSIZE;++i)
			for(reg int j=0;j<MAXSIZE;++j)
				unit[i][j]=(i==j?x:0);
		return;
	}
	inline Matrix operator*(const Matrix &a)const{
		Matrix res;
		reg int r;
		for(reg int i=0;i<MAXSIZE;++i)
			for(reg int k=0;k<MAXSIZE;++k){
				r=unit[i][k];
				for(reg int j=0;j<MAXSIZE;++j)
					res.unit[i][j]=add(res.unit[i][j],mul(r,a.unit[k][j]));
			}
		return res;
	}
	inline Matrix operator^(reg int exp)const{
		Matrix x=*this,res(1);
		while(exp){
			if(exp&1)
				res=res*x;
			x=x*x;
			exp>>=1;
		}
		return res;
	}
	inline int* operator[](reg int i){
		return unit[i];
	}
};

int main(void){
	reg int T=read();
	while(T--){
		n=read();
		if(n<=3)
			puts("1");
		else{
			static Matrix B,f,ans;
			B[0][0]=B[0][1]=B[0][2]=1;
			f[0][0]=f[0][1]=f[1][2]=f[2][0]=1;
			ans=B*(f^(n-3));
			printf("%d\n",ans[0][0]);
		}
	}
	return 0;
}