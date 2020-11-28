#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
typedef unsigned long long ull;
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++)
static char buf[100000],*p1=buf,*p2=buf;
inline ll read(void){
	reg char ch=getchar();
	reg ll res=0;
	while(ch<'0'||'9'<ch)ch=getchar();
	while('0'<=ch&&ch<='9')res=10*res+ch-'0',ch=getchar();
	return res;
}

const int MAXN=2e7+5;
const int S=2e7;

bool vis[MAXN];
ull cnt,prime[MAXN];
ull phi[MAXN];
ull Sphi[MAXN];
unordered_map<ll,ull> MSphi;

inline void Init(void){
	phi[1]=1;
	for(reg ull i=2;i<=S;++i){
		if(!vis[i]){
			phi[i]=i-1;
			prime[++cnt]=i;
		}
		for(reg ull j=1;j<=cnt&&i*prime[j]<=S;++j){
			vis[i*prime[j]]=true;
			if(i%prime[j]==0){
				phi[i*prime[j]]=phi[i]*prime[j];
				break;
			}
			phi[i*prime[j]]=phi[i]*(prime[j]-1);
		}
	}
	for(reg ull i=1;i<=S;++i)
		Sphi[i]=Sphi[i-1]+phi[i];
	return;
}

inline ull GetSphi(ll n){
	if(n<=S)
		return Sphi[n];
	if(MSphi[n])
		return MSphi[n];
	reg ull ans;
	if(n&1)
		ans=((n+1ull)>>1)*n;
	else
		ans=(n>>1)*(1ull+n);
	for(reg ull l=2,r;l<=n;l=r+1){
		r=n/(n/l);
		ans-=1ull*(r-l+1)*GetSphi(n/l);
	}
	return MSphi[n]=ans;
}

inline ull getAns(reg ull n){
	if(n<=1)
		return 0;
	else
		return getAns(n/2)+GetSphi(n);
}

int main(void){
	Init();
	reg ull T=read();
	while(T--){
		reg ull n=read();
		printf("%llu\n",getAns(n));
	}
	return 0;
}