#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++)
static char buf[1<<21],*p1=buf,*p2=buf;
#define flush() (fwrite(wbuf,1,wp1,stdout),wp1=0)
#define putchar(c) (wp1==wp2&&(flush(),0),wbuf[wp1++]=c)
static char wbuf[1<<21];int wp1;const int wp2=1<<21;
inline int read(void){
	reg char ch=getchar();
	reg int res=0;
	while(!isdigit(ch)) ch=getchar();
	while(isdigit(ch)) res=10*res+(ch^'0'),ch=getchar();
	return res;
}

inline void write(reg int x){
	static char buf[32];
	reg int p=-1;
	if(x==0) putchar('0');
	else while(x) buf[++p]=(x%10)^'0',x/=10;
	while(~p) putchar(buf[p--]);
	return;
}

const int MAXN=200+5;

int n;
bitset<MAXN> G[MAXN];

int main(void){
	n=read();
	for(reg int i=1;i<=n;++i){
		reg int deg=read();
		for(reg int j=1;j<=deg;++j)
			G[i][read()]=true;
		if(deg&1)
			G[i][i]=G[i][n+1]=true;
	}
	for(reg int i=1;i<=n;++i){
		reg int Max=i;
		for(reg int j=i+1;j<=n;++j)
			if(G[j][i]>G[Max][i])
				Max=j;
		swap(G[Max],G[i]);
		G[i][i]=true;
		for(reg int j=1;j<=n;++j)
			if(j!=i&&G[j][i])
				G[j]^=G[i];
	}
	reg int tot=0;
	static int ans[MAXN];
	for(reg int i=1;i<=n;++i)
		if(G[i][n+1])
			ans[++tot]=i;
	write(tot),putchar('\n');
	for(reg int i=1;i<=tot;++i)
		write(ans[i]),putchar(i==tot?'\n':' ');
	flush();
	return 0;
}