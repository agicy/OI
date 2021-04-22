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

inline int sub(reg int a,reg int b){
	a-=b;
	return a<0?a+mod:a;
}

int n,k;
int fac[MAXN];
bool vis[MAXN];
int f[MAXN*2][MAXN];

int main(void){
	n=read(),k=read();
	fac[0]=1;
	for(reg int i=1;i<=n;++i)
		fac[i]=1ll*fac[i-1]*i%mod;
	reg int tot=0;
	vis[0]=true;
	for(reg int i=1;i<=(n-k)%k;++i)
		vis[tot+=(n-k)/k+1]=true,vis[tot+=(n-k)/k+1]=true;
	for(reg int i=1;i<=k-(n-k)%k;++i)
		vis[tot+=(n-k)/k]=true,vis[tot+=(n-k)/k]=true;
	f[0][0]=1;
	for(reg int i=1;i<=tot;++i)
		for(reg int j=0;j<=n;++j)
			f[i][j]=add(f[i-1][j],j?f[i-1-(!vis[i-1])][j-1]:0);
	reg int ans=0;
	for(reg int i=0;i<=n;++i)
		if(i&1)
			ans=sub(ans,1ll*f[tot][i]*fac[n-i]%mod);
		else
			ans=add(ans,1ll*f[tot][i]*fac[n-i]%mod);
	printf("%d\n",ans);
	return 0;
}