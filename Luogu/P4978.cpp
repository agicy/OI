#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++)
static char buf[1<<21],*p1=buf,*p2=buf;
inline int read(void){
	reg char ch=getchar();
	reg int res=0;
	while(!isdigit(ch)) ch=getchar();
	while(isdigit(ch)) res=10*res+(ch^'0'),ch=getchar();
	return res;
}

const int MAXN=2e3+5;
const int MAXM=2e3+5;
const int mod=998244353;

inline int add(reg int a,reg int b){
	a+=b;
	return a>=mod?a-mod:a;
}

inline int sub(reg int a,reg int b){
	a-=b;
	return a<0?a+mod:a;
}

inline int fpow(reg int x,reg int exp){
	reg int res=1;
	while(exp){
		if(exp&1)
			res=1ll*res*x%mod;
		x=1ll*x*x%mod;
		exp>>=1;
	}
	return res;
}

int n,m;
int a[MAXN],b[MAXM];
ll x[MAXN*MAXN],y[MAXN*MAXN];

int main(void){
	n=read(),m=read();
	for(reg int i=1;i<=n;++i)
		a[i]=read();
	for(reg int i=1;i<=m;++i)
		b[i]=read();
	reg int totx=0,toty=0;
	for(reg int i=1;i<=n;++i){
		reg ll sum=0;
		for(reg int j=i;j<=n;++j){
			sum+=a[j];
			x[++totx]=sum;
		}
	}
	for(reg int i=1;i<=m;++i){
		reg ll sum=0;
		for(reg int j=i;j<=m;++j){
			sum+=b[j];
			y[++toty]=sum;
		}
	}
	sort(x+1,x+totx+1),sort(y+1,y+toty+1);
	reg int ans1=0,ans2=1ll*totx*toty%mod;
	for(reg int i=1,j=0;i<=totx;++i){
		while(j<toty&&y[j+1]<x[i])
			++j;
		ans1=add(ans1,j);
	}
	reg int ans=1ll*ans1*fpow(ans2,mod-2)%mod;
	printf("%d\n",ans);
	return 0;
}