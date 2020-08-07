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

const int MAXN=50000+5;

bool vis[MAXN];
int cnt,prime[MAXN];
int mu[MAXN];
int Smu[MAXN];
ll S[MAXN];

inline void Init(reg int n){
	mu[1]=1;
	for(reg int i=2;i<=n;++i){
		if(!vis[i]){
			mu[i]=-1;
			prime[++cnt]=i;
		}
		for(reg int j=1;j<=cnt&&i*prime[j]<=n;++j){
			vis[i*prime[j]]=true;
			if(i%prime[j]==0)
				break;
			mu[i*prime[j]]=-mu[i];
		}
	}
	for(reg int i=1;i<=n;++i)
		Smu[i]=Smu[i-1]+mu[i];
	for(reg int i=1;i<=n;++i)
		for(reg int l=1,r;l<=i;l=r+1){
			r=i/(i/l);
			S[i]+=1ll*(i/l)*(r-l+1);
		}
	return;
}

int n,m;

int main(void){
	Init(5e4);
	reg int T=read();
	while(T--){
		n=read(),m=read();
		if(n>m)
			swap(n,m);
		reg ll ans=0;
		for(reg int l=1,r;l<=n;l=r+1){
			r=min(n/(n/l),m/(m/l));
			ans+=1ll*(Smu[r]-Smu[l-1])*S[n/l]*S[m/l];
		}
		printf("%lld\n",ans);
	}
	return 0;
}