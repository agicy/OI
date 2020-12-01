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

const int MAXN=1e3+5;

struct Node{
	int t,val;
};

Node T[MAXN];

inline void Init(reg int x){
	T[x].t=read(),T[x].val=read();
	if(!T[x].val)
		Init(x<<1),Init(x<<1|1);
	return;
}

int dp[MAXN][MAXN];

inline int dfs(reg int u,reg int t){
	if(dp[u][t]||!t)
		return dp[u][t];
	if(T[u].val)
		return dp[u][t]=min(T[u].val,(t-T[u].t*2)/5);
	int res=0;
	for(reg int i=0;i<=t-2*T[u].t;++i)
		res=max(res,dfs(u<<1,i)+dfs(u<<1|1,t-2*T[u].t-i));
	return dp[u][t]=res;
}

int main(void){
	reg int t=read();
	Init(1);
	printf("%d\n",dfs(1,t-1));
	return 0;
}