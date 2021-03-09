#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
#define getchar()(p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++)
static char buf[100000],*p1=buf,*p2=buf;
inline int read(void){
	reg bool f=false;
	reg char ch=getchar();
	reg int res=0;
	while(!isdigit(ch))f|=(ch=='-'),ch=getchar();
	while(isdigit(ch))res=10*res+(ch^'0'),ch=getchar();
	return f?-res:res;
}

inline void read(reg char *s){
	*s=getchar();
	while(!isalpha(*s))*s=getchar();
	while(isalpha(*s))*(++s)=getchar();
	*s='\0';
	return;
}

inline int min(reg int a,reg int b){
	return a<b?a:b;
}

const int MAXN=5e5+5;
const int MAXM=5e5+5;
const int MAXK=100+5;
const int inf=0x3f3f3f3f;

int n,m,k;
char a[MAXN],b[MAXM];

namespace Subtask1{
	int dp[2][MAXM];
	inline void Solve(void){
		for(reg int i=1;i<=n;++i)
			for(reg int j=1;j<=m;++j)
				if(a[i]==b[j])
					dp[i&1][j]=dp[(i-1)&1][j-1]+1;
				else
					dp[i&1][j]=max(dp[(i-1)&1][j],dp[i&1][j-1]);
		reg int ans=(n+m)-dp[n&1][m]*2;
		printf("%d\n",ans>k?-1:ans);
		return;
	}
}

namespace Subtask2{
	clock_t st;
	inline int dfs(reg int pa,reg int pb,reg int sum,reg int lim){
		if(clock()-st>1.5*CLOCKS_PER_SEC)
			puts("-1"),exit(0);
		if(sum>=lim)
			return inf;
		if(sum>k)
			return inf;
		if(pa==n+1)
			return sum+m-pb+1;
		if(pb==m+1)
			return sum+n-pa+1;
		reg int res=inf,tmp;
		if(a[pa]==b[pb]){
			tmp=dfs(pa+1,pb+1,sum,lim);
			if(tmp>=k)
				tmp=inf;
			res=min(res,tmp);
			tmp=dfs(pa,pb+1,sum+1,res);
			if(tmp>=k)
				tmp=inf;
			res=min(res,tmp);
			tmp=dfs(pa+1,pb,sum+1,res);
			if(tmp>=k)
				tmp=inf;
			res=min(res,tmp);
			tmp=dfs(pa+1,pb+1,sum+2,res);
			if(tmp>=k)
				tmp=inf;
			res=min(res,tmp);
		}
		else{
			tmp=dfs(pa,pb+1,sum+1,lim);
			if(tmp>=k)
				tmp=inf;
			res=min(res,tmp);
			tmp=dfs(pa+1,pb,sum+1,res);
			if(tmp>=k)
				tmp=inf;
			res=min(res,tmp);
			tmp=dfs(pa+1,pb+1,sum+2,res);
			if(tmp>=k)
				tmp=inf;
			res=min(res,tmp);
		}
		return res;
	}
	inline void Solve(void){
		st=clock();
		reg int res=dfs(1,1,0,inf);
		if(res==inf)
			puts("-1");
		else
			printf("%d\n",res);
		return;
	}
}

int main(void){
	n=read(),m=read(),k=read();
	read(a+1),read(b+1);
	if(1ll*n*m<=2e6)
		Subtask1::Solve();
	else if(k<=10)
		Subtask2::Solve();
	else
		puts("-1");
	return 0;
}