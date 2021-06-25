#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++)
static char buf[1<<21],*p1=buf,*p2=buf;
inline int read(void){
	reg char ch=getchar();
	reg int res=0;
	while(!isdigit(ch))ch=getchar();
	while(isdigit(ch))res=10*res+(ch^'0'),ch=getchar();
	return res;
}

const int MAXN=1.5e3+5;
const int mod=998244353;

int n,m,k;
int qh[MAXN],gj[MAXN];

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

namespace Subtask{
	int f[MAXN][MAXN<<1],g[MAXN][MAXN<<1];
	int fac[MAXN<<1],invfac[MAXN<<1];
	int sum[MAXN<<1];
	inline int binom(reg int n,reg int m){
		if(m<0||n<m)
			return 0;
		else
			return 1ll*fac[n]*invfac[m]%mod*invfac[n-m]%mod;
	}
	inline void Solve(void){
		fac[0]=1;
		for(reg int i=1;i<=(n<<1);++i)
			fac[i]=1ll*fac[i-1]*i%mod;
		invfac[n<<1]=fpow(fac[n<<1],mod-2);
		for(reg int i=(n<<1)-1;i>=0;--i)
			invfac[i]=1ll*invfac[i+1]*(i+1)%mod;
		fill(sum,sum+(n<<1)+1,0);
		for(reg int i=1;i<=n;++i)
			for(reg int j=k;j>=1;--j){
				f[i][j]=add(sum[j-1],1ll*binom(i-1,j-1)*gj[i]%mod);
				sum[j]=add(sum[j],f[i][j]);
			}
		fill(sum,sum+(n<<1)+1,0);
		g[0][0]=1,sum[0]=1;
		for(reg int i=1;i<=n;++i)
			for(reg int j=k;j>=1;--j){
				g[i][j]=1ll*sum[j-1]*qh[i]%mod;
				sum[j]=add(sum[j],g[i][j]);
			}
		reg int ans=0;
		for(reg int i=m-n;i<=m-1;++i){
			if(0<=i&&i<=n){
				if(i<k){
					reg int res1=0;
					for(reg int j=i;j<=n;++j)
						res1=add(res1,g[j][i]);
					reg int res2=0;
					for(reg int j=k-i;j<=n;++j)
						res2=add(res2,1ll*binom(n-j,m-k)*f[j][k-i]%mod);
					ans=add(ans,1ll*res1*res2%mod);
				}
				else{
					reg int res1=0;
					for(reg int j=k-1;j<=n;++j)
						res1=add(res1,1ll*binom(n-j,i-k+1)*g[j][k-1]%mod);
					reg int res2=0;
					for(reg int j=1;j<=n;++j)
						res2=add(res2,1ll*binom(n-j,m-i-1)*f[j][1]%mod);
					ans=add(ans,1ll*res1*res2%mod);
				}
			}
		}
		printf("%d\n",ans);
		return;
	}
}

int main(void){
	reg int t=read();
	while(t--){
		n=read(),m=read(),k=read();
		for(reg int i=1;i<=n;++i)
			qh[i]=read();
		for(reg int i=1;i<=n;++i)
			gj[i]=read();
		sort(qh+1,qh+n+1),reverse(qh+1,qh+n+1);
		sort(gj+1,gj+n+1),reverse(gj+1,gj+n+1);
		Subtask::Solve();
	}
	return 0;
}