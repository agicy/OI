#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++)
static char buf[100000],*p1=buf,*p2=buf;
inline int read(void){
	reg char ch=getchar();
	reg int res=0;
	while(!isdigit(ch))ch=getchar();
	while(isdigit(ch))res=10*res+(ch^'0'),ch=getchar();
	return res;
}

const int MAXN=1e5+5;
const int MAXM=1e5+5;
const int MAXC=1e5+5;

struct querys{
	int id,k;
	inline querys(reg int id=0,reg int k=0):id(id),k(k){
		return;
	}
};

int n,m;
int c[MAXN];
int cnt,head[MAXN],to[MAXN<<1],Next[MAXN<<1];
vector<querys> q[MAXN];

inline void Add_Edge(reg int u,reg int v){
	Next[++cnt]=head[u];
	to[cnt]=v;
	head[u]=cnt;
	return;
}

int siz[MAXN],son[MAXN];
int tim,dfn[MAXN],rnk[MAXN];

inline void dfs1(reg int u,reg int father){
	siz[u]=1;
	dfn[u]=++tim;
	rnk[tim]=u;
	for(reg int i=head[u];i;i=Next[i]){
		reg int v=to[i];
		if(v!=father){
			dfs1(v,u);
			siz[u]+=siz[v];
			if(siz[son[u]]<siz[v])
				son[u]=v;
		}
	}
	return;
}

int sum[MAXN];
int T[MAXC];

inline void add(reg int u){
	++sum[++T[c[u]]];
}

int ans[MAXM];

inline void dfs2(reg int u,reg int father,reg bool f){
	for(reg int i=head[u];i;i=Next[i]){
		reg int v=to[i];
		if(v!=father&&v!=son[u])
			dfs2(v,u,false);
	}
	if(son[u])
		dfs2(son[u],u,true);
	add(u);
	for(reg int i=head[u];i;i=Next[i]){
		reg int v=to[i];
		if(v!=father&&v!=son[u])
			for(reg int j=dfn[v];j<=dfn[v]+siz[v]-1;++j)
				add(rnk[j]);
	}
	for(vector<querys>::iterator it=q[u].begin();it!=q[u].end();++it)
		ans[it->id]=sum[it->k];
	if(!f){
		for(reg int i=1;i<=siz[u];++i)
			sum[i]=0;
		for(reg int i=dfn[u];i<=dfn[u]+siz[u]-1;++i)
			T[c[rnk[i]]]=0;
	}
	return;
}

int main(void){
	n=read(),m=read();
	for(reg int i=1;i<=n;++i)
		c[i]=read();
	for(reg int i=1;i<n;++i){
		static int u,v;
		u=read(),v=read();
		Add_Edge(u,v),Add_Edge(v,u);
	}
	for(reg int i=1;i<=m;++i){
		static int u,k;
		u=read(),k=read();
		q[u].push_back(querys(i,k));
	}
	dfs1(1,0),dfs2(1,0,true);
	for(reg int i=1;i<=m;++i)
		printf("%d\n",ans[i]);
	return 0;
}