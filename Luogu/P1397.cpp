#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
#define MOD 1000000007

struct Matrix{
	int unit[2][2];
	inline Matrix(reg int x=0){
		unit[0][0]=unit[1][1]=x;
		unit[0][1]=unit[1][0]=0;
		return;
	}
	inline Matrix operator*(const Matrix& a){
		Matrix res;
		res.unit[0][0]=(1ll*unit[0][0]*a.unit[0][0]%MOD+1ll*unit[0][1]*a.unit[1][0]%MOD)%MOD;
		res.unit[0][1]=(1ll*unit[0][0]*a.unit[0][1]%MOD+1ll*unit[0][1]*a.unit[1][1]%MOD)%MOD;
		res.unit[1][0]=(1ll*unit[1][0]*a.unit[0][0]%MOD+1ll*unit[1][1]*a.unit[1][0]%MOD)%MOD;
		res.unit[1][1]=(1ll*unit[1][0]*a.unit[0][1]%MOD+1ll*unit[1][1]*a.unit[1][1]%MOD)%MOD;
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

const int MAXSIZE=1000000+5;

char n[MAXSIZE],m[MAXSIZE];
int a,b,c,d;

inline Matrix GetExp(Matrix x,reg char str[],reg int len){
	Matrix res(1);
	for(reg int i=0;i<len;++i){
		reg int b=str[i]-'0';
		res=res^10;
		if(b)
			res=res*(x^b);
	}
	return res;
}

int main(void){
	scanf("%s%s%d%d%d%d",n,m,&a,&b,&c,&d);
	Matrix f,A,B;
	f.unit[0][0]=f.unit[0][1]=1,f.unit[1][0]=f.unit[1][1]=0;
	A.unit[0][0]=a,A.unit[0][1]=0,A.unit[1][0]=b,A.unit[1][1]=1;
	B.unit[0][0]=c,B.unit[0][1]=0,B.unit[1][0]=d,B.unit[1][1]=1;
	reg int nl=strlen(n);
	for(reg int i=nl-1;i>=0;--i)
		if(n[i]=='0')
			n[i]='9';
		else{
			--n[i];
			break;
		}
	reg int ml=strlen(m);
	for(reg int i=ml-1;i>=0;--i)
		if(m[i]=='0')
			m[i]='9';
		else{
			--m[i];
			break;
		}
	Matrix C=GetExp(A,m,ml);
	Matrix R=C*GetExp(B*C,n,nl);
	Matrix ans=f*R;
	printf("%d\n",ans.unit[0][0]);
	return 0;
}