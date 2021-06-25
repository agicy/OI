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

inline int max(reg int a,reg int b){
	return a>b?a:b;
}

const int MAXN=3e5+5;

int n,m,q;
int cnt,head[MAXN],to[MAXN<<1],Next[MAXN<<1];

inline void Add_Edge(reg int u,reg int v){
	Next[++cnt]=head[u];
	to[cnt]=v;
	head[u]=cnt;
	return;
}

namespace UnionFind{
	int fa[MAXN];
	inline void Init(reg int n){
		for(reg int i=1;i<=n;++i)
			fa[i]=i;
		return;
	}
	inline int find(reg int x){
		if(x==fa[x])
			return x;
		else
			return fa[x]=find(fa[x]);
	}
	inline void merge(reg int a,reg int b){
		fa[find(b)]=find(a);
		return;
	}
	inline bool search(reg int a,reg int b){
		return find(a)==find(b);
	}
}

bool vis[MAXN];
int f[MAXN][2];
int len[MAXN],tmp;

inline void dfs(reg int u,reg int father){
	f[u][0]=f[u][1]=0;
	for(reg int i=head[u];i;i=Next[i]){
		reg int v=to[i];
		if(v!=father){
			dfs(v,u);
			if(f[u][0]<f[v][0]+1)
				f[u][1]=f[u][0],f[u][0]=f[v][0]+1;
			else if(f[u][1]<f[v][0]+1)
				f[u][1]=f[v][0]+1;
		}
	}
	tmp=max(tmp,f[u][0]+f[u][1]);
	return;
}

int main(void){
	n=read(),m=read(),q=read();
	UnionFind::Init(n);
	for(reg int i=1;i<=m;++i){
		static int x,y;
		x=read(),y=read();
		Add_Edge(x,y),Add_Edge(y,x);
		UnionFind::merge(x,y);
	}
	for(reg int i=1;i<=n;++i)
		if(!vis[UnionFind::find(i)]){
			vis[UnionFind::find(i)]=true;
			tmp=0;
			dfs(UnionFind::find(i),0);
			len[UnionFind::find(i)]=tmp;
		}
	while(q--){
		static int opt,x,y;
		opt=read();
		switch(opt){
			case 1:{
				x=read();
				writeln(len[UnionFind::find(x)]);
				break;
			}
			case 2:{
				x=read(),y=read();
				if(!UnionFind::search(x,y)){
					reg int rx=UnionFind::find(x),ry=UnionFind::find(y);
					reg int Max=max(max(len[rx],len[ry]),((len[rx]+1)>>1)+((len[ry]+1)>>1)+1);
					UnionFind::fa[ry]=rx;
					len[rx]=Max;
				}
				break;
			}
		}
	}
	flush();
	return 0;
}