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

const int MAXN=1000+5;

inline void Read(void);
inline void Work(void);

int main(void){
	Read();
	Work();
	return 0;
}

struct Node{
	int x,y;
	inline void Read(void){
		x=read(),y=read();
		return;
	}
};

int n,K;
Node a[MAXN];

inline void Read(void){
	n=read(),K=read();
	for(reg int i=1;i<=n;++i)
		a[i].Read();
	return;
}

struct Edge{
	int f,t;
	double val;
	inline Edge(reg int f=0,reg int t=0,reg double val=0):f(f),t(t),val(val){
		return;
	}
	inline bool operator<(const Edge& a)const{
		return val<a.val;
	}
};

struct UnionFind{
	int ID[MAXN];
	inline void Init(reg int size){
		for(reg int i=1;i<=size;++i)
			ID[i]=i;
		return;
	}
	inline int find(reg int x){
		if(x==ID[x])
			return x;
		else
			return ID[x]=find(ID[x]);
	}
	inline void merge(reg int a,reg int b){
		reg int ra=find(a),rb=find(b);
		if(ra!=rb)
			ID[rb]=ra;
		return;
	}
	inline bool search(reg int a,reg int b){
		return find(a)==find(b);
	}
};

int m;
Edge E[MAXN*MAXN/2];
UnionFind U;

inline double GetDis(const Node& a,const Node& b){
	return sqrt((a.x-b.x)*(a.x-b.x)+(a.y-b.y)*(a.y-b.y));
}

inline void Work(void){
	for(reg int i=1;i<=n;++i)
		for(reg int j=1;j<i;++j)
			E[++m]=Edge(j,i,GetDis(a[j],a[i]));
	sort(E+1,E+m+1);
	U.Init(n);
	reg int cnt=0;
	for(reg int i=1;i<=m;++i)
		if(!U.search(E[i].f,E[i].t)){
			if(cnt==n-K){
				printf("%.2f\n",E[i].val);
				break;
			}
			else{
				++cnt;
				U.merge(E[i].f,E[i].t);
			}
		}
	return;
}
