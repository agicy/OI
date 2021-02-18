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

const int MAXN=10+5;
const int mod=2004;

inline int add(reg int a,reg int b){
	a+=b;
	return a>=mod?a-mod:a;
}

inline int sub(reg int a,reg int b){
	a-=b;
	return a<0?a+mod:a;
}

int n,a,b;
ll m[MAXN];
int fac=1;

inline int binom(reg int n,reg int m){
	reg ll res=1;
	reg ll Mod=1ll*mod*fac;
	for(reg int i=n-m+1;i<=n;++i)
		res=1ll*res*i%Mod;
	res/=fac;
	return res%mod;
}

inline int dfs(reg int dep,reg int k,reg int t,reg int lim){
	if(t>lim)
		return 0;
	if(dep==n+1)
		return 1ll*k*binom(n+lim-t,n)%mod;
	return add(dfs(dep+1,k,t,lim),dfs(dep+1,sub(0,k),t+m[dep]+1,lim));
}

int main(void){
	n=read(),a=read(),b=read();
	for(reg int i=1;i<=n;++i)
		m[i]=read(),fac*=i;
	printf("%d\n",sub(dfs(1,1,0,b),dfs(1,1,0,a-1)));
	return 0;
}