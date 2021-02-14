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

inline int gcd(reg int a,reg int b){
	return b?gcd(b,a%b):a;
}

const int MAXK=2e3+5;
const int MAXCNT=45+1;
const int MAXS=1e6+5;

bool vis[MAXS];
int tot,prime[MAXS];
int mu[MAXS],Smu[MAXS];

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
	for(reg int i=1;i<=n;++i)
		Smu[i]=Smu[i-1]+mu[i];
	return;
}

int n,m,k;
int sum[MAXK];
int cnt,T[MAXCNT];
int S=1e6;
map<int,ll> M[MAXCNT];

inline ll getVal(int n,reg int k){
	if(!n)
		return 0;
	if(k==1&&n<=S)
		return Smu[n];
	if(M[k].count(n))
		return M[k][n];
	reg ll ans;
	if(k>1){
		ans=0;
		for(reg int j=1;j<=k;++j)
			if((!(T[k]%T[j]))&&mu[T[j]])
				ans+=getVal(n/T[j],j);
	}
	else{
		ans=1;
		for(reg int l=2,r;l<=n;l=r+1){
			r=n/(n/l);
			ans-=(r-l+1)*getVal(n/l,1);
		}
	}
	return M[k][n]=ans;
}

int main(void){
	n=read(),m=read(),k=read();
	for(reg int i=1;i<=k;++i)
		sum[i]=sum[i-1]+(gcd(i,k)==1);
	Init(S);
	for(reg int i=1;i<=k;++i)
		if((!(k%i))&&(mu[i]||i==k))
			T[++cnt]=i;
	reg ll ans=0;
	for(reg int l=1,r;l<=n&&l<=m;l=r+1){
		r=min(n/(n/l),m/(m/l));
		ans+=1ll*(n/l)*(1ll*m/(1ll*l*k)*sum[k]+sum[m/l%k])*(getVal(r,cnt)-getVal(l-1,cnt));
	}
	printf("%lld\n",ans);
	return 0;
}