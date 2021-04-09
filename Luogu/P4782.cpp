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

inline void writeln(const char *s){
	while(*s) putchar(*(s++));
	putchar('\n');
	return;
}

const int MAXN=1e6+5;
const int MAXM=1e6+5;
const int MAXV=MAXN*2;
const int MAXE=MAXM*2;

int n,m;
int cnt,head[MAXV],to[MAXE],Next[MAXE];

inline void Add_Edge(reg int u,reg int v){
	Next[++cnt]=head[u];
	to[cnt]=v;
	head[u]=cnt;
	return;
}

bool vis[MAXV];
int tim,dfn[MAXV],low[MAXV];
int top,S[MAXV];
int scc_cnt,col[MAXV];

inline void tarjan(reg int u){
	dfn[u]=low[u]=++tim;
	vis[u]=true;
	S[++top]=u;
	for(reg int i=head[u];i;i=Next[i]){
		reg int v=to[i];
		if(!dfn[v]){
			tarjan(v);
			low[u]=min(low[u],low[v]);
		}
		else if(vis[v])
			low[u]=min(low[u],dfn[v]);
	}
	if(dfn[u]==low[u]){
		++scc_cnt;
		reg int v;
		do{
			v=S[top--];
			vis[v]=false;
			col[v]=scc_cnt;
		}while(u!=v);
	}
	return;
}

inline int getId(reg int i,reg int c){
	return i+c*n;
}

int main(void){
	n=read(),m=read();
	while(m--){
		static int i,a,j,b;
		i=read(),a=read(),j=read(),b=read();
		Add_Edge(getId(i,!a),getId(j,b));
		Add_Edge(getId(j,!b),getId(i,a));
	}
	for(reg int i=1;i<=(n<<1);++i)
		if(!dfn[i])
			tarjan(i);
	reg bool flag=true;
	for(reg int i=1;i<=n;++i)
		if(col[getId(i,0)]==col[getId(i,1)]){
			flag=false;
			break;
		}
	if(flag){
		writeln("POSSIBLE");
		for(reg int i=1;i<=n;++i){
			if(col[getId(i,0)]<col[getId(i,1)])
				putchar('0');
			else
				putchar('1');
			putchar(i==n?'\n':' ');
		}
	}
	else
		writeln("IMPOSSIBLE");
	flush();
	return 0;
}