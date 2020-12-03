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

const int MAXLOG10N=10+5;
const int MAXS=10+5;

int tot,a[MAXLOG10N];
ll dp[MAXLOG10N][MAXS];

inline ll dfs(reg int pos,reg int pre,reg bool leq,reg bool lim){
	if(pos>tot)
		return 1;
	if(!lim&&~dp[pos][pre])
		return dp[pos][pre];
	reg ll res=0;
	reg int Max=lim?a[tot-pos+1]:9;
	for(reg int i=0;i<=Max;++i){
		if(abs(i-pre)<2)
			continue;
		if(leq&&!i)
			res+=dfs(pos+1,-2,true,lim&&i==Max);
		else
			res+=dfs(pos+1,i,false,lim&&i==Max);
	}
	if(!lim&&!leq)
		dp[pos][pre]=res;
	return res;
}

inline ll getVal(reg int x){
	tot=0;
	while(x){
		a[++tot]=x%10;
		x/=10;
	}
	memset(dp,-1,sizeof(dp));
	return dfs(1,-2,1,1);
}

int main(void){
	int a,b;
	a=read(),b=read();
	printf("%lld\n",getVal(b)-getVal(a-1));
	return 0;
}