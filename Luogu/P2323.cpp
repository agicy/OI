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

inline int max(reg int a,reg int b){
	return a>b?a:b;
}

inline int min(reg int a,reg int b){
	return a<b?a:b;
}

const int MAXN=1e4+5;
const int MAXM=2e4+5;

struct Node{
	int id,c;
	inline Node(reg int id=0,reg int c=0):id(id),c(c){
		return;
	}
	inline bool operator<(const Node& a)const{
		return id<a.id;
	}
};

struct Edge{
	int id,u,v,w;
	inline Edge(reg int id=0,reg int u=0,reg int v=0,reg int w=0):id(id),u(u),v(v),w(w){
		return;
	}
	inline bool operator<(const Edge& a)const{
		return w<a.w;
	}
};

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
		fa[rb]=ra;
	}
	inline bool search(reg int a,reg int b){
		return find(a)==find(b);
	}
}

int n,k,m;
Edge E1[MAXM],E2[MAXM];
Node ans[MAXN];

int main(void){
	n=read(),k=read(),m=read();
	reg int tot1=0,tot2=0;
	for(reg int i=1;i<m;++i){
		static int a,b,c1,c2;
		a=read(),b=read(),c1=read(),c2=read();
		E1[++tot1]=Edge(i,a,b,c1),E2[++tot2]=Edge(i,a,b,c2);
	}
	sort(E1+1,E1+tot1+1),sort(E2+1,E2+tot2+1);
	reg int cnt=0,Max=0;
	UnionFind::Init(n);
	for(reg int i=1;i<=tot1&&cnt<k;++i)
		if(!UnionFind::search(E1[i].u,E1[i].v)){
			Max=max(Max,E1[i].w);
			UnionFind::merge(E1[i].u,E1[i].v);
			ans[++cnt]=Node(E1[i].id,1);
		}
	for(reg int i=1;i<=tot2&&cnt<n-1;++i)
		if(!UnionFind::search(E2[i].u,E2[i].v)){
			Max=max(Max,E2[i].w);
			UnionFind::merge(E2[i].u,E2[i].v);
			ans[++cnt]=Node(E2[i].id,2);
		}
	sort(ans+1,ans+cnt+1);
	printf("%d\n",Max);
	for(reg int i=1;i<=cnt;++i)
		printf("%d %d\n",ans[i].id,ans[i].c);
	return 0;
}