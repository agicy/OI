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

inline void writeln(reg ll x){
	static char buf[32];
	reg int p=-1;
	if(x==0) putchar('0');
	else while(x) buf[++p]=(x%10)^'0',x/=10;
	while(~p) putchar(buf[p--]);
	putchar('\n');
	return;
}

const int MAXN=2e5+5;
const int MAXLOG2N=18+1;

int n,m;
int cnt,head[MAXN],to[MAXN],w[MAXN],Next[MAXN];

inline void Add_Edge(reg int u,reg int v,reg int len){
	Next[++cnt]=head[u];
	to[cnt]=v,w[cnt]=len;
	head[u]=cnt;
	return;
}

namespace BIT{
	inline int lowbit(reg int x){
		return x&(-x);
	}
	int n;
	int unit[MAXN];
	inline void Init(reg int s){
		n=s;
		return;
	}
	inline void update(reg int id,reg int val){
		for(reg int i=id;i<=n;i+=lowbit(i))
			unit[i]+=val;
		return;
	}
	inline int query(reg int id){
		reg int res=0;
		for(reg int i=id;i;i^=lowbit(i))
			res+=unit[i];
		return res;
	}
	inline int query(reg int l,reg int r){
		return query(r)-query(l-1);
	}
}

int fa[MAXN][MAXLOG2N],dep[MAXN];
ll dis[MAXN];
int tim,lef[MAXN],rig[MAXN];

inline void dfs(reg int u,reg int father){
	fa[u][0]=father;
	dep[u]=dep[father]+1;
	lef[u]=++tim;
	for(reg int i=1;i<MAXLOG2N;++i)
		fa[u][i]=fa[fa[u][i-1]][i-1];
	for(reg int i=head[u];i;i=Next[i]){
		reg int v=to[i];
		dis[v]=dis[u]+w[i];
		dfs(v,u);
	}
	rig[u]=tim;
	return;
}

inline int LCA(int x,int y){
	if(dep[x]>dep[y])
		swap(x,y);
	for(reg int i=MAXLOG2N-1;i>=0;--i)
		if(dep[fa[y][i]]>=dep[x])
			y=fa[y][i];
	if(x==y)
		return y;
	for(reg int i=MAXLOG2N-1;i>=0;--i)
		if(fa[x][i]!=fa[y][i])
			x=fa[x][i],y=fa[y][i];
	return fa[x][0];
}

inline int getSon(reg int u,reg int rt){
	for(reg int i=MAXLOG2N-1;i>=0;--i)
		if(dep[fa[u][i]]>dep[rt])
			u=fa[u][i];
	return u;
}

inline int getCnt(reg int x){
	return BIT::query(lef[x],rig[x]);
}

inline int getCnt(reg int rt,reg int dir){
	return getCnt(getSon(dir,rt));
}

int main(void){
	n=read();
	for(reg int i=2;i<=n;++i){
		static int p,d;
		p=read(),d=read();
		Add_Edge(p,i,d);
	}
	dfs(1,0);
	reg int rt=1;
	reg ll ans=0;
	writeln(ans);
	BIT::Init(n);
	BIT::update(lef[1],1);
	reg int cnt=1;
	for(reg int i=2;i<=n;i++){
		++cnt;
		reg int add=i;
		BIT::update(lef[add],1);
		reg int lca=LCA(rt,add);
		ans+=dis[add]+dis[rt]-(dis[lca]<<1);
		if(lca==rt){
			reg int Siz=getCnt(getSon(add,rt));
			if(Siz>(cnt>>1)){
				reg int x=add;
				for(reg int j=MAXLOG2N-1;j>=0;--j)
					if(fa[x][j]&&getCnt(fa[x][j],add)<=(cnt>>1))
						x=fa[x][j];
				reg ll delta=dis[x]-dis[rt];
				ans+=delta*(cnt-(Siz<<1));
				rt=x;
			}
		}
		else{
			reg int Siz=getCnt(rt);
			if(cnt-Siz>(cnt>>1)){
				reg int x=rt;
				for(reg int j=MAXLOG2N-1;j>=0;--j)
					if(fa[x][j]&&cnt-getCnt(fa[x][j])>(cnt>>1))
						x=fa[x][j];
				x=fa[x][0];
				reg ll delta=dis[x]-dis[rt];
				ans+=delta*(cnt-(Siz<<1));
				rt=x;
			}
		}
		writeln(ans);
	}
	flush();
	return 0;
}