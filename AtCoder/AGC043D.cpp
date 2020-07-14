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

const int MAXN=2000+5;

int n,m;
int f[MAXN*3][MAXN*4];

inline int add(reg int a,reg int b,reg int mod){
	reg int sum=a+b;
	return sum>=mod?sum-mod:sum;
}

int main(void){
	reg int n=read(),m=read();
	reg int Delta=n+1;
	f[0][Delta]=1;
	f[1][1+Delta]=1;
	f[2][-1+Delta]=1;
	f[2][2+Delta]=1;
	for(reg int i=3;i<=3*n;++i)
		for(reg int j=-n;j<=3*n;++j){
			f[i][j+Delta]=add(f[i][j+Delta],1ll*f[i-3][j+Delta]*(i-2)%m*(i-1)%m,m);
			f[i][j+Delta]=add(f[i][j+Delta],1ll*f[i-2][j+1+Delta]*(i-1)%m,m);
			f[i][j+Delta]=add(f[i][j+Delta],f[i-1][j-1+Delta],m);
		}
	reg int ans=0;
	for(reg int i=0;i<=n;++i)
		ans=add(ans,f[3*n][i*3+Delta],m);
	printf("%d\n",ans);
	return 0;
}