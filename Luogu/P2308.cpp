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

const int MAXN=20+5;

int n;
int a[MAXN];
int sum[MAXN];
int f[MAXN][MAXN],from[MAXN][MAXN];
int lef[MAXN],rig[MAXN];
int cnt,ans[MAXN];

inline void print(reg int l,reg int r){
	if(l==r)
		return;
	print(l,from[l][r]);
	print(from[l][r]+1,r);
	++lef[l],++rig[r];
	ans[++cnt]=sum[r]-sum[l-1];
	return;
}

int main(void){
	n=read();
	for(reg int i=1;i<=n;++i){
		a[i]=read();
		sum[i]=sum[i-1]+a[i];
	}
	memset(f,0x3f,sizeof(f));
	for(reg int i=1;i<=n;++i)
		f[i][i]=0;
	for(reg int len=2;len<=n;++len)
		for(reg int l=1;l+len-1<=n;++l){
			reg int r=l+len-1;
			for(reg int k=l;k<r;++k)
				if(f[l][k]+f[k+1][r]+sum[r]-sum[l-1]<=f[l][r]){
					f[l][r]=f[l][k]+f[k+1][r]+sum[r]-sum[l-1];
					from[l][r]=k;
				}
		}
	print(1,n);
	for(reg int i=1;i<=n;++i){
		while(lef[i]--)
			putchar('(');
		printf("%d",a[i]);
		while(rig[i]--)
			putchar(')');
		if(i!=n)
			putchar('+');
		else
			putchar('\n');
	}
	printf("%d\n",f[1][n]);
	for(reg int i=1;i<=cnt;++i)
		printf("%d%c",ans[i],i==cnt?'\n':' ');
	return 0;
}