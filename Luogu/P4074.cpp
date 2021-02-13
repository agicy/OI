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

const int MAXN=1e5+5;
const int MAXM=1e5+5;
const int MAXQ=1e5+5;

struct querys{
	int id;
	int l,r,t,lca;
	int lId,rId;
	inline bool operator<(const querys& a)const{
		return lId<a.lId||(lId==a.lId&&(((lId&1)?rId<a.rId:rId>a.rId)||(rId==a.rId&&(((lId^rId)&1)?t<a.t:t>a.t))));
	}
};

struct updates{
	int x,c;
	inline updates(reg int x=0,reg int c=0):x(x),c(c){
		return;
	}
};

int n,m,Q;
int v[MAXM],w[MAXN],c[MAXN];
int cnt,head[MAXN],to[MAXN<<1],Next[MAXN<<1];
querys q[MAXQ];
updates t[MAXQ];

inline void Add_Edge(reg int u,reg int v){
	Next[++cnt]=head[u];
	to[cnt]=v;
	head[u]=cnt;
	return;
}

int fa[MAXN],dep[MAXN];
int siz[MAXN],son[MAXN];
int tim,lef[MAXN],rig[MAXN],rnk[MAXN<<1];

inline void dfs1(reg int u,reg int father){
	siz[u]=1;
	fa[u]=father;
	rnk[lef[u]=++tim]=u;
	dep[u]=dep[father]+1;
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

inline int LCA(reg int x,reg int y){
	while(top[x]!=top[y])
		if(dep[top[x]]>dep[top[y]])
			x=fa[top[x]];
		else
			y=fa[top[y]];
	return dep[x]<dep[y]?x:y;
}

ll sum,ans[MAXQ];
bool vis[MAXN];
int T[MAXM];

inline void calc(reg int x){
	reg int col=c[x];
	if(!vis[x]){
		vis[x]=true;
		sum+=1ll*w[++T[col]]*v[col];
	}
	else{
		vis[x]=false;
		sum-=1ll*w[T[col]--]*v[col];
	}
	return;
}

inline void upda(reg int i){
	reg int u=t[i].x,x=t[i].c,y=c[u];
	if(vis[u])
		sum+=1ll*w[++T[x]]*v[x]-1ll*w[T[y]--]*v[y];
	t[i].c=y,c[u]=x;
	return;
}

int main(void){
	n=read(),m=read(),Q=read();
	for(reg int i=1;i<=m;++i)
		v[i]=read();
	for(reg int i=1;i<=n;++i)
		w[i]=read();
	for(reg int i=1;i<n;++i){
		static int u,v;
		u=read(),v=read();
		Add_Edge(u,v),Add_Edge(v,u);
	}
	for(reg int i=1;i<=n;++i)
		c[i]=read();
	dfs1(1,0),dfs2(1,0,1);
	reg int totQ=0,totU=0;
	for(reg int i=1;i<=Q;++i){
		static int opt,x,y;
		opt=read();
		switch(opt){
			case 0:{
				x=read(),y=read();
				t[++totU]=updates(x,y);
				break;
			}
			case 1:{
				x=read(),y=read();
				if(lef[x]>lef[y])
					swap(x,y);
				reg int lca=LCA(x,y);
				if(lca==x){
					++totQ;
					q[totQ].id=totQ;
					q[totQ].l=lef[x],q[totQ].r=lef[y],q[totQ].t=totU,q[totQ].lca=0;
					q[totQ].lId=lef[x],q[totQ].rId=lef[y];
				}
				else{
					++totQ;
					q[totQ].id=totQ;
					q[totQ].l=rig[x],q[totQ].r=lef[y],q[totQ].t=totU,q[totQ].lca=lca;
					q[totQ].lId=rig[x],q[totQ].rId=lef[y];
				}
				break;
			}
		}
	}
	reg int B=pow(n,totU?0.666667:0.5);
	for(reg int i=1;i<=totQ;++i)
		q[i].lId/=B,q[i].rId/=B;
	sort(q+1,q+totQ+1);
	reg int l=1,r=0,t=0;
	for(reg int i=1;i<=totQ;++i){
		while(l>q[i].l) calc(rnk[--l]);
		while(l<q[i].l) calc(rnk[l++]);
		while(r<q[i].r) calc(rnk[++r]);
		while(r>q[i].r) calc(rnk[r--]);
		while(t<q[i].t) upda(++t);
		while(t>q[i].t) upda(t--);
		if(q[i].lca) calc(q[i].lca);
		ans[q[i].id]=sum;
		if(q[i].lca) calc(q[i].lca);
	}
	for(reg int i=1;i<=totQ;++i)
		writeln(ans[i]);
	flush();
	return 0;
}