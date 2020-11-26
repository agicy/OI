#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
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

inline void cMin(reg int &a,reg int b){
	if(a>b)
		a=b;
	return;
}

const int MAXN=3e3+5;
const int MAXM=3*MAXN/2;

int n,m;
int cnt=1,head[MAXN],to[MAXM<<1],w[MAXM<<1],Next[MAXM<<1];
bool del[MAXM<<1];

inline void Add_Edge(reg int u,reg int v){
	Next[++cnt]=head[u];
	to[cnt]=v;
	head[u]=cnt;
	return;
}

namespace UnionFind{
	int fa[MAXN];
	inline void Init(reg int n){
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
		if(ra!=rb)
			fa[rb]=ra;
		return;
	}
	inline bool search(reg int a,reg int b){
		return find(a)==find(b);
	}
}

int tim,dfn[MAXN],low[MAXN];
bool vis[MAXN];
int top,S[MAXN];
int tarjan_cnt,col[MAXN];

inline void tarjan(reg int u,reg int id){
	dfn[u]=low[u]=++tim;
	vis[u]=true;
	S[++top]=u;
	for(reg int i=head[u];i;i=Next[i]){
		if(i==id||del[i])
			continue;
		reg int v=to[i];
		if(!dfn[v]){
			tarjan(v,i^1);
			cMin(low[u],low[v]);
		}
		else if(vis[v])
			cMin(low[u],dfn[v]);
	}
	if(dfn[u]==low[u]){
		reg int v;
		++tarjan_cnt;
		do{
			v=S[top--];
			vis[v]=false;
			col[v]=tarjan_cnt;
		}while(v!=u);
	}
	return;
}

const ull p=131;
ull val[MAXN];

inline void Init(void){
	tim=0,memset(dfn,0,sizeof(dfn));
	tarjan_cnt=0;
	return;
}

int main(void){
	n=read(),m=read();
	UnionFind::Init(n);
	for(reg int i=1;i<=m;++i){
		static int x,y;
		x=read(),y=read();
		Add_Edge(x,y);
		Add_Edge(y,x);
		UnionFind::merge(x,y);
	}
	for(reg int i=2;i<=cnt;i+=2){
		del[i]=del[i^1]=true;
		Init();
		for(reg int j=1;j<=n;++j)
			if(!dfn[j])
				tarjan(j,0);
		for(reg int j=1;j<=n;++j)
			val[j]=val[j]*p+col[j];
		del[i]=del[i^1]=false;
	}
	Init();
	for(reg int i=1;i<=n;++i)
		if(!dfn[i])
			tarjan(i,0);
	reg int cnt1=0,cnt2=0,cnt3=0;
	for(reg int i=1;i<n;++i)
		for(reg int j=i+1;j<=n;++j)
			if(!UnionFind::search(i,j))
				continue;
			else if(col[i]!=col[j])
				++cnt1;
			else if(val[i]!=val[j])
				++cnt2;
			else
				++cnt3;
	printf("%d\n",cnt1+2*cnt2+3*cnt3);
	return 0;
}