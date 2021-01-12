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

inline void cMax(reg int &a,reg int b){
	if(a<b) a=b;
	return;
}

inline int min(reg int a,reg int b){
	return a<b?a:b;
}

inline int max(reg int a,reg int b){
	return a>b?a:b;
}

const int MAXN=300+5;

int n;
int a[MAXN][MAXN];
int f[MAXN<<1][MAXN][MAXN];

int main(void){
	n=read();
	for(reg int i=1;i<=n;++i)
		for(reg int j=1;j<=n;++j)
			a[i][j]=read();
	memset(f,-0x3f,sizeof(f));
	f[1][1][1]=0;
	for(reg int k=1;k<=2*n-1;++k)
		for(reg int i=max(1,k-n+1);i<=min(k,n);++i)
			for(reg int j=max(1,k-n+1);j<=min(k,n);++j){
				reg int val=(i==j?a[i][k-i+1]:a[i][k-i+1]+a[j][k-j+1])+f[k][i][j];
				cMax(f[k+1][i][j],val),
				cMax(f[k+1][i+1][j],val),
				cMax(f[k+1][i][j+1],val),
				cMax(f[k+1][i+1][j+1],val);
			}
	printf("%d\n",f[2*n-1][n][n]+a[n][n]);
	return 0;
}