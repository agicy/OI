#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
#define getchar()(p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++)
static char buf[100000],*p1=buf,*p2=buf;
inline int read(void){
	reg bool f=false;
	reg char ch=getchar();
	reg int res=0;
	while(!isdigit(ch))f|=(ch=='-'),ch=getchar();
	while(isdigit(ch))res=10*res+(ch^'0'),ch=getchar();
	return f?-res:res;
}

const int MAXN=400+5;

int p;

inline int add(reg int a,reg int b){
	a+=b;
	return a>=p?a-p:a;
}

inline int sub(reg int a,reg int b){
	a-=b;
	return a<0?a+p:a;
}

int n;
int u[MAXN],v[MAXN];
int deg[MAXN];

namespace Subtask2{
	const int MAXN=20;
	namespace UnionFind{
		int fa[MAXN],siz[MAXN];
		inline void Init(reg int n){
			for(reg int i=0;i<n;++i)
				fa[i]=i,siz[i]=1;
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
			if(ra!=rb){
				fa[rb]=ra;
				siz[ra]+=siz[rb];
			}
			return;
		}
		inline bool search(reg int a,reg int b){
			return find(a)==find(b);
		}
	}
	bool vis[1<<MAXN];
	int a[MAXN],b[MAXN];
	map<int,int> lg;
	int f[1<<MAXN][MAXN];
	int g[1<<MAXN];
	inline int lowbit(reg int x){
		return x&(-x);
	}
	inline void Solve(void){
		for(reg int i=0;i<n;++i)
			lg[1<<i]=i;
		for(reg int i=1;i<n;++i)
			a[i]=u[i]-1,b[i]=v[i]-1;
		for(reg int S=1;S<(1<<n);++S){
			if(__builtin_popcount(S)==n||__builtin_popcount(S)==n-1)
				vis[S]=true;
			else{
				UnionFind::Init(n);
				for(reg int i=1;i<n;++i)
					if(!((S>>a[i])&1)&&!((S>>b[i])&1))
						UnionFind::merge(a[i],b[i]);
				reg int id=lg[lowbit(~S)];
				if(UnionFind::siz[UnionFind::find(id)]==n-__builtin_popcount(S))
					vis[S]=true;
			}
		}
		g[0]=1;
		for(reg int i=1;i<=n;++i){
			for(reg int S=1;S<(1<<n);++S){
				fill(f[S],f[S]+n,0);
				for(reg int x=S;x;x^=lowbit(x))
					if(g[S^lowbit(x)]){
						reg int id=lg[lowbit(x)];
						f[S][id]=add(f[S][id],g[S^lowbit(x)]);
					}
			}
			for(reg int S=1;S<(1<<n);++S)
				for(reg int x=S;x;x^=lowbit(x)){
					reg int id=lg[lowbit(x)];
					for(reg int j=0;j<id;++j)
						if(f[S^lowbit(x)][j])
							f[S][id]=add(f[S][id],f[S^lowbit(x)][j]);
				}
			for(reg int S=0;S<(1<<n);++S){
				g[S]=0;
				if(vis[S])
					for(reg int j=0;j<n;++j)
						g[S]=add(g[S],f[S][j]);
			}
			printf("%d\n",g[(1<<n)-1]);
		}
		return;
	}
}

namespace Subtask3{
	int f[MAXN][MAXN];
	inline void Solve(void){
		f[1][1]=f[2][1]=1,f[2][2]=2;
		for(reg int i=3;i<=n;++i)
			for(reg int j=1;j<=i;++j)
				f[i][j]=sub(2ll*add(f[i-1][j],f[i-1][j-1])%p,add(f[i-2][j],f[i-2][j-1]));
		for(reg int i=1;i<=n;++i)
			printf("%d\n",f[n][i]);
		return;
	}
}

int main(void){
	//printf("%.1lf MiB\n",sizeof(Subtask2::f)/1048576.0);
	n=read(),p=read();
	for(reg int i=1;i<n;++i){
		u[i]=read(),v[i]=read();
		++deg[u[i]],++deg[v[i]];
	}
	reg bool subtask3flag=true;
	for(reg int i=1;i<=n;++i)
		if(deg[i]>2){
			subtask3flag=false;
			break;
		}
	if(n<=20)
		//puts("S2"),
		Subtask2::Solve();
	else if(subtask3flag)
		//puts("S3"),
		Subtask3::Solve();
	return 0;
}