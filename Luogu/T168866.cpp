
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

inline ll readll(void){
	reg char ch=getchar();
	reg ll res=0;
	while(!isdigit(ch))ch=getchar();
	while(isdigit(ch))res=10*res+(ch^'0'),ch=getchar();
	return res;
}

inline int max(reg int a,reg int b){
	return a>b?a:b;
}

inline int min(reg int a,reg int b){
	return a<b?a:b;
}

const int MAXSQRTN=1e6+5;

bool vis[MAXSQRTN];
int tot,prime[MAXSQRTN];
int mu[MAXSQRTN];

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

ll n;

inline ll dfs(reg int las,reg ll pod,reg int Min,reg int Max){
	reg ll ans=1ll*(Min-1)*Max;
	for(reg ll lim=n/pod;las<=tot&&1ll*prime[las]*prime[las]<=lim;++las){
		reg int c=2;
		reg ll ppod=pod*prime[las]*prime[las];
		while(ppod<=n){
			ans+=dfs(las+1,ppod,min(Min,c),max(Max,c));
			++c,ppod*=prime[las];
		}
	}
	return ans;
}

int main(void){
	Init(1e6);
	n=readll();
	reg ll sumg=n-1;
	for(reg int d=2;1ll*d*d<=n;++d)
		if(mu[d]){
			reg ll tmp=n/d;
			while(tmp/=d)
				sumg-=mu[d]*tmp;
		}
	reg ll delta=dfs(1,1,ceil(log2(n)),0);
	printf("%lld\n",sumg+delta);
	return 0;
}