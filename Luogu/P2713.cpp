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

const int MAXN=1000000+5;

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
	n=read();
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
			lson[i]=rson[i]=dist[i]=0;
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
		if(val[x]>val[y])
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
	m=read();
	while(m--){
		static char opt;
		do
			opt=getchar();
		while(opt!='M'&&opt!='K');
		if(opt=='M'){
			static int i,j;
			i=read(),j=read();
			if(T.val[i]==-1||T.val[j]==-1)
				continue;
			reg int ri=T.find(i),rj=T.find(j);
			if(ri!=rj)
				T.root[ri]=T.root[rj]=T.merge(ri,rj);
		}
		else if(opt=='K'){
			static int i;
			i=read();
			if(T.val[i]==-1)
				puts("0");
			else{
				reg int ri=T.find(i);
				printf("%d\n",T.val[ri]);
				T.pop(ri);
			}
		}
	}
	return;
}
