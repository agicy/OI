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

inline int max(reg int a,reg int b){
	return a>b?a:b;
}

const int MAXN=1e5+5;
const int MAXA=1e5+5;
const int mod=998244353;

inline int add(reg int a,reg int b){
	a+=b;
	return a>=mod?a-mod:a;
}

bool vis[MAXA];
int tot,prime[MAXA];
int phi[MAXA];

inline void Init(reg int n){
	phi[1]=1;
	for(reg int i=2;i<=n;++i){
		if(!vis[i]){
			prime[++tot]=i;
			phi[i]=i-1;
		}
		for(reg int j=1;j<=tot&&i*prime[j]<=n;++j){
			vis[i*prime[j]]=true;
			if(!(i%prime[j])){
				phi[i*prime[j]]=phi[i]*prime[j];
				break;
			}
			phi[i*prime[j]]=phi[i]*(prime[j]-1);
		}
	}
	return;
}

int n;
int T[MAXN];
int f[MAXN];

int main(void){
	n=read();
	reg int Max=0;
	for(reg int i=1;i<=n;++i){
		reg int a=read();
		++T[a];
		Max=max(Max,a);
	}
	Init(Max);
	for(reg int i=1;i<=Max;++i)
		for(reg int j=i;j<=Max;j+=i)
			f[i]=add(f[i],T[j]);
	reg int ans=0;
	for(reg int i=1;i<=Max;++i)
		ans=add(ans,1ll*phi[i]*f[i]%mod*f[i]%mod);
	printf("%d\n",ans);
	return 0;
}