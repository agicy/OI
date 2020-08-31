#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

const int MAXN=100+5;
const int inf=0x3f3f3f3f;

int n,m;
int G[MAXN][MAXN];
int dis[MAXN][MAXN];
int p[MAXN][MAXN];
vector<int> V;

inline void getPath(int a,int b){
	if(!p[a][b])
		return;
	getPath(a,p[a][b]);
	V.push_back(p[a][b]);
	getPath(p[a][b],b);
	return;
}

int main(void){
	int ans=inf;
	scanf("%d%d",&n,&m);
	memset(G,0x3f,sizeof(G));
	for(int i=1;i<=n;++i)
		G[i][i]=0;
	for(int i=1;i<=m;++i){
		static int x,y,z;
		scanf("%d%d%d",&x,&y,&z);
		G[x][y]=G[y][x]=min(G[x][y],z);
	}
	memcpy(dis,G,sizeof(G));
	for(int k=1;k<=n;++k){
		for(int i=1;i<k;++i)
			for(int j=i+1;j<k;++j){
				if(0ll+dis[i][j]+G[j][k]+G[k][i]<ans){
					ans=0ll+dis[i][j]+G[j][k]+G[k][i];
					V.clear();
					V.push_back(i);
					getPath(i,j);
					V.push_back(j);
					V.push_back(k);
				}
			}
		for(int i=1;i<=n;++i)
			for(int j=1;j<=n;++j)
				if(dis[i][k]+dis[k][j]<dis[i][j]){
					dis[i][j]=dis[i][k]+dis[k][j];
					p[i][j]=k;
				}
	}
	if(ans==inf)
		puts("No solution.");
	else
		for(int i=0,size=V.size();i<size;++i)
			printf("%d%c",V[i],i==size-1?'\n':' ');
	return 0;
}