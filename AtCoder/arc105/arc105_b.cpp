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

int n,ans;
int a[MAXN];

inline int gcd(reg int a,reg int b){
	return b?gcd(b,a%b):a;
}

int main(void){
	n=read(),ans=read();
	for(reg int i=2;i<=n;++i)
		ans=gcd(ans,read());
	printf("%d\n",ans);
	return 0;
}