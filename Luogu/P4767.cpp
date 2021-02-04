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

const int MAXP=300+5;
const int MAXN=3e3+5;

int n,m;
int a[MAXN];
int sum[MAXN];
int f[MAXN][MAXP],p[MAXN][MAXP];

inline int calc(reg int l,reg int r){
	reg int mid=(l+r+1)>>1;
	return a[mid]*(mid-l+1)-(sum[mid]-sum[l-1])+(sum[r]-sum[mid])-a[mid]*(r-mid);
}

int main(void){
	n=read(),m=read();
	for(reg int i=1;i<=n;++i){
		a[i]=read();
		sum[i]=sum[i-1]+a[i];
	}
	memset(f,0x3f,sizeof(f));
	for(reg int i=1;i<=n;++i)
		f[i][1]=calc(1,i);
	for(reg int i=1;i<=m;++i)
		p[n][i]=1;
	for(reg int j=2;j<=m;++j){
		p[n+1][j]=n;
		for(reg int i=n;i>=1;--i)
			for(reg int k=p[i][j-1];k<=p[i+1][j];++k)
				if(f[k][j-1]+calc(k+1,i)<f[i][j]){
					f[i][j]=f[k][j-1]+calc(k+1,i);
					p[i][j]=k;
				}
	}
	printf("%d\n",f[n][m]);
	return 0;
}