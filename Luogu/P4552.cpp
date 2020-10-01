#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++)
static char buf[100000],*p1=buf,*p2=buf;
inline int read(void){
	reg char ch=getchar();
	reg int res=0;
	while(ch<'0'||'9'<ch)ch=getchar();
	while('0'<=ch&&ch<='9')res=10*res+ch-'0',ch=getchar();
	return res;
}

const int MAXN=1e5+5;

int n;
int a[MAXN],b[MAXN];

int main(void){
	n=read();
	for(reg int i=1;i<=n;++i)
		a[i]=read();
	for(reg int i=1;i<=n;++i)
		b[i]=a[i]-a[i-1];
	ll p=0,q=0;
	for(reg int i=2;i<=n;++i)
		if(b[i]>0)
			p+=b[i];
		else
			q+=-b[i];
	printf("%lld\n%lld\n",max(p,q),abs(p-q)+1);
	return 0;
}