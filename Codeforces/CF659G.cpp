#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
#define getchar()(p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++)
static char buf[1<<21],*p1=buf,*p2=buf;
inline int read(void){
	reg char ch=getchar();
	reg int res=0;
	while(!isdigit(ch))ch=getchar();
	while(isdigit(ch))res=10*res+(ch^'0'),ch=getchar();
	return res;
}

const int MAXN=1e6+5;
const int mod=1e9+7;

inline int add(reg int a,reg int b){
	a+=b;
	return a>=mod?a-mod:a;
}

int n,m,k,ans;
int h[MAXN],f[MAXN][2];

int main(void){
	n=read();
	for(reg int i=1;i<=n;++i)
		h[i]=read()-1;
	f[1][0]=h[1];
	f[1][1]=min(h[1],h[2]);
	for(reg int i=2;i<=n;++i){
		f[i][1]=add(1ll*min(h[i-1],min(h[i],h[i+1]))*f[i-1][1]%mod,min(h[i],h[i+1]));
		f[i][0]=add(1ll*min(h[i-1],h[i])*f[i-1][1]%mod,h[i]);
	}
	for(reg int i=1;i<=n;++i)
		ans=add(ans,f[i][0]);
	printf("%d\n",ans);
	return 0;
}