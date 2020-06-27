#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
#define MOD 19260817
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++)
static char buf[100000],*p1=buf,*p2=buf;
inline int read(void){
	reg char ch=getchar();
	reg int res=0;
	while(ch<'0'||'9'<ch)ch=getchar();
	while('0'<=ch&&ch<='9')res=10*res+ch-'0',ch=getchar();
	return res;
}

inline int add(reg int a,reg int b){
	reg int sum=a+b;
	return sum>=MOD?sum-MOD:sum;
}

inline int mul(reg int a,reg int b){
	return 1ll*a*b%MOD;
}

const int MAXSIZE=3;

struct Matrix{
	int unit[MAXSIZE][MAXSIZE];
	inline Matrix(reg int x=0){
		for(reg int i=0;i<MAXSIZE;++i)
			for(reg int j=0;j<MAXSIZE;++j)
				unit[i][j]=((i==j)?x:0);
		return;
	}
	inline Matrix operator*(const Matrix& a){
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
	inline int* operator[](reg int i){
		return unit[i];
	}
};

int n;

inline Matrix POW(reg int n){
	Matrix c,d;
	c[0][0]=c[0][1]=c[0][2]=c[1][0]=c[2][1]=1;
	c[1][1]=c[1][2]=c[2][0]=c[2][2]=0;
	if(n==1)
		return c;
	d=POW(n>>1);
	if(n&1)
		return d*d*c;
	else
		return d*d;
}

int main(void){
	reg int m=read();
	while(m--){
		n=read();
		Matrix ans=POW(n);
		printf("%d\n",add(ans[0][0],ans[0][1]));
	}
	return 0;
}