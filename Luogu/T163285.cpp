#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++)
static char buf[100000],*p1=buf,*p2=buf;
#define flush() (fwrite(wbuf,1,wp1,stdout),wp1=0)
#define putchar(c)(wp1==wp2&&(flush(),0),wbuf[wp1++]=c)
static char wbuf[1<<21];int wp1;const int wp2=1<<21;
inline int read(void){
	reg char ch=getchar();
	reg int res=0;
	while(!isdigit(ch))ch=getchar();
	while(isdigit(ch))res=10*res+(ch^'0'),ch=getchar();
	return res;
}

const int MAXN=2e5+5;

int n;
int lasa[MAXN],lasb[MAXN];
int cnt,head[MAXN],to[MAXN<<2],Next[MAXN<<2];
int col[MAXN];

inline void Add_Edge(reg int u,reg int v){
	Next[++cnt]=head[u];
	to[cnt]=v;
	head[u]=cnt;
	return;
}

inline void dfs(int u,int color){
	col[u]=color;
	for(reg int i=head[u];i;i=Next[i]){
		reg int v=to[i];
		if(!(~col[v]))
			dfs(v,color^1);
	}
	return;
}
int main(void){
	n=read();
	memset(col,-1,sizeof(col));
	for(reg int i=1,x,y;i<=n;++i){
		x=read(),y=read();
		if(lasa[x]){
			Add_Edge(lasa[x],i),Add_Edge(i,lasa[x]);
			lasa[x]=0;
		}
		else
			lasa[x]=i;
		if(lasb[y]){
			Add_Edge(lasb[y],i),Add_Edge(i,lasb[y]);
			lasb[y]=0;
		}
		else
			lasb[y]=i;
	}
	for(reg int i=1;i<=n;++i)
		if(!(~col[i]))
			dfs(i,0);
	putchar('Y'),putchar('e'),putchar('s'),putchar('\n');
	for(reg int i=1;i<=n;++i)
		putchar(col[i]?'w':'b');
	putchar('\n');
	flush();
	return 0;
}