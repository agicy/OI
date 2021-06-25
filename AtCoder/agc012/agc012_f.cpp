#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++)
static char buf[1<<21],*p1=buf,*p2=buf;
inline int read(void){
	reg char ch=getchar();
	reg int res=0;
	while(!isdigit(ch)) ch=getchar();
	while(isdigit(ch)) res=10*res+(ch^'0'),ch=getchar();
	return res;
}

const int MAXN=50+5;
const int mod=1e9+7;

inline int add(reg int a,reg int b){
	a+=b;
	return a>=mod?a-mod:a;
}

inline int sub(reg int a,reg int b){
	a-=b;
	return a<0?a+mod:a;
}

int n;
int a[MAXN<<1];
int f[2][MAXN<<1][MAXN<<1];

int main(void){
	n=read();
	for(reg int i=1;i<(n<<1);++i)
		a[i]=read();
	sort(a+1,a+(n<<1));
	f[n&1][0][0]=1;
	for(reg int i=n;i>=2;--i){
		for(reg int l=0;l<(n<<1);++l)
			for(reg int r=0;r<(n<<1);++r)
				f[(i-1)&1][l][r]=0;
		reg int dl=(a[i-1]!=a[i]),dr=(a[(n<<1)-(i-1)]!=a[(n<<1)-i]);
		for(reg int l=0;l<(n<<1);++l)
			for(reg int r=0;r<(n<<1);++r)
				if(f[i&1][l][r]){
					f[(i-1)&1][l+dl][r+dr]=add(f[(i-1)&1][l+dl][r+dr],f[i&1][l][r]);
					for(reg int k=0;k<l+dl;++k)
						f[(i-1)&1][k][r+dr+1]=add(f[(i-1)&1][k][r+dr+1],f[i&1][l][r]);
					for(reg int k=0;k<r+dr;++k)
						f[(i-1)&1][l+dl+1][k]=add(f[(i-1)&1][l+dl+1][k],f[i&1][l][r]);
				}
	}
	reg int ans=0;
	for(reg int i=0;i<(n<<1);++i)
		for(reg int j=0;j<(n<<1);++j)
			ans=add(ans,f[1][i][j]);
	printf("%d\n",ans);
	return 0;
}