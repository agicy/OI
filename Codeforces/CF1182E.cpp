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

inline ll readll(void){
	reg char ch=getchar();
	reg ll res=0;
	while(!isdigit(ch))ch=getchar();
	while(isdigit(ch))res=10*res+(ch^'0'),ch=getchar();
	return res;
}

inline int add(reg int a,reg int b,reg int mod){
	a+=b;
	return a>=mod?a-mod:a;
}

inline int sub(reg int a,reg int b,reg int mod){
	a-=b;
	return a<0?a+mod:a;
}

inline int fpow(reg int x,reg int exp,reg int mod){
	reg int res=1;
	while(exp){
		if(exp&1)
			res=1ll*res*x%mod;
		x=1ll*x*x%mod;
		exp>>=1;
	}
	return res;
}

const int MAXSIZE=5;
const int pmod=1e9+6;
const int mod=1e9+7;

struct Matrix{
	int unit[MAXSIZE][MAXSIZE];
	inline Matrix(reg int x=0){
		for(reg int i=0;i<MAXSIZE;++i)
			for(reg int j=0;j<MAXSIZE;++j)
				unit[i][j]=(i==j)?x:0;
		return;
	}
	inline Matrix operator*(const Matrix& a)const{
		Matrix res(0);
		for(reg int i=0;i<MAXSIZE;++i)
			for(reg int k=0;k<MAXSIZE;++k){
				reg int r=unit[i][k];
				if(r)
					for(reg int j=0;j<MAXSIZE;++j)
						res.unit[i][j]=add(res.unit[i][j],1ll*r*a.unit[k][j]%pmod,pmod);
			}
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
	inline int* operator[](reg int i){
		return unit[i];
	}
};

inline int BSGS(reg int a,reg int b,reg int p){
	unordered_map<int,int> M;
	reg int m=ceil(sqrt(p));
	for(reg int i=1;i<=m;++i){
		b=1ll*b*a%p;
		M[b]=i;
	}
	reg int tmp=fpow(a,m,p);
	b=1;
	for(reg int i=1;i<=m;++i){
		b=1ll*b*tmp%p;
		if(M.count(b))
			return i*m-M[b];
	}
	return -1;
}

ll n;
int f1,f2,f3,c;

int main(void){
	n=readll(),f1=read(),f2=read(),f3=read(),c=read();
	if(n<=3)
		switch(n){
			case 1:{
				printf("%d\n",f1);
				break;
			}
			case 2:{
				printf("%d\n",f2);
				break;
			}
			case 3:{
				printf("%d\n",f3);
				break;
			}
		}
	else{
		reg int g1=BSGS(5,f1,mod),g2=BSGS(5,f2,mod),g3=BSGS(5,f3,mod),x=BSGS(5,c,mod);
		Matrix A(0),f(0);
		A[0][0]=g3,A[0][1]=g2,A[0][2]=g1,A[0][3]=3,A[0][4]=1;
		f[0][0]=1,f[0][1]=1,f[1][0]=1,f[1][2]=1,f[2][0]=1,f[3][0]=2ll*x%pmod,f[3][3]=1,f[4][0]=sub(0,4ll*x%pmod,pmod),f[4][3]=1,f[4][4]=1;
		printf("%d\n",fpow(5,(A*(f^(n-3))).unit[0][0],mod));
	}
	return 0;
}