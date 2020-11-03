#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++)
static char buf[100000],*p1=buf,*p2=buf;
inline int read(void){
	reg bool f=false;
	reg char ch=getchar();
	reg int res=0;
	while(!isdigit(ch))f|=(ch=='-'),ch=getchar();
	while(isdigit(ch))res=10*res+(ch^'0'),ch=getchar();
	return f?-res:res;
}

const int MAXN=5e3+5;
const int delta=1e6;

int n,q;
int a[MAXN],T[delta*2];
ll sum[MAXN][MAXN];

int main(void){
	n=read(),q=read();
	for(reg int i=1;i<=n;++i)
		a[i]=read()+delta;
	for(reg int i=1;i<n;++i){
		++T[a[i+1]];
		for(reg int j=i+2;j<=n;++j){
			if(a[i]+a[j]<=delta*3&&a[i]+a[j]>=delta)
				sum[i][j]=T[delta*3-a[i]-a[j]];
			++T[a[j]];
		}
		for(reg int j=i+1;j<=n;++j)
			--T[a[j]];
	}
	for(reg int i=1;i<=n;++i)
		for(reg int j=1;j<=n;++j)
			sum[i][j]+=sum[i-1][j]+sum[i][j-1]-sum[i-1][j-1];
	while(q--){
		static int l,r;
		l=read(),r=read();
		ll ans=sum[r][r]-sum[l-1][r]-sum[r][l-1]+sum[l-1][l-1];
		printf("%lld\n",ans);
	}
	return 0;
}