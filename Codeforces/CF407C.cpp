#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++)
static char buf[100000],*p1=buf,*p2=buf;
#define flush() (fwrite(wbuf,1,wp1,stdout),wp1=0)
#define putchar(c) (wp1==wp2&&(flush(),0),wbuf[wp1++]=c)
static char wbuf[1<<21];int wp1;const int wp2=1<<21;
inline int read(void){
	reg char ch=getchar();
	reg int res=0;
	while(!isdigit(ch))ch=getchar();
	while(isdigit(ch))res=10*res+(ch^'0'),ch=getchar();
	return res;
}

inline void write(reg int x){
	static char buf[32];
	reg int p=-1;
	if(!x) putchar('0');
	else while(x) buf[++p]=(x%10)^'0',x/=10;
	while(~p) putchar(buf[p--]);
	return;
}

const int MAXN=1e5+5;
const int mod=1e9+7;
const int K=100;

inline int add(reg int a,reg int b){
	a+=b;
	return a>=mod?a-mod:a;
}

inline int sub(reg int a,reg int b){
	a-=b;
	return a<0?a+mod:a;
}

int n,m;
int a[MAXN];
int binom[MAXN+K][K+1];
int ans[MAXN][K+2];

inline void Init(void){
	binom[0][0]=1;
	for(reg int i=1;i<=n+K;++i){
		binom[i][0]=1;
		for(reg int j=1;j<=i&&j<=K;++j)
			binom[i][j]=add(binom[i-1][j-1],binom[i-1][j]);
	}
	return;
}

int main(void){
	n=read(),m=read();
	Init();
	for(reg int i=1;i<=n;++i)
		a[i]=read();
	while(m--){
		static int l,r,k;
		l=read(),r=read(),k=read();
		for(reg int i=0;i<=k;++i)
			ans[l][i]=add(ans[l][i],binom[k][k-i]);
		if(r<n)
			for(reg int i=0;i<=k;++i)
				ans[r+1][i]=sub(ans[r+1][i],binom[r-l+1+k][k-i]);
	}
	for(reg int i=1;i<n;++i)
		for(reg int j=K+1;j>=1;--j)
			ans[i+1][j-1]=add(ans[i+1][j-1],add(ans[i][j],ans[i][j-1]));
	for(reg int i=1;i<=n;++i)
		write(add(ans[i][0],a[i])),putchar(i==n?'\n':' ');
	flush();
	return 0;
}