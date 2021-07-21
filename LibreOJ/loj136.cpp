#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;

bool st;

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

inline void writeln(reg int x){
	static char buf[32];
	reg int p=-1;
	if(x<0) x=-x,putchar('-');
	if(!x) putchar('0');
	else while(x) buf[++p]=(x%10)^'0',x/=10;
	while(~p) putchar(buf[p--]);
	putchar('\n');
	return;
}

const int MAXN=1e3+5;
const int MAXM=1e5+5;
const int inf=0x3f3f3f3f;

struct edge{
	int u,v,w;
	inline bool operator<(const edge& a)const{
		return w<a.w;
	}
};

namespace UnionFind{
	int fa[MAXN<<1];
	inline void init(reg int n){
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
		fa[rb]=ra;
		return;
	}
	inline bool search(reg int a,reg int b){
		return find(a)==find(b);
	}
}

namespace Tree{
	const int MAXV=MAXN<<1;
	const int MAXLOG2V=11+1;
	int w[MAXV];
	int cnt,head[MAXV],to[MAXV],nxt[MAXV];
	inline void Add_Edge(reg int u,reg int v){
		nxt[++cnt]=head[u];
		to[cnt]=v;
		head[u]=cnt;
		return;
	}
	int tim,dfn[MAXV];
	int val[MAXV<<1];
	inline void dfs(reg int u){
		val[dfn[u]=++tim]=w[u];
		for(reg int i=head[u];i;i=nxt[i]){
			reg int v=to[i];
			dfs(v);
			val[++tim]=w[u];
		}
		return;
	}
	namespace ST{
		int lg[MAXV<<1];
		int Max[MAXLOG2V+1][MAXV<<1];
		inline void init(reg int n,reg int a[]){
			lg[0]=-1;
			for(reg int i=1;i<=n;++i)
				lg[i]=lg[i>>1]+1;
			for(reg int i=1;i<=n;++i)
				Max[0][i]=a[i];
			for(reg int j=1;j<MAXLOG2V;++j)
				for(reg int i=1;i+(1<<j)-1<=n;++i)
					Max[j][i]=max(Max[j-1][i],Max[j-1][i+(1<<(j-1))]);
			return;
		}
		inline int query(reg int l,reg int r){
			reg int k=lg[r-l+1];
			return max(Max[k][l],Max[k][r-(1<<k)+1]);
		}
	}
}


int n,m,k;
edge e[MAXM+MAXN];

bool ed;

int main(void){
	n=read(),m=read(),k=read();
	for(reg int i=1;i<=m;++i)
		e[i].u=read(),e[i].v=read(),e[i].w=read();
	for(reg int i=1;i<n;++i)
		e[i+m].u=i,e[i+m].v=i+1,e[i+m].w=inf;
	sort(e+1,e+n+m);
	UnionFind::init(n<<1);
	reg int tot=n;
	for(reg int i=1;i<n+m;++i)
		if(!UnionFind::search(e[i].u,e[i].v)){
			reg int k=++tot;
			Tree::w[k]=e[i].w;
			Tree::Add_Edge(k,UnionFind::find(e[i].u));
			Tree::Add_Edge(k,UnionFind::find(e[i].v));
			UnionFind::merge(k,e[i].u);
			UnionFind::merge(k,e[i].v);
		}
	reg int rt=tot;
	Tree::dfs(rt);
	Tree::ST::init(Tree::tim,Tree::val);
	while(k--){
		static int s,t;
		s=read(),t=read();
		reg int l=min(Tree::dfn[s],Tree::dfn[t]);
		reg int r=max(Tree::dfn[s],Tree::dfn[t]);
		reg int res=Tree::ST::query(l,r);
		if(res==inf)
			writeln(-1);
		else
			writeln(res);
	}
	flush();
	fprintf(stderr,"%.3lf s\n",1.0*clock()/CLOCKS_PER_SEC);
	fprintf(stderr,"%.3lf MiB\n",(&ed-&st)/1048576.0);
	return 0;
}