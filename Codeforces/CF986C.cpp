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

inline int lowbit(reg int x){
	return x&(-x);
}

const int MAXN=22;
const int MAXM=1<<MAXN;

int n,m,U;
bool vis[2][1<<MAXN];

inline void dfs(reg int S,reg int col){
	if(col&&!vis[1][S]){
		vis[1][S]=true;
		dfs(U^S,0);
	}
	else if(!col&&!vis[0][S]){
		vis[0][S]=true;
		dfs(S,1);
		for(reg int i=S;i;i^=lowbit(i))
			dfs(S^lowbit(i),0);
	}
	return;
}

int main(void){
	n=read(),m=read(),U=(1<<n)-1;
	for(reg int i=0;i<=U;++i)
		vis[0][i]=false,vis[1][i]=true;
	reg int ans=0;
	for(reg int i=0;i<m;++i)
		vis[1][read()]=false;
	for(reg int i=0;i<=U;++i)
		if(!vis[1][i])
			++ans,dfs(i,1);
	printf("%d\n",ans);
	return 0;
}