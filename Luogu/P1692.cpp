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

const int MAXN=100+5;

int n,m;
bool G[MAXN][MAXN];
int p[MAXN];
int ans,Ans[MAXN];

inline void dfs(reg int dep,reg int sum){
	if(dep==n+1){
		if(sum>ans){
			ans=sum;
			for(reg int i=1;i<=n;++i)
				Ans[i]=p[i];
		}
		return;
	}
	if(sum+n-dep+1<=ans)
		return;
	reg bool flag=false;
	for(reg int i=1;i<dep;++i)
		if(p[i]&&G[dep][i]){
			flag=true;
			break;
		}
	if(!flag){
		p[dep]=true;
		dfs(dep+1,sum+1);
		p[dep]=false;
	}
	dfs(dep+1,sum);
	return;
}

int main(void){
	n=read(),m=read();
	for(reg int i=1;i<=m;++i){
		static int x,y;
		x=read(),y=read();
		G[x][y]=G[y][x]=true;
	}
	dfs(1,0);
	printf("%d\n",ans);
	for(reg int i=1;i<=n;++i)
		printf("%d%c",Ans[i],i==n?'\n':' ');
	return 0;
}