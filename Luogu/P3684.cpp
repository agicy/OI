#include<bits/stdc++.h>
using namespace std;
#define reg register

const int MAXN=1000+5;
const int MAXN2=MAXN*MAXN;

int n,q;
bool M[MAXN][MAXN];
int f[MAXN][MAXN];
int g[MAXN][MAXN];

inline bool check(reg int x,reg int y,reg int len){
	len|=1;
	if(x+len/2>n||y+len/2>n)
		return 0;
	return f[x+len/2][y+len/2]>=len;
}

inline void Calc(void){
	for(reg int i=1;i<=n;++i)
		for(reg int j=1;j<=n;++j)
			if(M[i][j])
				f[i][j]=1+min(f[i-1][j-1],min(f[i-1][j],f[i][j-1]));
			else
				f[i][j]=0;
	for(reg int i=1;i<=n;++i)
		for(reg int j=1;j<=n;++j)
			if(!M[i][j])
				g[i][j]=0;
			else{
				reg int l=1,r=n,mid;
				while(l<r){
					mid=l+(r-l+1)/2;
					if(check(i,j,mid))
						l=mid;
					else
						r=mid-1;
				}
				g[i][j]=l;
			}
	return;
}

namespace UnionFind{
	int fa[MAXN2],v[MAXN2],size[MAXN2];
	inline void Init(reg int S){
		for(reg int i=1;i<=S;++i)
			fa[i]=i,size[i]=1;
		return;
	}
	inline int find(reg int x){
		if(x==fa[x])
			return x;
		else
			return find(fa[x]);
	}
	inline void merge(int x,int y,reg int z){
		x=find(x),y=find(y);
		if(x==y)
			return;
		if(size[x]>size[y])
			swap(x,y);
		fa[x]=y,v[x]=z,size[y]+=size[x];
		return;
	}
	struct Node{
		int x,y;
		inline Node(reg int x=0,reg int y=0):x(x),y(y){
			return;
		}
		inline bool operator<(const Node &M)const{
			return g[x][y]>g[M.x][M.y];
		}
	};
	Node p[MAXN2];
	inline int GetID(reg int i,reg int j){
		return (i-1)*n+j;
	}
	inline void build(reg int x,reg int y){
		const int dx[]={-1,0,0,1},dy[]={0,-1,1,0};
		for(reg int i=0;i<4;++i){
			reg int fx=x+dx[i],fy=y+dy[i];
			if(1<=fx&&fx<=n&&1<=fy&&fy<=n&&g[x][y]<=g[fx][fy])
				merge(GetID(fx,fy),GetID(x,y),g[x][y]);
		}
		return;
	}
	inline void Solve(void){
		Init(n*n);
		for(reg int i=1;i<=n;++i)
			for(reg int j=1;j<=n;++j)
				p[GetID(i,j)]=Node(i,j);
		sort(p+1,p+n*n+1);
		for(reg int i=1;i<=n*n;++i)
			build(p[i].x,p[i].y);
		return;
	}
	int path1[MAXN2],path2[MAXN2];
	inline int GetAns(reg int x,reg int y){
		reg int cnt1=0,cnt2=0;
		for(reg int i=x;fa[i]!=i;i=fa[i]){
			path1[++cnt1]=i;
			if(fa[i]==y)
				return v[i];
		}
		for(reg int i=y;fa[i]!=i;i=fa[i]){
			path2[++cnt2]=i;
			if(fa[i]==x)
				return v[i];
		}
		while(path1[cnt1]==path2[cnt2])
			--cnt1,--cnt2;
		return min(v[path1[cnt1]],v[path2[cnt2]]);
	}
}

using namespace UnionFind;

int main(void){
	scanf("%d",&n);
	for(reg int i=1;i<=n;++i){
		static char str[1024];
		scanf("%s",str+1);
		for(reg int j=1;j<=n;++j)
			M[i][j]=(str[j]=='.');
	}
	Calc();
	Solve();
	scanf("%d",&q);
	while(q--){
		static int x1,y1,x2,y2;
		scanf("%d%d%d%d",&x1,&y1,&x2,&y2);
		printf("%d\n",GetAns(GetID(x1,y1),GetID(x2,y2)));
	}
	return 0;
}