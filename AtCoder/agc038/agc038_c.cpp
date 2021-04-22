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

inline int max(reg int a,reg int b){
	return a>b?a:b;
}

const int MAXN=5e4+5;
const int MAXA=5e4+5;

bool vis[MAXA];
int tot,prime[MAXA];
int mu[MAXA];

inline void Init(reg int n){
	mu[1]=1;
	for(reg int i=2;i<=n;++i){
		if(!vis[i]){
			prime[++tot]=i;
			mu[i]=-1;
		}
		for(reg int j=1;j<=tot&&i*prime[j]<=n;++j){
			vis[i*prime[j]]=true;
			if(!(i%prime[j]))
				break;
			mu[i*prime[j]]=-mu[i];
		}
	}
	return;
}

int n;
int T[MAXN];
ll f[MAXN];

int main(void){
	n=read();
	reg int Max=0;
	for(reg int i=1;i<=n;++i){
		static int a;
		a=read();
		++T[a];
		Max=max(Max,a);
	}
	Init(Max);
	for(reg int i=1;i<=Max;++i)
		for(reg int j=i;j<=Max;j+=i)
			f[j]+=1ll*mu[i]*i;
	reg ll ans=0;
	for(reg int i=1;i<=Max;++i){
		reg ll sum=0;
		for(reg int j=1;i*j<=Max;++j)
			sum+=1ll*j*T[i*j];
		ans+=1ll*i*f[i]*sum*sum;
	}
	printf("%lld\n",ans);
	return 0;
}