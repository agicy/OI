#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
#define INF 0X3F3F3F3F3F3F3F3Fll
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++)
static char buf[100000],*p1=buf,*p2=buf;
inline ll read(void){
	reg bool f=false;
	reg char ch=getchar();
	reg ll res=0;
	while(ch<'0'||'9'<ch)f|=(ch=='-'),ch=getchar();
	while('0'<=ch&&ch<='9')res=10*res+ch-'0',ch=getchar();
	return f?-res:res;
}

const int MAXN=500000+5;

ll n;
ll a[MAXN],f[MAXN];

int main(void){
	n=read();
	reg int m=(n+1)>>1;
	for(reg int i=1;i<=m;++i){
		a[i]=read();
		f[i]=f[i-1]+a[i];
	}
	reg int x=read();
	for(reg int i=m+1;i<=n;++i){
		a[i]=x;
		f[i]=f[i-1]+a[i];
	}
	if(x>=0)
		if(f[n]>0)
			printf("%lld\n",n);
		else
			puts("-1");
	else{
		reg bool flag=false;
		ll ans=INF;
		for(reg int i=1;i<=m;++i){
			ans=min(ans,m-i+1+(f[m]-f[i-1]-1)/(-x));
			if(i+ans-1>=n){
				flag=true;
				printf("%lld\n",min(ans,n));
				break;
			}
		}
		if(!flag)
			puts("-1");
	}
	return 0;
}