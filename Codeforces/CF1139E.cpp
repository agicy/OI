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

inline void writeln(reg int x){
	static char buf[32];
	reg int p=-1;
	if(x==0) putchar('0');
	else while(x) buf[++p]=(x%10)^'0',x/=10;
	while(~p) putchar(buf[p--]);
	putchar('\n');
	return;
}

const int MAXN=5e3+5;
const int MAXM=5e3+5;

int n,m,d;
int p[MAXN],c[MAXN],k[MAXN];
bool del[MAXN];
int tim,vis[MAXM];
int mat[MAXM];
int ans[MAXN];
int cnt,head[MAXM],to[MAXN],Next[MAXN];

inline void Add_Edge(reg int u,reg int v){
	Next[++cnt]=head[u];
	to[cnt]=v;
	head[u]=cnt;
	return;
}

inline bool dfs(reg int u){
	for(reg int i=head[u];i;i=Next[i]){
		reg int v=to[i];
		if(vis[v]!=tim){
			vis[v]=tim;
			if(mat[v]==-1||dfs(mat[v])){
				mat[v]=u;
				return true;
			}
		}
	}
	return false;
}

int main(void){
	n=read(),m=read();
	for(reg int i=1;i<=n;++i)
		p[i]=read();
	for(reg int i=1;i<=n;++i)
		c[i]=read();
	d=read();
	for(reg int i=1;i<=d;++i)
		del[k[i]=read()]=true;
	for(reg int i=1;i<=n;++i)
		if(!del[i]&&p[i]<=m)
			Add_Edge(p[i],c[i]);
	memset(mat,-1,sizeof(mat));
	for(reg int i=d;i>=1;--i){
		for(reg int j=ans[i+1];j<=m;++j){
			++tim;
			if(!dfs(j)){
				ans[i]=j;
				break;
			}
		}
		if(p[k[i]]<=m)
			Add_Edge(p[k[i]],c[k[i]]);
	}
	for(reg int i=1;i<=d;++i)
		writeln(ans[i]);
	flush();
	return 0;
}