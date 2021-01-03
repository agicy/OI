#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++)
static char buf[100000],*p1=buf,*p2=buf;
inline int read(void){
	reg bool f=false;
	reg char ch=getchar();
	reg int res=0;
	while(!isdigit(ch))f|=(ch=='-'),ch=getchar();
	while(isdigit(ch))res=10*res+(ch^'0'),ch=getchar();
	return f?-res:res;
}

const int MAXN=500+5;
const ll inf=1e18;

int n,m;
ll G[MAXN][MAXN];
int mat[MAXN];
ll slack[MAXN],ex[MAXN],ey[MAXN];
int pre[MAXN];
bool visx[MAXN],visy[MAXN];

inline void bfs(reg int u){
	memset(pre,0,sizeof(pre));
	for(reg int i=1;i<=n;++i)
		slack[i]=inf;
	reg int x,y=0;
	mat[y]=u;
	while(true){
		x=mat[y],visy[y]=true;
		reg int tmp=0;
		reg ll delta=inf;
		for(reg int i=1;i<=n;++i){
			if(visy[i])
				continue;
			if(slack[i]>ex[x]+ey[i]-G[x][i]){
				slack[i]=ex[x]+ey[i]-G[x][i];
				pre[i]=y;
			}
			if(slack[i]<delta){
				delta=slack[i];
				tmp=i;
			}
		}
		for(reg int i=0;i<=n;++i)
			if(visy[i])
				ex[mat[i]]-=delta,ey[i]+=delta;
			else
				slack[i]-=delta;
		y=tmp;
		if(!mat[y])
			break;
	}
	while(y){
		mat[y]=mat[pre[y]];
		y=pre[y];
	}
	return;
}

inline ll KM(void){
	memset(mat,0,sizeof(mat));
	memset(ex,0,sizeof(ex));
	memset(ey,0,sizeof(ey));
	for(reg int i=1;i<=n;++i){
		memset(visy,false,sizeof(visy));
		bfs(i);
	}
	reg ll res=0;
	for(reg int i=1;i<=n;++i)
		if(mat[i])
			res+=G[mat[i]][i];
	return res;
}

int main(void){
	n=read(),m=read();
	for(reg int i=1;i<=n;++i)
		for(reg int j=1;j<=n;++j)
			G[i][j]=-inf;
	for(reg int i=1;i<=m;++i){
		static int y,c,h;
		y=read(),c=read(),h=read();
		G[y][c]=h;
	}
	printf("%lld\n",KM());
	for(reg int i=1;i<=n;++i)
		printf("%d%c",mat[i],i==n?'\n':' ');
	return 0;
}