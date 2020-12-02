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
const int p=1e9+7;

inline int fpow(reg int x,reg int exp){
	reg int res=1;
	while(exp){
		if(exp&1)
			res=1ll*res*x%p;
		x=1ll*x*x%p;
		exp>>=1;
	}
	return res;
}

int fac[MAXN],invfac[MAXN];
bool vis[MAXN];
int tot,prime[MAXN];
int from[MAXN];

inline void Init(reg int n){
	fac[0]=1;
	for(reg int i=1;i<=n;++i)
		fac[i]=1ll*fac[i-1]*i%p;
	invfac[n]=fpow(fac[n],p-2);
	for(reg int i=n-1;i>=0;--i)
		invfac[i]=1ll*invfac[i+1]*(i+1)%p;
	for(reg int i=2;i<=n;++i){
		if(!vis[i]){
			prime[++tot]=i;
			from[i]=i;
		}
		for(reg int j=1;j<=tot&&i*prime[j]<=n;++j){
			vis[i*prime[j]]=true;
			from[i*prime[j]]=prime[j];
			if(i%prime[j]==0)
				break;
		}
	}
	return;
}

inline int binom(reg int n,reg int m){
	if(m<0||n<m)
		return 0;
	else
		return 1ll*fac[n]*invfac[m]%p*invfac[n-m]%p;
}

int f[MAXN];

int main(void){
	Init(2e6);
	reg int q=read();
	while(q--){
		reg int x=read(),y=read();
		reg int tot=0;
		while(x>1){
			reg int tmp=from[x];
			reg int cnt=0;
			while(x%tmp==0){
				++cnt;
				x/=tmp;
			}
			f[++tot]=cnt;
		}
		reg int ans=1;
		for(reg int i=1;i<=tot;++i)
			ans=1ll*ans*binom(f[i]+y-1,y-1)%p;
		ans=1ll*ans*fpow(2,y-1)%p;
		printf("%d\n",ans);
	}
	return 0;
}