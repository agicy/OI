#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++)
static char buf[100000],*p1=buf,*p2=buf;
inline int read(void){
	reg char ch=getchar();
	reg int res=0;
	while(!isdigit(ch))ch=getchar();
	while(isdigit(ch))res=10*res+(ch^'0'),ch=getchar();
	return res;
}

const int MAXN=35+5;

int n,m;
bool G[MAXN][MAXN];
bool vis[MAXN];
int ans=MAXN*MAXN;

inline bool Gauss(void){
	reg bool flag=true;
	for(reg int i=1;i<=n;++i){
		reg int Max=i;
		while(Max<=n&&!G[Max][i])
			++Max;
		if(Max>n){
			flag=false;
			continue;
		}
		for(reg int j=1;j<=n+1;++j)
			swap(G[i][j],G[Max][j]);
		for(reg int j=1;j<=n;++j)
			if(i!=j&&G[j][i])
				for(reg int k=i+1;k<=n+1;++k)
					G[j][k]^=G[i][k];
	}
	return flag;
}

inline void dfs(reg int x,reg int sum){
	if(sum>=ans)
		return;
	if(!x){
		ans=sum;
		return;
	}
	if(G[x][x]){
		reg bool val=G[x][n+1];
		for(reg int i=x+1;i<=n;++i)
			if(G[x][i])
				val^=vis[i];
		dfs(x-1,sum+val);
	}
	else{
		dfs(x-1,sum);
		vis[x]=true,dfs(x-1,sum+1),vis[x]=false;
	}
	return;
}

int main(void){
	n=read(),m=read();
	for(reg int i=1;i<=n;++i)
		G[i][i]=G[i][n+1]=true;
	for(reg int i=1;i<=m;++i){
		static int a,b;
		a=read(),b=read();
		G[a][b]=G[b][a]=true;
	}
	reg bool f=Gauss();
	if(f){
		reg int ans=0;
		for(reg int i=1;i<=n;++i)
			ans+=G[i][n+1];
		printf("%d\n",ans);
	}
	else{
		dfs(n,0);
		printf("%d\n",ans);
	}
	return 0;
}