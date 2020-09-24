#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;

const int MAXN=50+5;
const int MAXM=50+5;
const int MAXV=MAXN*MAXM;
const int MAXE=MAXN*MAXM;

int n,m;
char M[MAXN][MAXM];
int r[MAXN][MAXM],c[MAXN][MAXM];
int cnt,head[MAXV],to[MAXE],Next[MAXE];

inline void Add_Edge(reg int u,reg int v){
	Next[++cnt]=head[u];
	to[cnt]=v;
	head[u]=cnt;
	return;
}

bool vis[MAXV];
int mat[MAXV];

inline bool dfs(reg int u){
	for(reg int i=head[u];i;i=Next[i]){
		reg int v=to[i];
		if(!vis[v]){
			vis[v]=true;
			if(!mat[v]||dfs(mat[v])){
				mat[v]=u;
				return true;
			}
		}
	}
	return false;
}

int main(void){
	int T;
	scanf("%d",&T);
	reg int Case=0;
	while(T--){
		cnt=0,memset(head,0,sizeof(head));
		scanf("%d%d",&n,&m);
		for(reg int i=1;i<=n;++i)
			scanf("%s",M[i]+1);
		reg int R=0;
		for(reg int i=1;i<=n;++i){
			reg int j=1;
			while(j<=m){
				while(j<=m&&M[i][j]=='#')
					++j;
				if(j<=m)
					++R;
				while(j<=m&&M[i][j]!='#')
					r[i][j++]=R;
			}
		}
		reg int C=0;
		for(reg int i=1;i<=m;++i){
			reg int j=1;
			while(j<=n){
				while(j<=n&&M[j][i]=='#')
					++j;
				if(j<=n)
					++C;
				while(j<=n&&M[j][i]!='#')
					c[j++][i]=C;
			}
		}
		for(reg int i=1;i<=n;++i)
			for(reg int j=1;j<=m;++j)
				if(M[i][j]=='o')
					Add_Edge(r[i][j],c[i][j]);
		reg int ans=0;
		memset(mat,0,sizeof(mat));
		for(reg int i=1;i<=R;++i){
			memset(vis,false,sizeof(vis));
			if(dfs(i))
				++ans;
		}
		printf("Case :%d\n%d\n",++Case,ans);
	}
	return 0;
}