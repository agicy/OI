#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;

const int MAXN=1e3+5;
const int MAXM=1e3+5;

int n,m;
int id[MAXN][MAXM];
int fa[MAXN*MAXM];

inline int find(reg int x){
	if(x==fa[x])
		return x;
	else
		return fa[x]=find(fa[x]);
}

inline void merge(reg int a,reg int b){
	reg int ra=find(a),rb=find(b);
	if(ra!=rb)
		fa[rb]=ra;
	return;
}

inline bool search(reg int a,reg int b){
	return find(a)==find(b);
}

int main(void){
	scanf("%d%d",&n,&m);
	reg int cnt=0;
	for(reg int i=1;i<=n;++i)
		for(reg int j=1;j<=m;++j)
			id[i][j]=++cnt,fa[id[i][j]]=id[i][j];
	int x1,y1,x2,y2;
	while(scanf("%d%d%d%d",&x1,&y1,&x2,&y2)!=EOF)
		merge(id[x1][y1],id[x2][y2]);
	reg int ans=0;
	for(reg int i=1;i<n;++i)
		for(reg int j=1;j<=m;++j)
			if(!search(id[i][j],id[i+1][j])){
				ans+=1;
				merge(id[i][j],id[i+1][j]);
			}
	for(reg int i=1;i<=n;++i)
		for(reg int j=1;j<m;++j)
			if(!search(id[i][j],id[i][j+1])){
				ans+=2;
				merge(id[i][j],id[i][j+1]);
			}
	printf("%d\n",ans);
	return 0;
}