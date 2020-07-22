#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
typedef unsigned long long ull;
#define INF 1e18
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

const int MAXN=100+5;
const int MAXM=2000+5;

inline void Read(void);
inline void Work(void);

int main(void){
	Read();
	Work();
	return 0;
}

struct Edge{
	int u,v,c;
	inline void Read(void){
		u=read(),v=read(),c=read();
		return;
	}
};

int n,m;
Edge E[MAXM];

inline void Read(void){
	n=read(),m=read();
	if(n==1)
		puts("0.0000"),exit(0);
	for(reg int i=1;i<=m;++i)
		E[i].Read();
	return;
}

struct UnionFind{
	int fa[MAXN],rank[MAXN];
	inline void Init(reg int n){
		for(reg int i=1;i<=n;++i)
			fa[i]=i,rank[i]=1;
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
		if(ra==rb)
			return;
		if(rank[ra]<rank[rb])
			fa[ra]=rb;
		else if(rank[ra]==rank[rb]){
			++rank[ra];
			fa[rb]=ra;
		}
		else
			fa[rb]=ra;
		return;
	}
	inline bool search(reg int a,reg int b){
		return find(a)==find(b);
	}
};

double ave;

inline bool cmp(const Edge& a,const Edge& b){
	return fabs(a.c-ave)<fabs(b.c-ave);
}

UnionFind S;
int len[MAXN];

inline double Kruskal(void){
	S.Init(n);
	sort(E+1,E+m+1,cmp);
	reg int cnt=0,sum=0;
	for(reg int i=1;i<=m&&cnt<n-1;++i)
		if(!S.search(E[i].u,E[i].v)){
			sum+=E[i].c;
			len[++cnt]=E[i].c;
			S.merge(E[i].u,E[i].v);
		}
	reg double avg=(double)sum/(n-1),e=0;
	for(reg int i=1;i<=cnt;++i)
		e+=(len[i]-avg)*(len[i]-avg);
	e=sqrt(e/(n-1));
	return e;
}

inline void Work(void){
	reg double ans=INF;
	for(ave=1;ave<=100;ave+=0.4)
		ans=min((double)ans,Kruskal());
	printf("%.4lf\n",ans);
	return;
}
