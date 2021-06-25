#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++)
static char buf[1<<21],*p1=buf,*p2=buf;
inline int read(void){
	reg char ch=getchar();
	reg int res=0;
	while(!isdigit(ch)) ch=getchar();
	while(isdigit(ch)) res=10*res+(ch^'0'),ch=getchar();
	return res;
}

const int MAXN=38;
const int MAXM=MAXN*(MAXN-1)/2;
const int mod=1e9+7;
const int inv2=5e8+4;

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

inline int lowbit(reg int x){
	return x&(-x);
}

inline int lg(reg int x){
	switch(x){
		case 1<<0:return 0;
		case 1<<1:return 1;
		case 1<<2:return 2;
		case 1<<3:return 3;
		case 1<<4:return 4;
		case 1<<5:return 5;
		case 1<<6:return 6;
		case 1<<7:return 7;
		case 1<<8:return 8;
		case 1<<9:return 9;
		case 1<<10:return 10;
		case 1<<11:return 11;
		case 1<<12:return 12;
		case 1<<13:return 13;
		case 1<<14:return 14;
		case 1<<15:return 15;
		case 1<<16:return 16;
		case 1<<17:return 17;
		case 1<<18:return 18;
		case 1<<19:return 19;
		default:return -1;
	}
}

namespace Poly{
	typedef vector<int> poly;
	inline void FWT(reg vector<int>& a){
		reg int n=a.size();
		for(reg int i=1;i<n;i<<=1)
			for(reg int j=0;j<n;j+=(i<<1))
				for(reg int k=0;k<i;++k)
					a[i+j+k]=add(a[i+j+k],a[j+k]);
		return;
	}
	inline void iFWT(reg vector<int>& a){
		reg int n=a.size();
		for(reg int i=1;i<n;i<<=1)
			for(reg int j=0;j<n;j+=(i<<1))
				for(reg int k=0;k<i;++k)
					a[i+j+k]=sub(a[i+j+k],a[j+k]);
		return;
	}
}

using namespace Poly;

int n,m,c;
int bas[MAXN+1];
ll G[MAXN];
int dp[1<<(MAXN>>1)][MAXN];
int f[1<<(MAXN>>1)];

int main(void){
	n=(read()+1)>>1,m=read(),c=read();
	for(reg int i=0;i<m;++i){
		static int u,v;
		u=read()-1,v=read()-1;
		G[u]|=1ll<<v,G[v]|=1ll<<u;
	}
	bas[0]=1;
	for(reg int i=1;i<=(n<<1);++i)
		bas[i]=1ll*bas[i-1]*c%mod;
	for(reg int S=0;S<(1<<n);++S)
		fill(dp[S],dp[S]+(n<<1),0);
	for(reg int S=1;S<(1<<n);++S){
		reg int low=lg(lowbit(S));
		if(__builtin_popcount(S)==1)
			dp[S][low<<1]=dp[S][low<<1|1]=1;
		reg int sum=0;
		for(reg int i=0;i<(n<<1);++i)
			if(dp[S][i]){
				for(reg int j=0;j<(n<<1);++j)
					if(!((S>>(j>>1))&1)&&((G[i]>>j)&1))
						dp[S|(1<<(j>>1))][j^1]=add(dp[S|(1<<(j>>1))][j^1],dp[S][i]);
				sum=add(sum,dp[S][i]);
			}
		f[S]=add(f[S],1ll*sum*inv2%mod*bas[__builtin_popcount(S)-1]%mod);
	}
	for(reg int S=0;S<(1<<n);++S)
		fill(dp[S],dp[S]+(n<<1),0);
	for(reg int S=1;S<(1<<n);++S){
		reg int low=lg(lowbit(S));
		if(__builtin_popcount(S)==1)
			dp[S][low<<1|1]=1;
		reg int sum=0;
		for(reg int i=0;i<(n<<1);++i)
			if(dp[S][i]){
				for(reg int j=(low+1)<<1;j<(n<<1);++j)
					if(!((S>>(j>>1))&1)&&((G[i]>>j)&1))
						dp[S|(1<<(j>>1))][j^1]=add(dp[S|(1<<(j>>1))][j^1],dp[S][i]);
				if((G[i]>>(low<<1))&1)
					sum=add(sum,dp[S][i]);
			}
		f[S]=add(f[S],1ll*sum*bas[__builtin_popcount(S)]%mod);
	}
	poly fr[MAXN],to[MAXN];
	for(reg int i=0;i<=n;++i)
		fr[i].resize(1<<n),to[i].resize(1<<n);
	for(reg int S=0;S<(1<<n);++S)
		fr[__builtin_popcount(S)][S]=f[S];
	for(reg int i=0;i<=n;++i)
		FWT(fr[i]);
	for(reg int i=0;i<=n;++i)
		for(reg int S=0;S<(1<<n);++S)
			fr[i][S]=1ll*i*fr[i][S]%mod;
	for(reg int i=0;i<=n;++i){
		if(!i)
			fill(to[i].begin(),to[i].end(),1);
		else{
			reg int inv=fpow(i,mod-2);
			for(reg int S=0;S<(1<<n);++S)
				to[i][S]=1ll*inv*to[i][S]%mod;
		}
		for(reg int j=1;j<=n-i;++j)
			for(reg int S=0;S<(1<<n);++S)
				to[i+j][S]=add(to[i+j][S],1ll*to[i][S]*fr[j][S]%mod);
	}
	iFWT(to[n]);
	printf("%d\n",to[n][(1<<n)-1]);
	return 0;
}