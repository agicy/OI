#include<stdio.h>
unsigned long long dp[21][21]={0};
int main(void){
	int n,m;
	scanf("%d%d",&n,&m);
	int mx,my;
	scanf("%d%d",&mx,&my);
	dp[0][0]=1;
	for(int i=0;i<=n;i++){
		for(int j=0;j<=m;j++)
			if(i==mx&&j==my||i==mx-1&&j==my-2||i==mx-2&&j==my-1||i==mx-2&&j==my+1||i==mx-1&&j==my+2||i==mx+1&&j==my-2||i==mx+2&&j==my-1||i==mx+2&&j==my+1||i==mx+1&&j==my+2)
				dp[i][j]=0;
			else if(i==0&&j!=0)
				dp[i][j]=dp[i][j-1];
			else if(j==0&&i!=0)
				dp[i][j]=dp[i-1][j];
			else if(i==0&&j==0)
				dp[i][j]=1;
			else
				dp[i][j]=dp[i-1][j]+dp[i][j-1];
	}
	printf("%lld",dp[n][m]);
	return 0;
}