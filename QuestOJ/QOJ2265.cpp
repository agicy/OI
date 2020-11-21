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
	while(isdigit(ch))res=10ll*res+(ch^'0'),ch=getchar();
	return res;
}

inline int add(reg int a,reg int b,const int& mod){
	reg int sum=a+b;
	return sum>=mod?sum-mod:sum;
}

inline int mul(reg int a,reg int b,const int& mod){
	return 1ll*a*b%mod;
}

inline int fpow(reg int val,reg int exp,const int& mod){
	reg int res=1;
	while(exp){
		if(exp&1)
			res=mul(res,val,mod);
		val=mul(val,val,mod);
		exp>>=1;
	}
	return res;
}

const int MAXN=3e5+5;
const int p=998244353;
const int phip1=998244352;
const int phip2=402653184;

int n;
ll k;
bool vis[MAXN];
int tot,prime[MAXN];
int mu[MAXN];
int fac[MAXN],invfac[MAXN];
int summu[MAXN];

inline void Init(int n){
	mu[1]=fac[0]=1;
	for(reg int i=1;i<=n;++i)
		fac[i]=mul(fac[i-1],i,p);
	invfac[n]=fpow(fac[n],p-2,p);
	for(reg int i=n-1;i>=0;--i)
		invfac[i]=mul(invfac[i+1],i+1,p);
	for(reg int i=2;i<=n;++i){
		if(!vis[i]){
			mu[i]=-1;
			prime[++tot]=i;
		}
		for(reg int j=1;j<=tot&&i*prime[j]<=n;++j){
			vis[i*prime[j]]=true;
			if(i%prime[j]==0)
				break;
			mu[i*prime[j]]=-mu[i];
		}
	}
	for(reg int i=1;i<=n;++i)
		summu[i]=summu[i-1]+mu[i];
	return;
}

inline int min(reg int a,reg int b){
	return a<b?a:b;
}

int id[MAXN];

int main(void){
	reg int t=read();
	Init(3e5);
	while(t--){
		n=read(),k=readll();
		reg int kmp2=k%phip2;
		reg int ans1=fpow(fac[n],mul(k%phip1,fpow(n,(k-1)%phip2,phip1),phip1),p);
		reg int ans2=1;
		for(reg int l=1,r;l<=n;l=r+1){
			reg int val=n/l;
			r=min(n/val,n);
			id[val]=fpow(val,kmp2,phip1);
		}
		for(reg int l=1,r;l<=n;l=r+1){
			reg int val=n/l;
			r=min(n/val,n);
			reg int exp=0;
			for(reg int l=1,r;l<=val;l=r+1){
				reg int xval=val/l;
				r=min(val/xval,val);
				exp=add(exp,mul(add(summu[r],phip1-summu[l-1],phip1),id[xval],phip1),phip1);
			}
			reg int res=fpow(mul(fac[r],invfac[l-1],p),exp,p);
			ans2=mul(ans2,res,p);
		}
		printf("%d\n",mul(ans1,fpow(ans2,p-2,p),p));
	}
	return 0;
}