#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
#define getchar()(p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++)
static char buf[100000],*p1=buf,*p2=buf;
inline int read(void){
	reg char ch=getchar();
	reg int res=0;
	while(!isdigit(ch))ch=getchar();
	while(isdigit(ch))res=10*res+(ch^'0'),ch=getchar();
	return res;
}

const int MAXN=1e6+5;
const int mod=1e9+7;

inline int add(reg int a,reg int b){
	a+=b;
	return a>=mod?a-mod:a;
}

int n;
int p[MAXN*2];
int vis[MAXN];
int col[MAXN];
int fa[MAXN],nxt[MAXN];
vector<int> G[MAXN];

inline void Add_Edge(reg int u,reg int v){
	G[u].push_back(v);
	return;
}

inline int find(reg int x){
	if(x==fa[x])
		return x;
	else
		return fa[x]=find(fa[x]);
}

bool V[MAXN];

inline bool dfs(reg int u,reg int color){
	col[u]=color;
	for(int v:G[u])
		if(col[v]==-1&&!dfs(v,color^1))
			return false;
		else if(col[v]==col[u])
			return false;
	return true;
}

int main(void){
	n=read();
	for(reg int i=1;i<=n;++i)
		p[read()]=p[read()]=i;
	for(reg int i=1;i<=n+1;++i)
		fa[i]=i,nxt[i]=i;
	reg int tot=0;
	for(reg int i=1;i<=n*2;++i)
		if(!vis[p[i]])
			vis[p[i]]=++tot;
		else{
			reg int id=vis[p[i]];
			fa[id]=find(id+1);
			for(reg int j=fa[id],tmp;j<=tot;j=tmp){
				Add_Edge(j,id);
				Add_Edge(id,j);
				tmp=find(nxt[j]+1);
				nxt[j]=tot;
			}
		}
	fill(col+1,col+n+2,-1);
	reg int ans=1;
	for(reg int i=1;i<=n;++i)
		if(col[i]==-1){
			if(dfs(i,0))
				ans=add(ans,ans);
			else
				ans=0;
		}
	printf("%d\n",ans);
	return 0;
}