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

inline int lowbit(reg int x){
	return x&(-x);
}

const int MAXN=16;
const int p=1e9+7;

inline int sub(reg int a,reg int b){
	a-=b;
	return a<0?a+p:a;
}

int n;
int c[MAXN][MAXN];
int f[1<<MAXN],g[1<<MAXN];

int main(void){
	n=read();
	for(reg int i=0;i<n;++i)
		for(reg int j=0;j<n;++j)
			c[i][j]=read();
	for(reg int S=0;S<(1<<n);++S){
		g[S]=1;
		for(reg int i=0;i<n;++i)
			for(reg int j=i+1;j<n;++j)
				if(((S>>i)&1)&&((S>>j)&1))
					g[S]=1ll*g[S]*(c[i][j]+1)%p;
	}
	for(reg int S=0;S<(1<<n);++S){
		f[S]=g[S];
		for(reg int s=S&(S-1);s;s=S&(s-1))
			if((s&lowbit(S)))
				f[S]=sub(f[S],1ll*f[s]*g[S^s]%p);
	}
	printf("%d\n",f[(1<<n)-1]);
	return 0;
}