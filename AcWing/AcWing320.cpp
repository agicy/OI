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

const int MAXN=100+5;

int n,e[2*MAXN],s[2*MAXN][2*MAXN];

int main(void){
	n=read();
	for(reg int i=1;i<=n;++i)
		e[i+n]=e[i]=read();
	int ans=0;
	for(reg int i=2;i<(n<<1);++i)
		for(reg int j=i-1;i-j<n&&j;--j)
			for(reg int k=j;k<i;++k){
				s[j][i]=max(s[j][i],s[j][k]+s[k+1][i]+e[j]*e[k+1]*e[i+1]);
				ans=max(ans,s[j][i]);
			}
	printf("%d\n",ans);
	return 0;
}