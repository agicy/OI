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

inline int max(reg int a,reg int b){
	return a>b?a:b;
}

inline int min(reg int a,reg int b){
	return a<b?a:b;
}

const int MAXN=50+5;
const int MAXM=MAXN*(MAXN-1)/2;

int n,m;
int sum[MAXN][MAXM];
int f[MAXN][MAXM],Max[MAXN][MAXM];

int main(void){
	n=read(),m=read();
	for(reg int j=1;j<=n;++j)
		for(reg int i=n;i>=j;--i)
			sum[i][j]=sum[i][j-1]+read();
	reg int ans=0;
	for(reg int i=1;i<=n;++i){
		for(reg int j=i;j>=1;--j)
			for(reg int k=min(j+i*(i-1)/2,m);k>=j*(j+1)/2;--k){
				f[j][k]=Max[j-1][k-j]+sum[i][j];
				Max[j][k]=max(Max[j+1][k],f[j][k]);
				ans=max(ans,f[j][k]);
			}
		for(reg int k=i*(i-1)/2+1;k<=i*(i+1)/2;++k)
			for(reg int j=k-i*(i-1)/2-1;j>=0;--j)
				Max[j][k]=max(Max[j+1][k],f[j][k]);
		for(reg int k=1;k<=i*(i+1)/2;++k)
			Max[0][k]=max(Max[1][k],Max[0][k]);
	}
	printf("%d\n",ans);
	return 0;
}