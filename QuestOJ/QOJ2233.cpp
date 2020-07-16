#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
#define MOD 998244353
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++)
static char buf[100000],*p1=buf,*p2=buf;
inline int read(void){
	reg char ch=getchar();
	reg int res=0;
	while(ch<'0'||'9'<ch)ch=getchar();
	while('0'<=ch&&ch<='9')res=10*res+ch-'0',ch=getchar();
	return res;
}

const int MAXN=100000+5;
const int MAXS=500000+5;

inline int add(reg int a,reg int b){
	reg int sum=a+b;
	return sum>=MOD?sum-MOD:sum;
}

int n;
int f[MAXN];
int fac[MAXS],invfac[MAXS];

inline int pow(reg int x,reg int exp){
	reg int res=1;
	while(exp){
		if(exp&1)
			res=1ll*res*x%MOD;
		x=1ll*x*x%MOD;
		exp>>=1;
	}
	return res;
}

inline void Init(reg int n){
	fac[1]=invfac[1]=1;
	for(reg int i=2;i<=n;++i)
		fac[i]=1ll*fac[i-1]*i%MOD;
	invfac[n]=pow(fac[n],MOD-2);
	for(reg int i=n-1;i>=2;--i)
		invfac[i]=1ll*invfac[i+1]*(i+1ll)%MOD;
	return;
}

inline int C(reg int n,reg int m){
	return 1ll*fac[n]*invfac[m]%MOD*invfac[n-m]%MOD;
}

inline int Solve(reg int x,reg int k){
	reg int res=1;
	for(reg int i=2;i*i<=x;++i)
		if(x%i==0){
			reg int cnt=0;
			while(x%i==0)
				++cnt,x/=i;
			res=1ll*res*C(k+cnt-1,cnt)%MOD;
		}
	if(x>1)
		res=1ll*res*k%MOD;
	return res;
}

int main(void){
	Init(5e5);
	n=read();
	for(reg int i=1;i<=n;++i)
		f[i]=read();
	reg int m=read();
	while(m--){
		static int k,x;
		k=read(),x=read();
		reg int ans=0;
		for(reg int i=1;i*i<=x;++i)
			if(x%i==0){
				ans=add(ans,1ll*f[i]*Solve(x/i,k)%MOD);
				if(i*i!=x)
					ans=add(ans,1ll*f[x/i]*Solve(i,k)%MOD);
			}
		printf("%d\n",ans);
	}
	return 0;
}