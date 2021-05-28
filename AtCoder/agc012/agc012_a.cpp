#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++)
static char buf[1<<21],*p1=buf,*p2=buf;
inline int read(void){
	reg char ch=getchar();
	reg int res=0;
	while(!isdigit(ch))ch=getchar();
	while(isdigit(ch))res=10*res+(ch^'0'),ch=getchar();
	return res;
}

const int MAXN=1e5+5;

int n;
int a[MAXN*3];

int main(void){
	n=read();
	for(reg int i=1;i<=n*3;++i)
		a[i]=read();
	sort(a+1,a+3*n+1);
	reg ll ans=0;
	for(reg int i=3*n-1;i>=n+1;i-=2)
		ans+=a[i];
	printf("%lld\n",ans);
	return 0;
}