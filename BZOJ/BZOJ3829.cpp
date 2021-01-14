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

const int MAXN=5e5+5;

int n;
int c[MAXN];
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
		return val<a.val;
	}
};

ll f[MAXN];
int siz[MAXN];
Node p[MAXN];

inline void dfs(reg int u,reg int father){
	if(u!=1)
		f[u]=c[u];
	for(reg int i=head[u];i;i=Next[i]){
		reg int v=to[i];
		if(v!=father)
			dfs(v,u);
	}
	reg int tot=0;
	for(reg int i=head[u];i;i=Next[i]){
		reg int v=to[i];
		if(v!=father)
			p[++tot]=Node(v,siz[v]-f[v]);
	}
	sort(p+1,p+tot+1);
	for(reg int i=1;i<=tot;++i){
		f[u]=max(f[u],f[p[i].id]+siz[u]+1);
		siz[u]+=siz[p[i].id]+2;
	}
	return;
}

int main(void){
	n=read();
	for(reg int i=1;i<=n;++i)
		c[i]=read();
	for(reg int i=1;i<n;++i){
		static int a,b;
		a=read(),b=read();
		Add_Edge(a,b),Add_Edge(b,a);
	}
	dfs(1,0);
	printf("%lld\n",max(f[1],0ll+siz[1]+c[1]));
	return 0;
}