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
const int MAXM=200+5;

int n,m,k;
int mat[MAXM];
bool M[MAXN][MAXM],vis[MAXM];

inline bool dfs(reg int u){
	for(reg int i=1;i<=m;++i){
		if(M[u][i]||vis[i])
			continue;
		vis[i]=true;
		if(!mat[i]||dfs(mat[i])){
			mat[i]=u;
			return true;
		}
	}
	return false;
}

int main(void){
	n=read(),m=read(),k=read();
	for(reg int i=1;i<=k;++i){
		static int x,y;
		x=read(),y=read();
		M[x][y]=true;
	}
	reg int ans=0;
	for(reg int i=1;i<=n;++i){
		memset(vis,false,sizeof(vis));
		if(dfs(i))
			++ans;
	}
	printf("%d\n",ans);
	return 0;
}