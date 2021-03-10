#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
#define getchar()(p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++)
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

const int MAXN=10+5;
const int MAXS=1e4+5;
const int mod=1e9+7;

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

struct Matrix{
	int n,m,unit[MAXN][MAXN];
	inline Matrix(reg int n,reg int m,reg int x=0):n(n),m(m){
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
					res.unit[i][j]=add(res.unit[i][j],1ll*r*a.unit[k][j]%mod);
			}
		return res;
	}
	inline Matrix operator^(reg int exp){
		Matrix res(n,n,1),x=*this;
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

int n,k,val=0,len;
char s[MAXS];
int G[MAXN+1];
int fac[MAXN+1],invfac[MAXN+1];
int col[MAXN+1],cnt[MAXN+1];

inline int getK(reg int t,reg int n){
	return (n?1ll<<(n-1):t^1)%mod;
}

inline int A(reg int n,reg int m){
	reg int res=1;
	for(reg int i=0;i<m;++i)
		res=1ll*res*sub(n,i)%mod;
	return res;
}

inline int binom(reg int n,reg int m){
	if(m<0||n<m)
		return 0;
	else
		return 1ll*fac[n]*invfac[m]%mod*invfac[n-m]%mod;
}

inline void dfs(reg int lim,reg int dep,reg int Max){
	if(dep==lim){
		if(col[lim-1]==lim-1)
			return;
		reg int sum=0;
		for(reg int a=0;a<Max;++a)
			sum+=cnt[a]&1;
		G[lim]=sub(G[lim],1ll*G[sum]*A(val-sum,Max-sum)%mod);
		return;
	}
	for(reg int i=0;i<=Max;++i){
		col[dep]=i;
		++cnt[i];
		dfs(lim,dep+1,Max+(i==Max));
		--cnt[i];
	}
	return;
}

int main(void){
	n=read(),k=read(),read(s);
	len=strlen(s);
	fac[0]=1;
	for(reg int i=1;i<=n;++i)
		fac[i]=1ll*fac[i-1]*i%mod;
	invfac[n]=fpow(fac[n],mod-2);
	for(reg int i=n-1;i>=0;--i)
		invfac[i]=1ll*invfac[i+1]*(i+1)%mod;
	for(reg int i=0;i<len;++i){
		s[i]^='0';
		val=add(add(val,val),s[i]);
	}
	reg int base2=fpow(2,len),del=val;
	for(reg int i=1;i<k;++i)
		val=add(1ll*val*base2%mod,del);
	for(reg int i=0;i<=n;++i)
		if(!((n-i)&1)){
			if(i<2)
				G[i]=1;
			else{
				Matrix bas(i+1,i+1,1);
				Matrix f[2]={Matrix(i+1,i+1,0),Matrix(i+1,i+1,0)};
				for(reg int j=0;j<=i;++j){
					f[0][j][j]=getK(0,i-j);
					for(reg int k=j;k<=i;++k)
						f[1][j][k]=1ll*getK(j&1,i-k)*binom(k,j)%mod;
				}
				for(reg int j=0;j<len;++j)
					bas=f[s[j]]*bas;
				G[i]=(bas^k)[0][i];
				dfs(i,0,0);
			}
		}
	printf("%lld\n",1ll*G[n]*invfac[n]%mod);
	return 0;
}