#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;

const int MAXN=1000000+5;
const int MAXLOG2N=20+1;
const int MOD=998244853;

inline void Read(void);
inline void Work(void);

int main(void){
	Read();
	Work();
	return 0;
}

int n,m;
char str[MAXN];
int cnt,head[MAXN],to[MAXN<<1],Next[MAXN<<1];

inline void Add_Edge(reg int u,reg int v){
	Next[++cnt]=head[u];
	to[cnt]=v;
	head[u]=cnt;
	return;
}

inline ll pow(reg ll x,reg ll exp,reg ll mod){
	reg ll res=1;
	while(exp){
		if(exp&1)
			res=res*x%mod;
		x=x*x%mod;
		exp>>=1;
	}
	return res;
}

ll base,inv;
ll basep[MAXN],invp[MAXN];

inline void InitP(void){
	srand(time(NULL));
	basep[0]=invp[0]=1;
	base=(rand()%2000)+1001;
	inv=pow(base,MOD-2,MOD);
	for(reg int i=1;i<=n;++i){
		basep[i]=basep[i-1]*base%MOD;
		invp[i]=invp[i-1]*inv%MOD;
	}
	return;
}

inline void Read(void){
	scanf("%d\n%s",&n,str+1);
	InitP();
	for(reg int i=1;i<n;++i){
		static int u,v;
		scanf("%d%d",&u,&v);
		Add_Edge(u,v);
		Add_Edge(v,u);
	}
	return;
}

int son[MAXN],fa[MAXN][MAXLOG2N];
int tim,dfn[MAXN],dfn_dep[MAXN],rnk[MAXN];
int dep[MAXN],MaxDep[MAXN];
ll Hash[MAXN],revHash[MAXN];

inline void DFS1(reg int ID,reg int father){
	dfn[ID]=++tim;
	fa[ID][0]=father;
	dep[ID]=dep[father]+1;
	dfn_dep[dfn[ID]]=MaxDep[ID]=dep[ID];
	rnk[tim]=ID;
	Hash[ID]=(Hash[father]*base%MOD+str[ID])%MOD;
	revHash[ID]=(revHash[father]+basep[dep[father]]%MOD*str[ID])%MOD;
	for(reg int i=1;i<MAXLOG2N;++i)
		fa[ID][i]=fa[fa[ID][i-1]][i-1];
	for(reg int i=head[ID];i;i=Next[i])
		if(to[i]!=father){
			DFS1(to[i],ID);
			rnk[++tim]=ID;
			dfn_dep[tim]=dep[ID];
			if(MaxDep[to[i]]>MaxDep[ID])
				MaxDep[ID]=MaxDep[to[i]],son[ID]=to[i];
		}
	return;
}

int top[MAXN];
vector<int> up[MAXN],down[MAXN];

inline void DFS2(reg int ID,reg int father,reg int topf){
	top[ID]=topf;
	if(ID==topf){
		int x=ID;
		for(reg int i=0;i<=MaxDep[ID]-dep[ID];++i)
			up[ID].push_back(x),x=fa[x][0];
		x=ID;
		for(reg int i=0;i<=MaxDep[ID]-dep[ID];++i)
			down[ID].push_back(x),x=son[x];
	}
	if(son[ID])
		DFS2(son[ID],ID,topf);
	for(reg int i=head[ID];i;i=Next[i])
		if(to[i]!=father&&to[i]!=son[ID])
			DFS2(to[i],ID,to[i]);
	return;
}

int f[MAXN][MAXLOG2N],Log[MAXN];

inline int LCA(reg int u,reg int v){
	int l=dfn[u],r=dfn[v];
	if(l>r)
		swap(l,r);
	reg int k=Log[r-l+1];
	return (dfn_dep[f[l][k]]<=dfn_dep[f[r-(1<<k)+1][k]])?rnk[f[l][k]]:rnk[f[r-(1<<k)+1][k]];
}

inline int GetHash(reg int u,reg int v,reg int lca,reg int flca){
	reg int dv=dep[v]-dep[lca];
	reg ll h1=(revHash[u]-revHash[flca]+MOD)%MOD*invp[dep[flca]]%MOD;
	reg ll h2=(Hash[v]-Hash[lca]*basep[dv]%MOD+MOD)%MOD;
	reg ll H=(h1*basep[dv]%MOD+h2)%MOD;
	return H;
}

inline bool get(reg int u,reg int v,reg int k){
	return k<=dep[u]-dep[LCA(u,v)];
}

inline int querykth(int u,int k){
	if(!k)
		return u;
	u=fa[u][Log[k]];
	k-=(1<<Log[k]);
	k-=dep[u]-dep[top[u]],u=top[u];
	return((k>=0)?up[u][k]:down[u][-k]);
}

inline int path(reg int u,reg int v,reg int k){
	reg int lca=LCA(u,v),d=dep[u]+dep[v]-(dep[lca]<<1)+1;
	if(k<=dep[u]-dep[lca])
		return querykth(u,k-1);
	else
		return querykth(v,d-k);
}

inline int Query(reg int a,reg int b,reg int c,reg int d){
	if(str[a]!=str[c])
		return 0;
	reg int lca1=LCA(a,b),flca1=fa[lca1][0],lca2=LCA(c,d),flca2=fa[lca2][0];
	int d1=dep[a]+dep[b]-(dep[lca1]<<1)+1,d2=dep[c]+dep[d]-(dep[lca2]<<1)+1;
	reg int l=1,r=min(d1,d2),mid;
	while(l<r){
		mid=(l+r+1)>>1;
		reg int x1=get(a,b,mid),x2=get(c,d,mid);
		reg int v1=path(a,b,mid),v2=path(c,d,mid);
		if(GetHash(a,v1,(x1?v1:lca1),(x1?fa[v1][0]:flca1))==GetHash(c,v2,(x2?v2:lca2),(x2?fa[v2][0]:flca2)))
			l=mid;
		else
			r=mid-1;
	}
	return l;
}

inline void InitF(void){
	Log[0]=-1;
	for(reg int i=1;i<=tim;++i){
		Log[i]=Log[i>>1]+1;
		f[i][0]=i;
	}
	for(reg int j=1;(1<<j)<=tim;++j)
		for(reg int i=1;i<=tim-(1<<j)+1;++i)
			f[i][j]=(dfn_dep[f[i][j-1]]<=dfn_dep[f[i+(1<<(j-1))][j-1]])?f[i][j-1]:f[i+(1<<(j-1))][j-1];
	return;
}

inline void Work(void){
	scanf("%d",&m);
	DFS1(1,0);
	DFS2(1,0,1);
	InitF();
	for(reg int i=1;i<=m;++i){
		static int a,b,c,d;
		scanf("%d%d%d%d",&a,&b,&c,&d);
		printf("%d\n",Query(a,b,c,d));
	}
	return;
}