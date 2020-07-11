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

const int MAXN=100+5;

inline void Read(void);
inline void Work(void);

int main(void){
	Read();
	Work();
	return 0;
}

int n,K,r;

const int dx[]={-1,0,0,1};
const int dy[]={0,-1,1,0};

bool R[MAXN][MAXN][4];

inline void Read(void){
	n=read(),K=read(),r=read();
	for(reg int i=1;i<=r;++i){
		static int x1,y1,x2,y2;
		x1=read(),y1=read(),x2=read(),y2=read();
		for(reg int j=0;j<4;++j)
			if(x1+dx[j]==x2&&y1+dy[j]==y2)
				R[x1][y1][j]=R[x2][y2][4-j-1]=true;
	}
	return;
}

struct UnionFind{
	int ID[MAXN*MAXN],size[MAXN*MAXN];
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
		if(ra!=rb){
			ID[rb]=ra;
			size[ra]+=size[rb];
		}
		return;
	}
	inline bool search(reg int a,reg int b){
		return find(a)==find(b);
	}
};

UnionFind U;

inline int GetID(reg int i,reg int j){
	return (i-1)*n+j;
}

bool vis[MAXN*MAXN];

inline void Work(void){
	U.Init(n*n);
	for(reg int i=1;i<=K;++i){
		static int x,y;
		x=read(),y=read();
		++U.size[GetID(x,y)];
	}
	for(reg int i=1;i<=n;++i)
		for(reg int j=1;j<=n;++j)
			for(reg int k=0;k<4;++k){
				reg int fx=i+dx[k],fy=j+dy[k];
				if(1<=fx&&fx<=n&&1<=fy&&fy<=n)
					if(!R[i][j][k])
						U.merge(GetID(i,j),GetID(fx,fy));
			}
	reg int sum=0,ans=0;
	for(reg int i=1;i<=n*n;++i)
		if(vis[U.find(i)])
			continue;
		else{
			reg int fa=U.find(i);
			vis[fa]=true;
			ans+=sum*U.size[fa];
			sum+=U.size[fa];
		}
	printf("%d\n",ans);
	return;
}
