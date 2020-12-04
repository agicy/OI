#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++)
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
	while(isdigit(ch))res=10ll*res+(ch^'0'),ch=getchar();
	return f?-res:res;
}

const int MAXN=100;
const int p=1e9+7;

inline int add(reg int a,reg int b){
	a+=b;
	return a>=p?a-p:a;
}

inline int mul(reg int a,reg int b){
	return 1ll*a*b%p;
}

struct Matrix{
	int n,unit[MAXN][MAXN];
	inline Matrix(reg int s,reg int x=0){
		n=s;
		for(reg int i=0;i<n;++i)
			for(reg int j=0;j<n;++j)
				unit[i][j]=(i==j)?x:0;
		return;
	}
	inline Matrix operator*(const Matrix& a)const{
		Matrix res(n);
		for(reg int i=0;i<n;++i)
			for(reg int k=0;k<n;++k){
				reg int r=unit[i][k];
				for(reg int j=0;j<n;++j)
					res.unit[i][j]=add(res.unit[i][j],mul(r,a.unit[k][j]));
			}
		return res;
	}
	inline Matrix operator^(reg ll exp){
		Matrix res(n,1),x=*this;
		while(exp){
			if(exp&1)
				res=res*x;
			x=x*x;
			exp>>=1;
		}
		return res;
	}
};

int main(void){
	reg int n=read();
	reg ll k=readll();
	Matrix M(n);
	for(reg int i=0;i<n;++i)
		for(reg int j=0;j<n;++j)
			M.unit[i][j]=(read()+p)%p;
	Matrix ans=M^k;
	for(reg int i=0;i<n;++i)
		for(reg int j=0;j<n;++j)
			printf("%d%c",ans.unit[i][j],j==n-1?'\n':' ');
	return 0;
}