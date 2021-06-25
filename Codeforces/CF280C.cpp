#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++)
static char buf[1<<21],*p1=buf,*p2=buf;
inline int read(void){
	reg char ch=getchar();
	reg int res=0;
	while(!isdigit(ch)) ch=getchar();
	while(isdigit(ch)) res=10*res+(ch^'0'),ch=getchar();
	return res;
}

const int MAXN=1e5+5;

int n;
vector<int> G[MAXN];
double ans;

inline void dfs(reg int u,reg int father,reg int dep){
	ans+=1.0/dep;
	for(int v:G[u])
		if(v!=father)
			dfs(v,u,dep+1);
	return;
}

int main(void){
	n=read();
	for(reg int i=1;i<n;++i){
		static int a,b;
		a=read(),b=read();
		G[a].push_back(b),G[b].push_back(a);
	}
	dfs(1,0,1);
	printf("%.20lf\n",ans);
	return 0;
}