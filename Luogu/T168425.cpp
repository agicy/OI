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

const int MAXS=1e7+5;

bool vis[MAXS];
int tot,prime[MAXS];
int from[MAXS],Max[MAXS];
ull Sg[MAXS],g[MAXS];

inline void Init(reg int n){
	g[1]=Sg[1]=1;
	from[1]=1;
	for(reg int i=2;i<=n;++i){
		if(!vis[i]){
			prime[++tot]=i;
			g[i]=1ull*i*i-1;
		}
		for(reg int j=1;j<=tot&&i*prime[j]<=n;++j){
			vis[i*prime[j]]=true;
			from[i*prime[j]]=prime[j];
			if(!(i%prime[j])){
				g[i*prime[j]]=g[i]*prime[j]*prime[j];
				break;
			}
			g[i*prime[j]]=g[i]*g[prime[j]];
		}
	}
	for(reg int i=2;i<=n;++i)
		Sg[i]=Sg[i-1]+g[i];
	return;
}

int main(void){
	Init(1e7);
	reg int T=read();
	while(T--){
		reg ll n=readll();
		reg ull ans=0;
		for(reg int l=1,r;1ll*l*l<=n;l=r+1){
			r=sqrt(n/(n/(1ull*l*l)));
			ans+=1ull*(n/(1ull*l*l))*(Sg[r]-Sg[l-1]);
		}
		printf("%llu\n",ans);
	}
	return 0;
}