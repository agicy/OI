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

inline int max(reg int a,reg int b){
	return a>b?a:b;
}

const int mod=998244353;

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

const int MAXN=6e5+5;

int las=0;
int fac[MAXN<<1],invfac[MAXN<<1];

inline void Init(reg int n){
	if(n<=las)
		return;
	for(reg int i=las+1;i<=n;++i)
		fac[i]=1ll*fac[i-1]*i%mod;
	invfac[n]=fpow(fac[n],mod-2);
	for(reg int i=n-1;i>las;--i)
		invfac[i]=1ll*invfac[i+1]*(i+1)%mod;
	las=n;
	return;
}

inline int binom(reg int n,reg int m){
	if(m<0||n<m)
		return 0;
	else
		return 1ll*fac[n]*invfac[m]%mod*invfac[n-m]%mod;
}

int n;
int q[MAXN];
bool vis[MAXN];

int main(void){
	freopen("inverse.in","r",stdin);
	freopen("inverse.out","w",stdout);
	las=0,fac[0]=invfac[0]=1;
	reg int t=read();
	while(t--){
		n=read();
		Init(n<<1);
		fill(vis+1,vis+n+1,false);
		for(reg int i=1;i<=n;++i)
			q[i]=read();
		reg int Max=0,Min=1;
		reg int ans=0;
		for(reg int i=1;i<=n;++i){
			reg int lim=max(Max,q[i])+1;
			vis[q[i]]=true;
			if(lim<=n)
				ans=add(ans,sub(binom((n<<1|1)-lim-i,n-i+1),binom((n<<1|1)-lim-i,n-i+2)));
			if(Max<q[i])
				Max=q[i];
			else if(q[i]!=Min)
				break;
			while(vis[Min])
				++Min;
		}
		printf("%d\n",ans);
	}
	fclose(stdin);
	fclose(stdout);
	return 0;
}