#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
#define getchar()(p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++)
static char buf[100000],*p1=buf,*p2=buf;
inline int read(void){
	reg char ch=getchar();
	reg int res=0;
	while(!isdigit(ch))ch=getchar();
	while(isdigit(ch))res=10*res+(ch^'0'),ch=getchar();
	return res;
}

inline int max(reg int a,reg int b){
	return a>b?a:b;
}

const int MAXN=1e5+5;

int n,k;
int a[MAXN];
vector<int> G[MAXN];
int ans;

inline int dfs(reg int u,reg int depth){
	reg int res=depth;
	for(int v:G[u])
		res=max(res,dfs(v,depth+1));
	if(a[u]!=1&&res-depth==k-1){
		++ans;
		return 0;
	}
	else
		return res;
}

int main(void){
	n=read(),k=read();
	for(reg int i=1;i<=n;++i)
		a[i]=read();
	if(a[1]!=1)
		a[1]=1,++ans;
	for(int i=2;i<=n;++i)
		G[a[i]].push_back(i);
	dfs(1,0);
	printf("%d\n",ans);
	return 0;
}