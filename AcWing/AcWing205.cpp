#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
#define MOD 10000
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

const int MAXSIZE=2+1;

struct Matrix{
	ll unit[MAXSIZE][MAXSIZE];
	inline Matrix(void){
		memset(unit,0,sizeof(unit));
		return;
	}
	inline Matrix(const ll a[]){
		reg int cnt=0;
		for(reg int i=1;i<MAXSIZE;++i)
			for(reg int j=1;j<MAXSIZE;++j)
				unit[i][j]=a[cnt++];
		return;
	}
	inline Matrix operator*(const Matrix& a)const{
		Matrix res;
		for(reg int i=1;i<MAXSIZE;++i)
			for(reg int j=1;j<MAXSIZE;++j)
				for(reg int k=1;k<MAXSIZE;++k)
					res.unit[i][j]=(res.unit[i][j]+unit[i][k]*a.unit[k][j]%MOD)%MOD;
		return res;
	}
};

ll n;
const ll Ans[]={1,1,0,0},Base[]={1,1,1,0};

inline Matrix pow(Matrix,reg ll);

int main(void){
	while(true){
		n=read();
		if(n==-1)
			exit(0);
		else if(n==0)
			puts("0");
		else if(n<=2)
			puts("1");
		else{
			Matrix ans=Ans,base=Base,res;
			res=ans*pow(base,n-2);
			printf("%lld\n",res.unit[1][1]%MOD);
		}
	}
	return 0;
}

inline Matrix pow(Matrix x,reg ll exp){
	Matrix res=x;
	--exp;
	while(exp){
		if(exp&1)
			res=res*x;
		x=x*x;
		exp>>=1;
	}
	return res;
}
