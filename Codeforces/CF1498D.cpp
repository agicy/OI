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

inline ll readll(void){
	reg char ch=getchar();
	reg ll res=0;
	while(!isdigit(ch))ch=getchar();
	while(isdigit(ch))res=10*res+(ch^'0'),ch=getchar();
	return res;
}

inline void write(reg int x){
	static char buf[32];
	reg int p=-1;
	if(x<0) x=-x,putchar('-');
	if(x==0) putchar('0');
	else while(x) buf[++p]=(x%10)^'0',x/=10;
	while(~p) putchar(buf[p--]);
	return;
}

inline int min(reg int a,reg int b){
	return a<b?a:b;
}

const int MAXN=1e5+5;
const int inf=0x3f3f3f3f;
const int base=1e5;

int n,m;
int f[MAXN],g[MAXN];

inline void solve(reg int id){
	static int t,y;
	static ll x;
	fill(g+1,g+m+1,inf);
	t=read(),x=readll(),y=read();
	switch(t){
		case 1:{
			x=(x+base-1)/base;
			g[x]=1;
			for(reg int i=1;i<=m;++i)
				if(f[i]!=inf)
					g[i]=0;
			for(reg int i=1;i<=m;++i)
				if(g[i]!=y&&g[i]!=inf&&i+x<=m)
					g[i+x]=min(g[i+x],g[i]+1);
			for(reg int i=1;i<=m;++i)
				if(g[i]<=y&&f[i]==inf)
					f[i]=id;
			break;
		}
		case 2:{
			for(reg int i=1;i<=m;++i)
				if(f[i]!=inf)
					g[i]=0;
			for(reg int i=1;i<=m;++i){
				reg ll p=(1ll*i*x+base-1)/base;
				if(g[i]!=y&&g[i]!=inf&&p<=m)
					g[p]=min(g[p],g[i]+1);
			}
			for(reg int i=1;i<=m;++i)
				if(g[i]<=y&&f[i]==inf)
					f[i]=id;
			break;
		}
	}
	return;
}

int main(void){
	n=read(),m=read();
	fill(f+1,f+m+1,inf);
	for(reg int i=1;i<=n;++i)
		solve(i);
	for(reg int i=1;i<=m;++i)
		write(f[i]==inf?-1:f[i]),putchar(i==m?'\n':' ');
	flush();
	return 0;
}