#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
typedef unsigned long long ull;
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

inline ll max(reg ll a,reg ll b){
	return a>b?a:b;
}

const int MAXT=1e4+5;
const int MAXL=1e8+5;

ll a[MAXT];
bool vis[MAXL];
int tot,prime[5761456];
char mu[MAXL];
int S2mu[MAXL];
int c[MAXL];
ull Sd[MAXL];
ull L;

inline void Init(reg int n){
	Sd[1]=S2mu[1]=mu[1]=1;
	for(reg int i=2;i<=n;++i){
		if(!vis[i]){
			prime[++tot]=i;
			mu[i]=-1,c[i]=1,Sd[i]=2;
		}
		for(reg int j=1;j<=tot&&i*prime[j]<=n;++j){
			vis[i*prime[j]]=true;
			if(!(i%prime[j])){
				c[i*prime[j]]=c[i]+1,Sd[i*prime[j]]=Sd[i]/(c[i]+1)*(c[i]+2);
				break;
			}
			mu[i*prime[j]]=-mu[i],c[i*prime[j]]=1,Sd[i*prime[j]]=2*Sd[i];
		}
	}
	for(reg int i=1;i<=n;++i){
		Sd[i]+=Sd[i-1];
		S2mu[i]=S2mu[i-1]+(mu[i]?1:0);
	}
	return;
}

inline ull getSd(reg ull x){
	if(x<=L)
		return Sd[x];
	reg ull res=0;
	for(reg ull l=1,r;l<=x;l=r+1){
		r=x/(x/l);
		res+=(r-l+1)*(x/l);
	}
	return res;
}

inline ull getSmu(reg ull x){
	if(x<=L)
		return S2mu[x];
	reg ull res=0;
	for(reg int i=1;1ull*i*i<=x;++i)
		if(mu[i])
			res+=mu[i]*(x/(1ull*i*i));
	return res;
}

inline ull solve(reg ull n){
	reg ull res=0;
	for(reg int i=1;1ll*i*i<=n;++i)
		if(mu[i])
			res+=getSd(n/i);
	reg ull las=S2mu[(int)sqrt(n)],val;
	for(reg ull l=sqrt(n)+1,r;l<=n;l=r+1){
		r=n/(n/l);
		val=getSmu(r);
		res+=(val-las)*getSd(n/l);
		las=val;
	}
	return res;
}

int main(void){
	reg int T=read();
	reg ll Max=0;
	for(reg int i=1;i<=T;++i){
		a[i]=readll();
		Max=max(Max,a[i]);
	}
	if(Max<=1e4)
		L=1e4;
	else
		L=1e8;
	Init(L);
	for(reg int i=1;i<=T;++i)
		printf("%llu\n",solve(a[i]));
	return 0;
}