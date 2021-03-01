#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++)
static char buf[100000],*p1=buf,*p2=buf;
inline ll readll(void){
	reg char ch=getchar();
	reg ll res=0;
	while(!isdigit(ch))ch=getchar();
	while(isdigit(ch))res=10*res+(ch^'0'),ch=getchar();
	return res;
}

const int MAXS=5.32e5+5;
const int S=5.32e5;
const int pS=100;

bool vis[MAXS];
int tot,prime[MAXS];
int pi[MAXS];
ll f[MAXS][pS+5];

inline void Init(reg int n){
	for(reg int i=2;i<=n;++i){
		if(!vis[i]){
			prime[tot++]=i;
			pi[i]=pi[i-1]+1;
		}
		else
			pi[i]=pi[i-1];
		for(reg int j=0;j<tot&&i*prime[j]<=n;++j){
			vis[i*prime[j]]=true;
			if(!(i%prime[j]))
				break;
		}
	}
	for(reg int i=0;i<=n;++i){
		f[i][0]=i;
		for(reg int j=1;j<=pS;++j)
			f[i][j]=f[i][j-1]-f[i/prime[j-1]][j-1];
	}
	return;
}

inline ll getF(reg ll m,reg ll n){
	if(!n)
		return m;
	if(prime[n-1]>=m)
		return 1;
	if(m<=S&&n<=pS)
		return f[m][n];
	return getF(m,n-1)-getF(m/prime[n-1],n-1);
}

inline ll getCnt(reg ll m){
	if(m<=S)
		return pi[m];
	reg ll y=cbrt(m);
	reg ll n=pi[y];
	reg ll res=getF(m,n)+n-1;
	for(reg ll i=n;1ll*prime[i]*prime[i]<=m;++i)
		res=res-getCnt(m/prime[i])+getCnt(prime[i])-1;
	return res;
}

ll n;

int main(void){
	Init(S);
	n=readll();
	reg ll ans=0;
	reg ll tmp=0;
	for(reg int i=0;i<tot;++i){
		if(1ll*prime[i]*prime[i]>=n)
			break;
		reg ll x=n/prime[i];
		reg ll cnt=getCnt(x)-(tmp+1);
		tmp=getCnt(prime[i]);
		ans+=cnt;
	}
	if(n>=8)
		ans+=getCnt(cbrt(n));
	printf("%lld\n",ans);
	return 0;
}