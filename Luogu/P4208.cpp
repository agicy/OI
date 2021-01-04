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

const int MAXN=100+5;
const int MAXM=1e3+5;
const int p=31011;

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
			return find(fa[x]);
	}
}

struct Edge{
	int u,v,len;
	inline Edge(reg int u=0,reg int v=0,reg int len=0):u(u),v(v),len(len){
		return;
	}
	inline bool operator<(const Edge& a)const{
		return len<a.len;
	}
};

int n,m;
Edge E[MAXM];

struct T{
	int l,r,val;
	inline T(reg int l=0,reg int r=0,reg int val=0):l(l),r(r),val(val){
		return;
	}
};

T t[MAXM];
int sum;

inline void dfs(reg int ptr,reg int dep,reg int k){
	if(dep==t[ptr].r+1){
		if(k==t[ptr].val)
			++sum;
		return;
	}
	reg int x=UnionFind::find(E[dep].u),y=UnionFind::find(E[dep].v);
	if(x!=y){
		UnionFind::fa[x]=y;
		dfs(ptr,dep+1,k+1);
		UnionFind::fa[x]=x,UnionFind::fa[y]=y;
	}
	dfs(ptr,dep+1,k);
	return;
}

int main(void){
	n=read(),m=read();
	for(reg int i=1;i<=m;++i){
		static int a,b,c;
		a=read(),b=read(),c=read();
		E[i]=Edge(a,b,c);
	}
	sort(E+1,E+m+1);
	UnionFind::Init(n);
	reg int tot=0;
	reg int cnt=0;
	for(reg int i=1;i<=m;++i){
		if(E[i-1].len!=E[i].len){
			++cnt;
			t[cnt-1].r=i-1,t[cnt].l=i;
		}
		reg int x=UnionFind::find(E[i].u),y=UnionFind::find(E[i].v);
		if(x!=y){
			++tot,++t[cnt].val;
			UnionFind::fa[x]=y;
		}
	}
	if(tot!=n-1){
		puts("0");
	}
	else{
		t[cnt].r=m;
		reg int ans=1;
		UnionFind::Init(n);
		for(reg int i=1;i<=cnt;++i){
			sum=0;
			dfs(i,t[i].l,0);
			ans=ans*sum%p;
			for(reg int j=t[i].l;j<=t[i].r;++j){
				reg int x=UnionFind::find(E[j].u),y=UnionFind::find(E[j].v);
				if(x!=y)
					UnionFind::fa[x]=y;
			}
		}
		printf("%d\n",ans);
	}
	return 0;
}