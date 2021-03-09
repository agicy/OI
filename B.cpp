#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
#define getchar()(p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++)
static char buf[100000],*p1=buf,*p2=buf;
inline int read(void){
	reg bool f=false;
	reg char ch=getchar();
	reg int res=0;
	while(!isdigit(ch))f|=(ch=='-'),ch=getchar();
	while(isdigit(ch))res=10*res+(ch^'0'),ch=getchar();
	return f?-res:res;
}

inline void read(reg char *s){
	*s=getchar();
	while(!isdigit(*s))*s=getchar();
	while(isdigit(*s))*(++s)=getchar();
	*s='\0';
	return;
}

const int MAXN=7+2;
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

int n,k,l;
char s[MAXS];

namespace Subtask1{
	const int MAXS=5e5+5;
	char a[MAXS];
	int dp[MAXS][MAXN][MAXN];
	int binom[MAXN][MAXN];
	int f[MAXN][MAXN][MAXN];
	int g[MAXN];
	int tmp[MAXN];
	inline void Init(reg int n){
		binom[0][0]=1;
		for(reg int i=1;i<=n;++i){
			binom[i][0]=1;
			for(reg int j=1;j<=i;++j)
				binom[i][j]=add(binom[i-1][j-1],binom[i-1][j]);
		}
		return;
	}
	inline void Solve(void){
		Init(n);
		reg int len=l*k;
		for(reg int i=1;i<=k;++i)
			for(reg int j=1;j<=l;++j)
				a[(i-1)*l+j]=s[j]^'0';
		for(reg int i=0;i<=n;++i)
			dp[0][i][0]=1;
		for(reg int i=1;i<=len;++i)
			for(reg int l=0;l<=n;++l)
				for(reg int r=0;l+r<=n;++r)
					if(dp[i-1][l][r])
						for(reg int cnt1=0;cnt1<=l&&(a[i]||!cnt1);++cnt1)
							for(reg int cnt2=0;cnt2<=r;++cnt2){
								if(!a[i]&&cnt1)
									continue;
								if(!((cnt1+cnt2)&1)){
									if(!a[i])
										dp[i][l][r]=add(dp[i][l][r],1ll*dp[i-1][l][r]*binom[l][cnt1]%mod*binom[r][cnt2]%mod);
									else
										dp[i][cnt1][l+r-cnt1]=add(dp[i][cnt1][l+r-cnt1],1ll*dp[i-1][l][r]*binom[l][cnt1]%mod*binom[r][cnt2]%mod);
								}
							}
		for(reg int i=1;i<=n;++i)
			g[i]=dp[len][0][i];
		f[1][1][0]=1;
		for(reg int i=1;i<n;++i)
			for(reg int l=0;l<=i;++l)
				for(reg int r=0;r<=i;++r)
					if(f[i][l][r]){
						f[i+1][l+1][r]=add(f[i+1][l+1][r],f[i][l][r]);
						if(l)
							f[i+1][l-1][r+1]=add(f[i+1][l-1][r+1],1ll*f[i][l][r]*l%mod);
						if(r)
							f[i+1][l+1][r-1]=add(f[i+1][l+1][r-1],1ll*f[i][l][r]*r%mod);
					}
		reg int bas=0;
		for(reg int i=1;i<=len;++i)
			bas=add(add(bas,bas),a[i]);
		tmp[0]=tmp[1]=1;
		for(reg int i=3;i<=n;++i){
			tmp[i]=g[i];
			for(reg int l=0;l<=i;++l)
				for(reg int r=0;r<=i;++r){
					if(!f[i][l][r]||l==i)
						continue;
					reg int val=sub(bas,l),pod=1;
					for(reg int k=val;k>=val-r+1;--k)
						pod=1ll*pod*k%mod;
					tmp[i]=sub(tmp[i],1ll*pod*f[i][l][r]%mod*tmp[l]%mod);
				}
		}
		reg int fac=1;
		for(reg int i=1;i<=n;++i)
			fac=1ll*fac*i%mod;
		reg int ans=1ll*tmp[n]*fpow(fac,mod-2)%mod;
		printf("%d\n",ans);
		return;
	}
}

int main(void){
	n=read(),k=read(),read(s+1);
	l=strlen(s+1);
	//if(l*k<=1e4)
	Subtask1::Solve();
	return 0;
}