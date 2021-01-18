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
	while(isdigit(ch))res=10*res+ch-'0',ch=getchar();
	return res;
}

const int MAXN=5e5+5;
const int MAXD=10;
const int MAXA=1048576;
const int p=1e9+7;

inline int add(reg int a,reg int b){
	a+=b;
	return a>=p?a-p:a;
}

inline int sub(reg int a,reg int b){
	a-=b;
	return a<0?a+p:a;
}

int n,d;
int a[MAXN];
int f[MAXD][MAXA<<1];
int g[MAXA<<1];

int main(void){
	n=read(),d=read();
	reg int sum=0;
	for(reg int i=1;i<=n;++i)
		a[i]=read(),sum^=a[i];
	sort(a+1,a+n+1);
	f[0][0]=1;
	reg int u=1;
	for(reg int i=1;i<=n;++i){
		while(u<=a[i])
			u<<=1;
		for(reg int j=0;j<u;++j)
			g[j]=add(f[d-1][j^a[i]],f[0][j]);
		for(reg int j=d-1;j>0;--j)
			for(reg int k=0;k<u;++k)
				f[j][k]=add(f[j][k],f[j-1][k^a[i]]);
		for(reg int j=0;j<u;++j)
			f[0][j]=g[j];
	}
	printf("%d\n",sub(f[0][sum],!(n%d)));
	return 0;
}