#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;

const int MAXS=700+5;
const int p=1e9+7;

char s[MAXS];
int T[MAXS];
int top,S[MAXS];
int dp[MAXS][MAXS][3][3];

inline int add(reg int a,reg int b){
	reg int sum=a+b;
	return sum>=p?sum-p:sum;
}

inline int mul(reg int a,reg int b){
	return 1ll*a*b%p;
}

inline void dfs(reg int l,reg int r){
	if(l+1==r)
		dp[l][r][0][1]=dp[l][r][0][2]=dp[l][r][1][0]=dp[l][r][2][0]=1;
	else if(T[l]==r){
		dfs(l+1,r-1);
		for(reg int i=0;i<3;++i)
			for(reg int j=0;j<3;++j){
				if(i!=1)
					dp[l][r][1][0]=add(dp[l][r][1][0],dp[l+1][r-1][i][j]);
				if(i!=2)
					dp[l][r][2][0]=add(dp[l][r][2][0],dp[l+1][r-1][i][j]);
				if(j!=1)
					dp[l][r][0][1]=add(dp[l][r][0][1],dp[l+1][r-1][i][j]);
				if(j!=2)
					dp[l][r][0][2]=add(dp[l][r][0][2],dp[l+1][r-1][i][j]);
			}
	}
	else{
		dfs(l,T[l]),dfs(T[l]+1,r);
		for(reg int il=0;il<3;++il)
			for(reg int jl=0;jl<3;++jl)
				for(reg int ir=0;ir<3;++ir)
					for(reg int jr=0;jr<3;++jr){
						if(jl==jr&&jl!=0)
							continue;
						dp[l][r][il][ir]=add(dp[l][r][il][ir],mul(dp[l][T[l]][il][jl],dp[T[l]+1][r][jr][ir]));
					}
	}
	return;
}

int main(void){
	scanf("%s",s+1);
	reg int n=strlen(s+1);
	for(reg int i=1;i<=n;++i)
		if(s[i]=='(')
			S[++top]=i;
		else{
			T[i]=S[top--];
			T[T[i]]=i;
		}
	dfs(1,n);
	reg int ans=0;
	for(reg int i=0;i<3;++i)
		for(reg int j=0;j<3;++j)
			ans=add(ans,dp[1][n][i][j]);
	printf("%d\n",ans);
	return 0;
}