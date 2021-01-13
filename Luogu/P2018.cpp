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

const int MAXN=1e3+5;
const int inf=0x3f3f3f3f;

int n;
int cnt,head[MAXN],to[MAXN<<1],Next[MAXN<<1];

inline void Add_Edge(reg int u,reg int v){
	Next[++cnt]=head[u];
	to[cnt]=v;
	head[u]=cnt;
	return;
}

struct Node{
	int id,val;
	inline Node(reg int id=0,reg int val=0):id(id),val(val){
		return;
	}
	inline bool operator<(const Node& a)const{
		return val>a.val;
	}
};

int f[MAXN];
Node V[MAXN];

inline void dfs1(reg int u){
	for(reg int i=head[u];i;i=Next[i])
		dfs1(to[i]);
	reg int tot=0;
	for(reg int i=head[u];i;i=Next[i])
		V[++tot]=Node(to[i],f[to[i]]);
	sort(V+1,V+tot+1);
	for(reg int i=1;i<=tot;++i)
		f[u]=max(f[u],i+V[i].val);
	return;
}

int g[MAXN];
int pre[MAXN],suf[MAXN];
int res[MAXN];

inline void dfs2(reg int u){
	reg int tot=0;
	for(reg int i=head[u];i;i=Next[i])
		V[++tot]=Node(to[i],f[to[i]]);
	if(u!=1)
		V[++tot]=Node(u,g[u]);
	sort(V+1,V+tot+1);
	pre[0]=suf[tot+1]=0;
	for(reg int i=1;i<=tot;++i)
		pre[i]=max(pre[i-1],i+V[i].val);
	for(reg int i=tot;i>=1;--i)
		suf[i]=max(suf[i+1],i+V[i].val);
	for(reg int i=1;i<=tot;++i)
		if(V[i].id!=u)
			g[V[i].id]=max(pre[i-1],suf[i+1]-1);
	res[u]=pre[tot];
	for(reg int i=head[u];i;i=Next[i])
		dfs2(to[i]);
	return;
}

int S[MAXN];

int main(void){
	n=read();
	for(reg int i=2;i<=n;++i){
		static int f;
		f=read();
		Add_Edge(f,i);
	}
	dfs1(1),dfs2(1);
	reg int ans=inf,tot=0;
	for(reg int i=1;i<=n;++i)
		if(ans>res[i]){
			ans=res[i];
			S[tot=1]=i;
		}
		else if(ans==res[i])
			S[++tot]=i;
	printf("%d\n",ans+1);
	for(reg int i=1;i<=tot;++i)
		printf("%d%c",S[i],i==tot?'\n':' ');
	return 0;
}