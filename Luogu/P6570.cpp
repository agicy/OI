#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
#define MOD 1000000007
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++)
static char buf[100000],*p1=buf,*p2=buf;
inline int read(void){
	reg char ch=getchar();
	reg int res=0;
	while(ch<'0'||'9'<ch)ch=getchar();
	while('0'<=ch&&ch<='9')res=10*res+ch-'0',ch=getchar();
	return res;
}

const int MAXN=300000+5;

bool vis[MAXN];
int phi[MAXN];
int cnt,prime[MAXN];

inline void Init(reg int n){
	phi[1]=1;
	for(reg int i=2;i<=n;++i){
		if(!vis[i]){
			phi[i]=i-1;
			prime[++cnt]=i;
		}
		for(reg int j=1;j<=cnt&&i*prime[j]<=n;++j){
			vis[i*prime[j]]=true;
			if(i%prime[j]==0){
				phi[i*prime[j]]=phi[i]*prime[j];
				break;
			}
			phi[i*prime[j]]=phi[i]*(prime[j]-1);
		}
	}
	return;
}

int n;
int T[MAXN],b[MAXN];
ll f[MAXN];

int main(void){
	n=read();
	int Max=0;
	for(reg int i=0;i<n;++i){
		static int x;
		x=read();
		++T[x];
		Max=max(Max,x);
	}
	reg int m=0;
	while((1<<m)<=Max)
		++m;
	Init(1<<m);
	f[0]=1,b[0]=0;
	for(reg int i=1;i<(1<<m);++i){
		b[i]=((b[i>>1]<<1)|1);
		if(T[i]){
			reg int mask=b[i]^i;
			for(reg int S=mask;;S=(S-1)&mask){
				f[S|i]=(f[S|i]+f[S]*T[i]%MOD)%MOD;
				if(!S)
					break;
			}
		}
	}
	reg int ans=0;
	for(reg int i=0;i<(1<<m);++i)
		ans=(ans+f[i]*phi[i+1]%MOD)%MOD;
	for(reg int i=1;i<=T[0];++i)
		ans=(ans<<1)%MOD;
	printf("%d\n",ans);
	return 0;
}