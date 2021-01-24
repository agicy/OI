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

const int MAXN=3e5+5;

int n;
int a[MAXN];
int sum[MAXN];
int d[MAXN];
int f[MAXN];

int main(void){
	n=read();
	for(reg int i=1;i<=n;++i){
		a[i]=read();
		sum[i]=sum[i-1]+a[i];
	}
	memset(d,0x3f,sizeof(d));
	d[0]=0;
	for(reg int i=1;i<=n;++i)
		for(reg int j=i-1;j>=0;--j)
			if(sum[i]-sum[j]>=d[j]){
				d[i]=sum[i]-sum[j];
				f[i]=f[j]+i-j-1;
				break;
			}
	printf("%d\n",f[n]);
	return 0;
}