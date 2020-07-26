#include<bits/stdc++.h>
using namespace std;
#define reg register
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

const int MAXN=250+5;
const int MAXA=1000000+5;

struct Edge{
	int u,v;
	pair<int,int> color;
	inline bool operator<(const Edge& a)const{
		return color<a.color;
	}
};

namespace UnionFind{
	int fa[MAXN*MAXN],size[MAXN*MAXN];
	inline void Init(reg int S){
		for(reg int i=1;i<=S;++i)
			fa[i]=i,size[i]=1;
		return;
	}
	inline int find(reg int x){
		if(x==fa[x])
			return x;
		else
			return fa[x]=find(fa[x]);
	}
	inline void merge(reg int a,reg int b){
		int ra=find(a),rb=find(b);
		if(ra!=rb){
			if(size[ra]<size[rb])
				swap(ra,rb);
			fa[rb]=ra;
			size[ra]+=size[rb];
		}
		return;
	}
}

using namespace UnionFind;

int tot;
Edge E[(MAXN*MAXN)<<1];

inline void Add_Edge(reg int u,reg int v,pair<int,int> color){
	if(color.first>color.second)
		swap(color.first,color.second);
	E[++tot].u=find(u);
	E[tot].v=find(v);
	E[tot].color=color;
	return;
}

int n;
int M[MAXN][MAXN];
int temp[MAXN*MAXN];
vector<int> V[MAXA];

inline int GetID(reg int i,reg int j){
	return (i-1)*n+j;
}

inline void back(reg int x){
	for(reg int i=0,S=V[x].size();i<S;++i){
		reg int u=V[x][i];
		fa[u]=u;
		size[u]=temp[u];
	}
	return;
}

int main(void){
	n=read();
	for(reg int i=1;i<=n;++i)
		for(reg int j=1;j<=n;++j)
			M[i][j]=read();
	Init(n*n);
	int ans1=0,ans2=0;
	for(reg int i=1;i<=n;++i)
		for(reg int j=1;j<=n;++j){
			if(i!=n&&M[i][j]==M[i+1][j])
				merge(GetID(i,j),GetID(i+1,j));
			if(j!=n&& M[i][j+1] == M[i][j])
				merge(GetID(i,j),GetID(i,j+1));
			ans1=max(ans1,size[find(GetID(i,j))]);
		}
	for(reg int i=1;i<=n;++i)
		for(reg int j=1;j<=n;++j)
			if(find(GetID(i,j))==GetID(i,j))
				V[M[i][j]].push_back(GetID(i,j));
	for(reg int i=1;i<=n;++i)
		for(reg int j=1;j<=n;++j){
			if(i!=n&& M[i][j]!=M[i+1][j])
				Add_Edge(GetID(i,j),GetID(i+1,j),make_pair(M[i][j],M[i+1][j]));
			if(j!=n&&M[i][j]!=M[i][j+1])
				Add_Edge(GetID(i,j),GetID(i,j+1),make_pair(M[i][j],M[i][j+1]));
		}
	sort(E+1,E+tot+1);
	memcpy(temp,size,sizeof(size));
	for(reg int i=1,r;i<=tot;i=r){
		static pair<int,int> color;
		r=i;
		color=E[i].color;
		while(E[r].color==color){
			merge(E[r].u,E[r].v);
			ans2=max(ans2,size[find(E[r].u)]);
			++r;
		}
		back(color.first),back(color.second);
	}
	printf("%d\n%d\n",ans1,ans2);
	return 0;
}