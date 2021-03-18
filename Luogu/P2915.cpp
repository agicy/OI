#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
#define getchar()(p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++)
static char buf[100000],*p1=buf,*p2=buf;
inline int read(void){
	reg char ch=getchar();
	reg int res=0;
	while(!isdigit(ch))ch=getchar();
	while(isdigit(ch))res=10*res+(ch^'0'),ch=getchar();
	return res;
}

const int MAXN=16;

int n,k;
int a[MAXN];
ll f[MAXN][1<<MAXN];

int main(void){
	n=read(),k=read();
	for(reg int i=0;i<n;++i)
		a[i]=read();
	for(reg int i=0;i<n;++i)
		f[i][1<<i]=1;
	for(reg int S=1;S<(1<<n);++S)
		for(reg int i=0;i<n;++i)
			for(reg int j=0;j<n;++j)
				if(abs(a[i]-a[j])>k&&((S>>i)&1)&&!((S>>j)&1))
					f[j][((1<<j)|S)]+=f[i][S];
	reg ll ans=0;
	for(reg int i=0;i<n;++i)
		ans+=f[i][(1<<n)-1];
	printf("%lld\n",ans);
	return 0;
}