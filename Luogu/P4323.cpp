#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef unsigned long long ull;
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++)
static char buf[100000],*p1=buf,*p2=buf;
inline int read(void){
	reg char ch=getchar();
	reg int res=0;
	while(ch<'0'||'9'<ch)ch=getchar();
	while('0'<=ch&&ch<='9')res=10*res+ch-'0',ch=getchar();
	return res;
}

const int MAXN=100000+5;

int n;
bool flag;
int deg[MAXN];

namespace Tree{
	int cnt,head[MAXN],to[MAXN<<1],Next[MAXN<<1];
	inline void Add_Edge(reg int u,reg int v){
		Next[++cnt]=head[u];
		to[cnt]=v;
		head[u]=cnt;
		return;
	}
	inline void Init(void){
		cnt=0;
		memset(head,0,sizeof(head));
		return;
	}
}

using namespace Tree;

const ull base=1331;
ull basep[MAXN];

int fa[MAXN],size[MAXN];
ull f[MAXN],g[MAXN];
vector<ull> son[MAXN];
set<ull> vis;

inline ull DFS1(reg int ID,reg int father){
	size[ID]=1;
	fa[ID]=father;
	son[ID].clear();
	for(reg int i=head[ID];i;i=Next[i])
		if(to[i]!=father){
			son[ID].push_back(DFS1(to[i],ID));
			size[ID]+=size[to[i]];
		}
	if(son[ID].empty())
		return f[ID]=1;
	else{
		reg ull res=0;
		sort(son[ID].begin(),son[ID].end());
		for(reg int i=0,size=son[ID].size();i<size;++i)
			res=res*base+son[ID][i];
		res=res*size[ID];
		return f[ID]=res;
	}
}

vector<ull> sl[MAXN],sr[MAXN];
int ans;

inline void DFS2(reg int ID){
	if(fa[ID]){
		son[ID].push_back(g[ID]);
		sort(son[ID].begin(),son[ID].end());
	}
	reg int S=son[ID].size();
	sl[ID].resize(S);
	sr[ID].resize(S);
	sl[ID][0]=son[ID][0];
	sr[ID][S-1]=son[ID][S-1];
	for(reg int i=1,j=S-2;i<S;++i,--j){
		sl[ID][i]=sl[ID][i-1]*base+son[ID][i];
		sr[ID][j]=sr[ID][j+1]+son[ID][j]*basep[S-j-1];
	}
	for(reg int i=head[ID];i;i=Next[i]){
		int v=to[i];
		if(v!=fa[ID]){
			if(S==1){
				g[v]=1;
				DFS2(v);
				break;
			}
			reg int p=lower_bound(son[ID].begin(),son[ID].end(),f[v])-son[ID].begin();
			g[v]=0;
			if(p+1<S)
				g[v]=sr[ID][p+1];
			if(p-1>=0)
				g[v]+=sl[ID][p-1]*basep[S-p-1];
			g[v]*=n-size[v];
			if(flag&&deg[v]==1&&vis.find(g[v])!=vis.end())
				ans=min(ans,v);
			DFS2(v);
		}
	}
	if(!flag)
		vis.insert(sl[ID][S-1]*n);
	return;
}

inline void GetHash(reg int n){
	basep[0]=1;
	for(reg int i=1;i<=n;++i)
		basep[i]=basep[i-1]*base;
	return;
}

int main(void){
	n=read();
	GetHash(n+1);
	for(reg int i=1;i<n;++i){
		static int u,v;
		u=read(),v=read();
		Add_Edge(u,v);
		Add_Edge(v,u);
	}
	DFS1(1,0);
	DFS2(1);
	++n;
	Init();
	flag=true;
	for(reg int i=1;i<n;++i){
		static int u,v;
		u=read(),v=read();
		Add_Edge(u,v);
		Add_Edge(v,u);
		++deg[u],++deg[v];
	}
	DFS1(1,0);
	if(deg[1]==1&&vis.find(f[to[head[1]]])!=vis.end())
		ans=1;
	else
		ans=n+2,DFS2(1);
	printf("%d\n",ans);
	return 0;
}