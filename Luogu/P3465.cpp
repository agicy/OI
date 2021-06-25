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
	while(!isdigit(ch))ch=getchar();
	while(isdigit(ch))res=10*res+(ch^'0'),ch=getchar();
	return res;
}

inline void writeln(reg int x){
	static char buf[32];
	reg int p=-1;
	if(x==0) putchar('0');
	else while(x) buf[++p]=(x%10)^'0',x/=10;
	while(~p) putchar(buf[p--]);
	putchar('\n');
	return;
}

const int MAXN=1e5+5;
const int MAXM=2e5+5;

int n,m;
int cnt,head[MAXN],to[MAXM<<1],Next[MAXM<<1];
bool vis[MAXN];
bool flag;
int ans[MAXN];

inline void Add_Edge(reg int u,reg int v){
	Next[++cnt]=head[u];
	to[cnt]=v;
	head[u]=cnt;
	return;
}

inline void update(reg int u,reg int pre){
	if(ans[u])
		update(ans[u],u);
	ans[u]=pre;
	return;
}

inline void dfs(reg int u,reg int father){
	vis[u]=true;
	for(reg int i=head[u];i;i=Next[i]){
		reg int v=to[i];
		if(v!=father){
			if(vis[v]){
				if(!flag){
					flag=true;
					update(v,u);
				}
			}
			else{
				ans[v]=u;
				dfs(v,u);
			}
		}
	}
	return;
}

int main(void){
	n=read(),m=read();
	for(reg int i=1;i<=m;++i){
		static int a,b;
		a=read(),b=read();
		Add_Edge(a,b),Add_Edge(b,a);
	}
	for(reg int i=1;i<=n;++i)
		if(!vis[i]){
			flag=false;
			dfs(i,0);
			if(!flag){
				puts("NIE");
				return 0;
			}
		}
	puts("TAK");
	for(reg int i=1;i<=n;++i)
		writeln(ans[i]);
	flush();
	return 0;
}