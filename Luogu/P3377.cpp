#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
typedef unsigned long long ull;
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

const int MAXN=100000+5;

inline void Read(void);
inline void Work(void);

int main(void){
	Read();
	Work();
	return 0;
}

int n,m;
int a[MAXN];

inline void Read(void){
	n=read(),m=read();
	for(reg int i=1;i<=n;++i)
		a[i]=read();
	return;
}

struct LeftistTree{
	int dist[MAXN];
	int val[MAXN],root[MAXN];
	int lson[MAXN],rson[MAXN];
	inline void Init(reg int size,reg int a[]){
		dist[0]=-1;
		for(reg int i=1;i<=size;++i){
			val[i]=a[i];
			root[i]=i;
		}
		return;
	}
	inline void pop(reg int x){
		val[x]=-1;
		root[lson[x]]=lson[x];
		root[rson[x]]=rson[x];
		root[x]=merge(lson[x],rson[x]);
		return;
	}
	inline int merge(int x,int y){
		if(!x||!y)
			return x|y;
		if(val[x]>val[y]||(val[x]==val[y]&&x>y))
			swap(x,y);
		rson[x]=merge(rson[x],y);
		if(dist[lson[x]]<dist[rson[x]])
			swap(lson[x],rson[x]);
		root[lson[x]]=root[rson[x]]=root[x]=x;
		dist[x]=dist[rson[x]]+1;
		return x;
	}
	inline int find(reg int x){
		if(x==root[x])
			return x;
		else
			return root[x]=find(root[x]);
	}
};

LeftistTree T;

inline void Work(void){
	T.Init(n,a);
	while(m--){
		static int opt;
		opt=read();
		if(opt==1){
			static int x,y;
			x=read(),y=read();
			if(T.val[x]==-1||T.val[y]==-1)
				continue;
			reg int rx=T.find(x),ry=T.find(y);
			if(rx!=ry)
				T.root[rx]=T.root[ry]=T.merge(rx,ry);
		}
		else if(opt==2){
			static int x;
			x=read();
			if(T.val[x]==-1)
				puts("-1");
			else
				printf("%d\n",T.val[T.find(x)]),T.pop(T.find(x));
		}
	}
	return;
}
