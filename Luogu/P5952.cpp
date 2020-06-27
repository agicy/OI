#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
#define MOD 1000000007
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++)
static char buf[100000],*p1=buf,*p2=buf;
inline int read(void){
	reg char ch=getchar();
	reg int res=0;
	while(ch<'0'||'9'<ch)ch=getchar();
	while('0'<=ch&&ch<='9')res=10*res+ch-'0',ch=getchar();
	return res;
}

const int MAXNM=500000+5;

int n,m,H;

struct Edge{
	int from,to,len;
	inline Edge(reg int from=0,reg int to=0,reg int len=0):from(from),to(to),len(len){
		return;
	}
	inline bool operator<(const Edge& a)const{
		return len<a.len;
	}
};

inline int GetID(reg int i,reg int j){
	return (i-1)*m+j;
}

namespace UnionFind{
	int fa[MAXNM];
	inline void Init(reg int size){
		for(reg int i=1;i<=size;++i)
			fa[i]=i;
		return;
	}
	inline int find(reg int x){
		if(x==fa[x])
			return x;
		else
			return fa[x]=find(fa[x]);
	}
	inline bool search(reg int a,reg int b){
		return find(a)==find(b);
	}
}

int tot;
Edge E[MAXNM<<1];

int Max[MAXNM],g[MAXNM];

inline int Calc(reg int id,reg int val){
	return ((g[id]+val)%MOD-Max[id]+MOD)%MOD;
}

int main(void){
	n=read(),m=read(),H=read();
	for(reg int i=1;i<=n;++i)
		for(reg int j=1;j<m;++j){
			static int a;
			a=read();
			E[++tot]=Edge(GetID(i,j),GetID(i,j+1),a);
		}
	for(reg int i=1;i<n;++i)
		for(reg int j=1;j<=m;++j){
			static int b;
			b=read();
			E[++tot]=Edge(GetID(i,j),GetID(i+1,j),b);
		}
	sort(E+1,E+tot+1);
	using namespace UnionFind;
	Init(n*m);
	for(reg int i=1;i<=n*m;++i){
		g[i]=1;
	}
	for(reg int i=1;i<=tot;++i){
		if(!search(E[i].from,E[i].to)){
			reg int ra=find(E[i].from),rb=find(E[i].to);
			reg int tmp=1ll*Calc(ra,E[i].len)*Calc(rb,E[i].len)%MOD;
			fa[rb]=ra;
			g[ra]=tmp;
			Max[ra]=E[i].len;
		}
	}
	printf("%d\n",Calc(find(1),H));
	return 0;
}