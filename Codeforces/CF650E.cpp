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
	reg bool f=false;
	reg char ch=getchar();
	reg int res=0;
	while(!isdigit(ch))f|=(ch=='-'),ch=getchar();
	while(isdigit(ch))res=10*res+(ch^'0'),ch=getchar();
	return f?-res:res;
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

const int MAXN=5e5+5;

int n;
vector<int> G[2][MAXN];
int fa[2][MAXN];

inline void dfs(reg int u,reg int father,reg int c){
	fa[c][u]=father;
	for(int v:G[c][u])
		if(v!=father)
			dfs(v,u,c);
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
		reg int ra=find(a),rb=find(b);
		if(ra!=rb)
			fa[rb]=ra;
		return;
	}
	inline bool search(reg int a,reg int b){
		return find(a)==find(b);
	}
}

struct Event{
	int a,b,c,d;
	inline Event(reg int a=0,reg int b=0,reg int c=0,reg int d=0):a(a),b(b),c(c),d(d){
		return;
	}
};

int tot;
Event ans[MAXN<<1];

inline void dfs(reg int u,reg int father){
	for(int v:G[0][u])
		if(v!=father){
			dfs(v,u);
			if(fa[1][u]!=v&&fa[1][v]!=u)
				ans[++tot]=Event(v,u,UnionFind::find(v),fa[1][UnionFind::find(v)]);
		}
	return;
}

int main(void){
	n=read();
	for(reg int i=1;i<n;++i){
		static int u,v;
		u=read(),v=read();
		G[0][u].push_back(v),G[0][v].push_back(u);
	}
	dfs(1,0,0);
	for(reg int i=1;i<n;++i){
		static int u,v;
		u=read(),v=read();
		G[1][u].push_back(v),G[1][v].push_back(u);
	}
	dfs(1,0,1);
	for(reg int i=2;i<=n;++i){
		reg int tmp=fa[1][i];
		if(tmp==fa[0][i]||i==fa[0][tmp])
			UnionFind::fa[i]=tmp;
		else
			UnionFind::fa[i]=i;
	}
	dfs(1,0);
	write(tot),putchar('\n');
	for(reg int i=1;i<=tot;++i)
		write(ans[i].a),putchar(' '),write(ans[i].b),putchar(' '),write(ans[i].c),putchar(' '),write(ans[i].d),putchar('\n');
	flush();
	return 0;
}