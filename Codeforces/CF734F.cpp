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

const int MAXN=2e5+5;
const int MAXLOG2A=31;

int n;
int a[MAXN],b[MAXN],c[MAXN];
int T[MAXLOG2A];

int main(void){
	n=read();
	reg ll sum=0;
	for(reg int i=1;i<=n;++i)
		b[i]=read(),sum+=b[i];
	for(reg int i=1;i<=n;++i)
		c[i]=read(),sum+=c[i];
	if(sum%(n<<1))
		puts("-1"),exit(0);
	sum/=n<<1;
	for(reg int i=1;i<=n;++i){
		if((b[i]+c[i]-sum)%n)
			puts("-1"),exit(0);
		a[i]=(b[i]+c[i]-sum)/n;
		if(a[i]<0)
			puts("-1"),exit(0);
		for(reg int j=0;j<MAXLOG2A;++j)
			T[j]+=(a[i]>>j)&1;
	}
	for(reg int i=1;i<=n;++i){
		reg ll tmpb=0,tmpc=0;
		for(reg int j=0;j<MAXLOG2A;++j)
			if((a[i]>>j)&1)
				tmpb+=(1ll<<j)*T[j],tmpc+=(1ll<<j)*n;
			else
				tmpc+=(1ll<<j)*T[j];
		if(tmpb!=b[i]||tmpc!=c[i])
			puts("-1"),exit(0);
	}
	for(reg int i=1;i<=n;++i)
		printf("%d%c",a[i],i==n?'\n':' ');
	return 0;
}