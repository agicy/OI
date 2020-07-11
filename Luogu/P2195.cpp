#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
typedef unsigned long long ull;
#define INF 0X3F3F3F3F
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

const int MAXN=300000+5;

inline void Read(void);
inline void Work(void);

int main(void){
	Read();
	Work();
	return 0;
}

struct UnionFind{
	int ID[MAXN];
	inline void Init(reg int n){
		for(reg int i=1;i<=n;++i)
			ID[i]=i;//,dis[i]=0;
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
		if(ra!=rb){
			ID[rb]=ra;/*
			int temp=((dis[ra]+1)>>1)+((dis[rb]+1)>>1)+1;
			temp=max(temp,max(dis[ra],dis[rb]));
			dis[ra]=temp;*/
		}
		return;
	}
	inline bool search(reg int a,reg int b){
		return find(a)==find(b);
	}
};

int n,m,q;
UnionFind U;

inline void Read(void){
	n=read(),m=read(),q=read();
	U.Init(n);
	for(reg int i=1;i<=m;++i){
		static int x,y;
		x=read(),y=read();
		Add_Edge(x,y);
		Add_Edge(y,x);
		U.merge(x,y);
	}
	return;
}

inline void Work(void){
	for(reg int i=1;i<=n;++i)
	while(q--){
		static int opt;
		opt=read();
		if(opt==1){
			static int x;
			x=read();
			printf("%d\n",U.dis[U.find(x)]);
		}
		else if(opt==2){
			static int x,y;
			x=read(),y=read();
			U.merge(x,y);
		}
	}
	return;
}
