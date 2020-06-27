#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++)
static char buf[100000],*p1=buf,*p2=buf;
inline int read(void){
	reg char ch=getchar();
	reg int res=0;
	while(ch<'0'||'9'<ch)ch=getchar();
	while('0'<=ch&&ch<='9')res=10*res+ch-'0',ch=getchar();
	return res;
}

inline ll pow(reg ll x,reg ll exp,reg ll mod){
	reg ll res=1;
	while(exp){
		if(exp&1)
			res=res*x%mod;
		x=x*x%mod;
		exp>>=1;
	}
	return res;
}

const int MAXN=1000000+5;

int vis[MAXN<<1];
int tot,prime[MAXN<<1];

inline void Init(reg int n){
	for(reg int i=2;i<=n;++i){
		if(!vis[i]){
			vis[i]=i;
			prime[++tot]=i;
		}
		for(reg int j=1;j<=tot&&i*prime[j]<=n;++j){
			vis[i*prime[j]]=prime[j];
			if(i%prime[j]==0)
				break;
		}
	}
	return;
}

int T[MAXN];
int n,p;
int cnt[MAXN<<1];

int main(void){
	n=read(),p=read();
	Init(2*n);
	for(reg int i=1;i<=n;++i)
		cnt[i]=-1;
	for(reg int i=n+2;i<=2*n;++i)
		cnt[i]=1;
	for(reg int i=2*n;i>=2;--i)
		if(vis[i]<i){
			cnt[vis[i]]+=cnt[i];
			cnt[i/vis[i]]+=cnt[i];
		}
	reg ll ans=1;
	for(reg int i=2;i<=2*n;++i)
		if(vis[i]==i)
			ans=ans*pow(i,cnt[i],p)%p;
	printf("%lld\n",ans);
	return 0;
}