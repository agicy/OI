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

const int MAXN=1e5+5;
const int MAXM=1e5+5;

struct querys{
	int id,l,r,lca;
	int lId,rId;
	inline bool operator<(const querys& a)const{
		if(lId==a.lId)
			return (lId&1)?r<a.r:r>a.r;
		else
			return l<a.l;
	}
};

int n,m;
vector<int> V;
int a[MAXN];
querys q[MAXM];
int cnt,head[MAXN],to[MAXN<<1],Next[MAXN<<1];

inline void Add_Edge(reg int u,reg int v){
	Next[++cnt]=head[u];
	to[cnt]=v;
	head[u]=cnt;
	return;
}

int fa[MAXN],dep[MAXN];
int siz[MAXN],son[MAXN];
int tim,lef[MAXN],rig[MAXN],rnk[MAXN];

inline void dfs1(reg int u,reg int father){
	siz[u]=1;
	fa[u]=father;
	dep[u]=dep[father]+1;
	rnk[lef[u]=++tim]=u;
	for(reg int i=head[u];i;i=Next[i]){
		reg int v=to[i];
		if(v!=father){
			dfs1(v,u);
			siz[u]+=siz[v];
			if(siz[son[u]]<siz[v])
				son[u]=v;
		}
	}
	rnk[rig[u]=++tim]=u;
	return;
}

int top[MAXN];

inline void dfs2(reg int u,reg int father,reg int topf){
	top[u]=topf;
	if(!son[u])
		return;
	dfs2(son[u],u,topf);
	for(reg int i=head[u];i;i=Next[i]){
		reg int v=to[i];
		if(v!=father&&v!=son[u])
			dfs2(v,u,v);
	}
	return;
}

inline int LCA(int x,int y){
	while(top[x]!=top[y]){
		if(dep[top[x]]>dep[top[y]])
			swap(x,y);
		y=fa[top[y]];
	}
	return dep[x]<dep[y]?x:y;
}

int ans;
bool vis[MAXN];
int T[MAXN];

inline void add(reg int x){
	if(!T[a[x]]) ++ans;
	++T[a[x]];
	return;
}

inline void del(reg int x){
	--T[a[x]];
	if(!T[a[x]]) --ans;
	return;
}

inline void calc(reg int x){
	if(!vis[x])
		add(x),vis[x]=true;
	else
		del(x),vis[x]=false;
	return;
}

int Ans[MAXM];

int main(void){
	n=read(),m=read();
	for(reg int i=1;i<=n;++i){
		a[i]=read();
		V.push_back(a[i]);
	}
	sort(V.begin(),V.end());
	V.erase(unique(V.begin(),V.end()),V.end());
	for(reg int i=1;i<=n;++i)
		a[i]=lower_bound(V.begin(),V.end(),a[i])-V.begin()+1;
	for(reg int i=1;i<n;++i){
		static int x,y;
		x=read(),y=read();
		Add_Edge(x,y),Add_Edge(y,x);
	}
	dfs1(1,0),dfs2(1,0,1);
	reg int B=n*2/sqrt(m*2/3);
	for(reg int i=1;i<=m;++i){
		static int x,y;
		x=read(),y=read();
		if(lef[x]>lef[y])
			swap(x,y);
		q[i].id=i,q[i].lca=LCA(x,y);
		if(q[i].lca==x){
			q[i].l=lef[x],q[i].r=lef[y];
			q[i].lId=lef[x]/B,q[i].rId=lef[y]/B;
			q[i].lca=0;
		}
		else{
			q[i].l=rig[x],q[i].r=lef[y];
			q[i].lId=rig[x]/B,q[i].rId=lef[y]/B;
		}
	}
	sort(q+1,q+m+1);
	for(reg int i=1,l=1,r=0;i<=m;++i){
		while(l>q[i].l) calc(rnk[--l]);
		while(l<q[i].l) calc(rnk[l++]);
		while(r>q[i].r) calc(rnk[r--]);
		while(r<q[i].r) calc(rnk[++r]);
		if(q[i].lca) calc(q[i].lca);
		Ans[q[i].id]=ans;
		if(q[i].lca) calc(q[i].lca);
	}
	for(reg int i=1;i<=m;++i)
		writeln(Ans[i]);
	flush();
	return 0;
}