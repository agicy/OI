#include<bits/stdc++.h>
using namespace std;
#define reg register
#define INF 0X3F3F3F3F
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++)
static char buf[100000],*p1=buf,*p2=buf;
inline int read(void){
	reg char ch=getchar();
	reg int res=0;
	while(ch<'0'||'9'<ch)ch=getchar();
	while('0'<=ch&&ch<='9')res=10*res+ch-'0',ch=getchar();
	return res;
}

const int MAXN=10000000+5;
const int MOD=20101009;

int n,m;
bool vis[MAXN];
int tot,prime[MAXN];
int mu[MAXN];
int Smu[MAXN];

inline void Init(reg int S){
	mu[1]=1;
	for(reg int i=2;i<=S;++i){
		if(!vis[i]){
			mu[i]=-1;
			prime[++tot]=i;
		}
		for(reg int j=1;j<=tot&&i*prime[j]<=S;++j){
			vis[i*prime[j]]=true;
			if(i%prime[j]==0){
				break;
			}
			mu[i*prime[j]]=-mu[i];
		}
	}
	for(reg int i=1;i<=S;++i)
		Smu[i]=(Smu[i-1]+1ll*i*i%MOD*((mu[i]+MOD)%MOD)%MOD)%MOD;
	return;
}

inline int Sum(reg int x,reg int y){
	return ((1ll*x*(x+1)>>1ll)%MOD)*((1ll*y*(y+1)>>1ll)%MOD)%MOD;
}

inline int Solve(int x,int y){
	reg int res=0,S=min(x,y);
	for(reg int l=1,r;l<=S;l=r+1){
		r=min(x/(x/l),y/(y/l));
		res=(res+1ll*(Smu[r]-Smu[l-1]+MOD)%MOD*Sum(x/l,y/l)%MOD)%MOD;
	}
	return res;
}

int main(void){
	n=read(),m=read();
	Init(min(n,m));
	reg int res=0;
	for(reg int l=1,r;l<=min(n,m);l=r+1){
		r=min(n/(n/l),m/(m/l));
		res=(res+1ll*(r-l+1)*(l+r)/2%MOD*Solve(n/l,m/l)%MOD)%MOD;
	}
	printf("%d\n",res);
	return 0;
}