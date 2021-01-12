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

inline void read(reg char *s){
	*s=getchar();
	while(!isdigit(*s))*s=getchar();
	while(isdigit(*s))*(++s)=getchar();
	*s='\0';
	return;
}

const int MAXM=20+5;
const int MAXSIZE=20;

int n,m,K;
char s[MAXM];
int kmp[MAXM];

inline int add(reg int a,reg int b){
	a+=b;
	return a>=K?a-K:a;
}

struct Matrix{
	int n,m;
	int unit[MAXSIZE][MAXSIZE];
	inline Matrix(reg int n=0,reg int m=0,reg int x=0):n(n),m(m){
		for(reg int i=0;i<n;++i)
			for(reg int j=0;j<m;++j)
				unit[i][j]=(i==j)?x:0;
		return;
	}
	inline Matrix operator*(const Matrix& a)const{
		Matrix res(n,a.m,0);
		for(reg int i=0;i<n;++i)
			for(reg int k=0;k<m;++k){
				reg int r=unit[i][k];
				for(reg int j=0;j<a.m;++j)
					res.unit[i][j]=add(res.unit[i][j],r*a.unit[k][j]%K);
			}
		return res;
	}
	inline Matrix operator^(reg int exp)const{
		Matrix res(n,n,1),x=*this;
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
	n=read(),m=read(),K=read();
	read(s+1);
	for(reg int i=2,j=0;i<=m;++i){
		while(j&&s[j+1]!=s[i])
			j=kmp[j];
		if(s[j+1]==s[i])
			++j;
		kmp[i]=j;
	}
	Matrix G(m,m);
	for(reg int i=0;i<m;++i)
		for(reg char ch='0';ch<='9';++ch){
			reg int j=i;
			while(j&&s[j+1]!=ch)
				j=kmp[j];
			if(s[j+1]==ch)
				++j;
			++G.unit[i][j];
		}
	G=G^n;
	reg int ans=0;
	for(reg int i=0;i<m;++i)
		ans=add(ans,G.unit[0][i]);
	printf("%d\n",ans);
	return 0;
}