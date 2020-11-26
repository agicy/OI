#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
typedef unsigned long long ull;
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++)
static char buf[100000],*p1=buf,*p2=buf;
inline int read(void){
	reg bool f=false;
	reg char ch=getchar();
	reg int res=0;
	while(ch<'0'||'9'<ch)f|=(ch=='-'),ch=getchar();
	while('0'<=ch&&ch<='9')res=10*res+ch-'0',ch=getchar();
	return f?-res:res;
}

const int MAXN=4e4+5;
const int MAXLOG2N=16+1;

int n,p,q;

int ans[MAXN],V[MAXN];
struct Query{
	int op,x,l,r,k,v,id;
};

Query Q[MAXN*5],q1[MAXN*5],q2[MAXN*5];

inline bool cmp(const Query& a,const Query& b){
	if(a.x!=b.x)
		return a.x<b.x;
	else
		return a.op<b.op;
}

int cnt,head[MAXN],to[MAXN<<1],Next[MAXN<<1];

inline void Add_Edge(reg int u,reg int v){
	Next[++cnt]=head[u];
	to[cnt]=v;
	head[u]=cnt;
	return;
}

int fa[MAXN][MAXLOG2N],dep[MAXN];
int siz[MAXN],son[MAXN];

inline void dfs1(reg int u,reg int father){
	siz[u]=1;
	fa[u][0]=father;
	dep[u]=dep[father]+1;
	for(reg int i=1;i<MAXLOG2N;++i)
		fa[u][i]=fa[fa[u][i-1]][i-1];
	for(reg int i=head[u];i;i=Next[i])
		if(to[i]!=father){
			dfs1(to[i],u);
			siz[u]+=siz[to[i]];
			if(siz[to[i]]>siz[son[u]])
				son[u]=to[i];
		}
	return;
}

int tim,dfn[MAXN],ed[MAXN];
int top[MAXN];

inline void dfs2(reg int u,reg int father,reg int topf){
	top[u]=topf;
	dfn[u]=++tim;
	ed[u]=dfn[u]+siz[u]-1;
	if(son[u])
		dfs2(son[u],u,topf);
	for(reg int i=head[u];i;i=Next[i])
		if(to[i]!=father&&to[i]!=son[u])
			dfs2(to[i],u,to[i]);
	return;
}

inline int LCA(int x,int y){
	if(dep[x]>dep[y])
		swap(x,y);
	for(reg int i=MAXLOG2N-1;i>=0;--i)
		if(dep[fa[y][i]]>=dep[x])
			y=fa[y][i];
	if(x==y)
		return x;
	for(reg int i=MAXLOG2N-1;i>=0;--i)
		if(fa[x][i]!=fa[y][i])
			x=fa[x][i],y=fa[y][i];
	return fa[x][0];
}

int getson(int x,int y){
	while(top[x]!=top[y]){
		if(fa[top[x]][0]==y)
			return top[x];
		x=fa[top[x]][0];
	}
	return son[y];
}

struct TreeArray{
	#define lowbit(x) ( (x) & ( - (x) ) )
	int n,unit[MAXN];
	inline void Init(reg int siz){
		n=siz;
		memset(unit,0,sizeof(unit));
		return;
	}
	inline void Update(reg int u,reg int val){
		for(reg int i=u;i<=n;i+=lowbit(i))
			unit[i]+=val;
		return;
	}
	inline int Query(reg int u){
		reg int res=0;
		for(reg int i=u;i;i-=lowbit(i))
			res+=unit[i];
		return res;
	}
	#undef lowbit
};

TreeArray T;

void solve(int l,int r,int L,int R){
	if(L>R)
		return;
	if(l==r){
		for(reg int i=L;i<=R;++i)
			if(Q[i].op==2)
				ans[Q[i].id]=V[l];
		return;
	}
	int mid=(l+r)>>1,cnt1=0,cnt2=0,val;
	for(reg int i=L;i<=R;++i){
		if(Q[i].op==1){
			if(Q[i].k<=mid){
				T.Update(Q[i].l,Q[i].v);
				T.Update(Q[i].r+1,-Q[i].v);
				q1[++cnt1]=Q[i];
			}
			else q2[++cnt2]=Q[i];
		}
		else {
			val=T.Query(Q[i].l);
			if(val>=Q[i].k)
				q1[++cnt1]=Q[i];
			else
				Q[i].k-=val,q2[++cnt2]=Q[i];
		}
	}
	for(int i=1;i<=cnt1;++i)
		Q[L+i-1]=q1[i];
	for(int i=1;i<=cnt2;++i)
		Q[L+i+cnt1-1]=q2[i];
	solve(l,mid,L,L+cnt1-1);
	solve(mid+1,r,L+cnt1,R);
	return;
}

int main(void){
	n=read(),p=read(),q=read();
	T.Init(n);
	for(reg int i=1;i<n;++i){
		static int x,y;
		x=read(),y=read();
		Add_Edge(x,y);
		Add_Edge(y,x);
	}
	dfs1(1,0);
	dfs2(1,0,1);
	reg int cnt=0;
	for(int i=1;i<=p;++i){
		static int x,y,k;
		x=read(),y=read(),k=read();
		V[i]=k;
		if(dfn[x]>dfn[y])
			swap(x,y);
		reg int lca=LCA(x,y);
		if(lca==x){
			reg int z=getson(y,x);
			if(dfn[z]>1){
				Q[++cnt]=(Query){1,1,dfn[y],ed[y],k,1,0};
				Q[++cnt]=(Query){1,dfn[z],dfn[y],ed[y],k,-1,0};
			}
			if(ed[z]<n){
				Q[++cnt]=(Query){1,dfn[y],ed[z]+1,n,k,1,0};
				Q[++cnt]=(Query){1,ed[y]+1,ed[z]+1,n,k,-1,0};
			}
		}
		else{
			Q[++cnt]=(Query){1,dfn[x],dfn[y],ed[y],k,1,0};
			Q[++cnt]=(Query){1,ed[x]+1,dfn[y],ed[y],k,-1,0};
		}
	}
	sort(V+1,V+p+1);
	reg int lim=unique(V+1,V+p+1)-(V+1);
	for(reg int i=1;i<=cnt;++i)
		Q[i].k=lower_bound(V+1,V+lim+1,Q[i].k)-V;
	for(reg int i=1;i<=q;++i){
		static int x,y,k;
		x=read(),y=read(),k=read();
		if(dfn[x]>dfn[y])
			swap(x,y);
		Q[++cnt]=(Query){2,dfn[x],dfn[y],0,k,0,i};
	}
	sort(Q+1,Q+cnt+1,cmp);
	solve(1,lim,1,cnt);
	for(reg int i=1;i<=q;++i)
		printf("%d\n",ans[i]);
	return 0;
}