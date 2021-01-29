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

const int MAXN=1e5+5;
const int p=1e5+3;

inline int add(reg int a,reg int b){
	a+=b;
	return a>=p?a-p:a;
}

inline int fpow(reg int x,reg int exp){
	reg int res=1;
	while(exp){
		if(exp&1)
			res=1ll*res*x%p;
		x=1ll*x*x%p;
		exp>>=1;
	}
	return res;
}

int n,k;
int a[MAXN];
int f[MAXN];
int fac[MAXN],invfac[MAXN],inv[MAXN];
vector<int> factor[MAXN];

int main(void){
	n=read(),k=read();
	for(reg int i=1;i<=n;++i)
		a[i]=read();
	for(reg int i=1;i<=n;++i)
		for(reg int j=i;j<=n;j+=i)
			factor[j].push_back(i);
	reg int sum=0;
	for(reg int i=n;i>=1;--i)
		if(a[i]){
			++sum;
			for(vector<int>::iterator it=factor[i].begin();it!=factor[i].end();++it)
				a[*it]^=1;
		}
	fac[0]=1;
	for(reg int i=1;i<=n;++i)
		fac[i]=1ll*fac[i-1]*i%p;
	reg int ans;
	if(sum<=k)
		ans=sum;
	else{
		invfac[n]=fpow(fac[n],p-2);
		for(reg int i=n-1;i>=0;--i)
			invfac[i]=1ll*invfac[i+1]*(i+1)%p;
		inv[0]=1;
		for(reg int i=1;i<=n;++i)
			inv[i]=1ll*invfac[i]*fac[i-1]%p;
		f[n]=1;
		for(reg int i=n-1;i>=1;--i)
			f[i]=1ll*add(n,1ll*(n-i)*f[i+1]%p)*inv[i]%p;
		ans=k;
		for(reg int i=sum;i>k;--i)
			ans=add(ans,f[i]);
	}
	ans=1ll*ans*fac[n]%p;
	printf("%d\n",ans);
	return 0;
}