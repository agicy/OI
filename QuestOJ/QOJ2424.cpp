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

const int MAXN=5e5+5;

int n;
int c[MAXN];
bool f[MAXN];

int main(void){
	n=read();
	for(reg int i=1;i<=n;++i)
		c[i]=read();
	f[1]=true;
	for(reg int i=1;i<=n;++i)
		for(reg int j=i<<1;j<=n;j+=i)
			f[j]=f[j]||c[j]!=c[i];
	reg int ans=0;
	for(reg int i=1;i<=n;++i)
		ans+=f[i];
	printf("%d\n",ans);
	return 0;
}