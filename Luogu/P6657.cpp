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

const int MAXN=2e6+5;
const int MAXM=100;
const int mod=998244353;
const int N=2e6;

inline int add(reg int a,reg int b){
	a+=b;
	return a>=mod?a-mod:a;
}

inline int sub(reg int a,reg int b){
	a-=b;
	return a<0?a+mod:a;
}

inline int fpow(reg int x,reg int exp){
	reg int res=1;
	while(exp){
		if(exp&1)
			res=1ll*res*x%mod;
		x=1ll*x*x%mod;
		exp>>=1;
	}
	return res;
}

int n,m;
int a[MAXM],b[MAXM];
int fac[MAXN],invfac[MAXN];
int G[MAXM][MAXM];

inline int binom(reg int n,reg int m){
	if(m<0||n<m)
		return 0;
	else
		return 1ll*fac[n]*invfac[m]%mod*invfac[n-m]%mod;
}

inline int det(reg int m){
	reg int res=1,sgn=0;
	for(reg int i=0;i<m;++i){
		reg int Max=-1;
		for(reg int j=i;j<m;++j)
			if(G[j][i]){
				Max=j;
				break;
			}
		if(Max==-1)
			return 0;
		if(i!=Max){
			sgn^=1;
			for(reg int k=0;k<m;++k)
				swap(G[i][k],G[Max][k]);
		}
		for(reg int j=i+1;j<m;++j){
			reg int d=1ll*G[j][i]*fpow(G[i][i],mod-2)%mod;
			for(reg int k=i;k<m;++k)
				G[j][k]=sub(G[j][k],1ll*d*G[i][k]%mod);
		}
		res=1ll*res*G[i][i]%mod;
	}
	return sgn?sub(0,res):res;
}

int main(void){
	reg int T=read();
	fac[0]=1;
	for(reg int i=1;i<=N;++i)
		fac[i]=1ll*fac[i-1]*i%mod;
	invfac[N]=fpow(fac[N],mod-2);
	for(reg int i=N-1;i>=0;--i)
		invfac[i]=1ll*invfac[i+1]*(i+1)%mod;
	while(T--){
		n=read(),m=read();
		for(reg int i=0;i<m;++i)
			a[i]=read(),b[i]=read();
		for(reg int i=0;i<m;++i)
			for(reg int j=0;j<m;++j)
				G[i][j]=binom(n-1+b[j]-a[i],n-1);
		printf("%d\n",det(m));
	}
	return 0;
}