#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
#define getchar()(p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++)
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
	if(x==0) putchar('0');
	else while(x) buf[++p]=(x%10)^'0',x/=10;
	while(~p) putchar(buf[p--]);
	return;
}

const int MAXN=3e3+5;

int n;
int a[MAXN];
int cnt,head[MAXN],to[MAXN<<1],Next[MAXN<<1];

inline void Add_Edge(reg int u,reg int v){
	Next[++cnt]=head[u];
	to[cnt]=v;
	head[u]=cnt;
	return;
}

inline bool dfs(reg int u){
	for(reg int i=head[u];i;i=Next[i])
		if(!dfs(to[i]))
			return true;
	return false;
}

int main(void){
	n=read();
	for(reg int i=1;i<=n;++i)
		a[i]=read();
	for(reg int i=1;i<n;++i){
		static int u,v;
		u=read(),v=read();
		if(a[u]>a[v])
			Add_Edge(u,v);
		if(a[v]>a[u])
			Add_Edge(v,u);
	}
	reg int tot=0;
	static int ans[MAXN];
	for(reg int i=1;i<=n;++i)
		if(dfs(i))
			ans[++tot]=i;
	for(reg int i=1;i<=tot;++i)
		write(ans[i]),putchar(i==tot?'\n':' ');
	flush();
	return 0;
}