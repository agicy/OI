#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++)
static char buf[100000],*p1=buf,*p2=buf;
inline int read(void){
	reg char ch=getchar();
	reg int res=0;
	while(ch<'0'||'9'<ch)ch=getchar();
	while('0'<=ch&&ch<='9')res=10*res+ch-'0',ch=getchar();
	return res;
}

const int MAXN=200+5;
const int MAXM=3e4+5;

int n,m;
bitset<MAXN> G[MAXN];
bool vis[MAXN];
int mat[MAXN];

inline bool dfs(reg int u){
	for(reg int i=1;i<=n;++i)
		if(G[u][i]&&!vis[i]){
			vis[i]=true;
			if(!mat[i]||dfs(mat[i])){
				mat[i]=u;
				return true;
			}
		}
	return false;
}

int main(void){
	n=read(),m=read();
	for(reg int i=1;i<=m;++i){
		static int a,b;
		a=read(),b=read();
		G[a][b]=true;
	}
	for(reg int k=1;k<=n;++k)
		for(reg int i=1;i<=n;++i)
			if(G[i][k])
				G[i]|=G[k];
	reg int sum=0;
	for(reg int i=1;i<=n;++i){
		memset(vis,false,sizeof(vis));
		if(dfs(i))
			++sum;
	}
	printf("%d\n",n-sum);
	return 0;
}