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

const int MAXN=5e3+5;

int n;
int c[MAXN];
int sum[MAXN];
int f[MAXN];

int main(void){
	n=read();
	for(reg int i=1;i<=n;++i){
		c[i]=read();
		f[i]=c[i];
		sum[i]=sum[i-1]+c[i];
	}
	for(reg int len=2;len<=n;++len)
		for(reg int l=1;l+len-1<=n;++l){
			reg int r=l+len-1;
			f[l]=sum[r]-sum[l-1]-min(f[l],f[l+1]);
		}
	printf("%d\n",f[1]);
	return 0;
}