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

const int MAXN=2e3+5;
const int mod=924844033;

inline int add(reg int a,reg int b){
    a+=b;
    return a>=mod?a-mod:a;
}

int n,k;
int fac[MAXN];
int tot,a[MAXN];
int f[MAXN*2][MAXN];

int main(void){
    n=read(),k=read();
    fac[0]=1;
    for(reg int i=1;i<=n;++i)
        fac[i]=1ll*fac[i-1]*i%mod;
	a[tot=0]=1;
	for(reg int i=1;i<=(n-k)%k;++i)
	  a[tot+=(n-k)/k+1]=1,a[tot+=(n-k)/k+1]=1;
	for(reg int i=1;i<=k-(n-k)%k;++i)
	  a[tot+=(n-k)/k]=1,a[tot+=(n-k)/k]=1;
	f[0][0]=1;
	for(reg int i=1;i<=tot;++i)
	    for(reg int j=0;j<=n;++j)
		    f[i][j]=(f[i-1][j]+(j?f[i-1-(!a[i-1])][j-1]:0))%mod;
    reg int ans=0;
	for(int j=0;j<=n;j++)
	    ans=add(ans,1ll*f[tot][j]*fac[n-j]%mod*(j&1?mod-1:1)%mod)%mod;
	printf("%d\n",ans);
    return 0;
}