#pragma GCC optimize("Ofast")
#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;

bool st;

const int MAXN=200+5;
const int MAXM=200+5;

int n,m,mod=1;

struct modInt{
	int x;
	inline modInt(void){
		return;
	}
	inline modInt(reg int x):x(x){
		return;
	}
	inline modInt operator+(const modInt& a)const{
		reg int sum=x+a.x;
		return sum>=mod?sum-mod:sum;
	}
	inline modInt operator-(const modInt& a)const{
		reg int sum=x-a.x;
		return sum<0?sum+mod:sum;
	}
	inline modInt operator-(void)const{
		return modInt(0)-*this;
	}
	inline modInt operator*(const modInt& a)const{
		return 1ll*x*a.x%mod;
	}
	inline void operator+=(const modInt& a){
		x+=a.x;
		if(x>=mod) x-=mod;
		return;
	}
	inline void operator-=(const modInt& a){
		x-=a.x;
		if(x<0) x+=mod;
		return;
	}
	inline void operator*=(const modInt& a){
		x=1ll*x*a.x%mod;
		return;
	}
};

inline modInt fpow(modInt x,reg int exp){
	modInt res=1;
	while(exp){
		if(exp&1)
			res*=x;
		x*=x,exp>>=1;
	}
	return res;
}

modInt f[MAXN][MAXM],g[MAXN][MAXM];
modInt __h[MAXN][MAXM][MAXM];

inline modInt h(reg int n,reg int m,reg int k){
	if(n==1)
		return 1;
	else if(__h[n][m][k].x!=-1)
		return __h[n][m][k];
	else
		return __h[n][m][k]=f[n-1][m]*2+modInt(m-1)+h(n-1,m,k)+modInt(k-1)*modInt(m-k-1)+g[m-k+1][n-1]*modInt(k-1)+g[k+1][n-1]*modInt(m-k-1);
}

bool ed;

int main(void){
	scanf("%d%d%d",&n,&m,&mod);
	memset(__h,-1,sizeof(__h));
	reg int lim=max(n,m);
	for(reg int j=1;j<=lim;++j)
		f[1][j]=1;
	for(reg int i=2;i<=lim;++i)
		for(reg int j=1;j<=lim;++j)
			f[i][j]=f[i-1][j]*2+modInt(j-1);
	for(reg int j=1;j<=lim;++j)
		g[1][j]=1;
	for(reg int i=2;i<=lim;++i)
		for(reg int j=1;j<=lim;++j)
			g[i][j]=g[i-1][j]+modInt(j-1);
	/*
	for(reg int j=1;j<=lim;++j)
		for(reg int k=1;k<j;++k)
			h[1][j][k]=1;
	for(reg int i=2;i<=lim;++i)
		for(reg int j=1;j<=lim;++j)
			for(reg int k=1;k<j;++k)
				h[i][j][k]=f[i-1][j]*2+modInt(j-1)+h[i-1][j][k]+modInt(k-1)*modInt(j-k-1)+g[j-k+1][i-1]*modInt(k-1)+g[k+1][i-1]*modInt(j-k-1);
	*/
	modInt ans=fpow(2,n*m)-f[n][m]*2;
	for(reg int i=1;i<m;++i){
		ans-=f[m-i][n];
		for(reg int j=1;j<i;++j)
			ans-=f[m-i][n]*g[j+1][n];
	}
	for(reg int i=1;i<m;++i)
		ans-=h(n,m,i);
	printf("%d\n",ans.x);
	fprintf(stderr,"%.3lf s\n",1.0*clock()/CLOCKS_PER_SEC);
	fprintf(stderr,"%.3lf MiB\n",(&ed-&st)/1048576.0);
	return 0;
}