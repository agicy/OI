#include<stdio.h>
int f[60][60][60][60]={0},num[60][60]={0};
int max(int a,int b){
	return a>b?a:b;
}
int max(int a,int b,int c,int d){
	return max(max(a,b),max(c,d));
}
int main(void){
	int m,n;
	scanf("%d%d",&m,&n);
	for(int i=1;i<=m;i++)
		for(int j=1;j<=n;j++)
			scanf("%d",&num[i][j]);
	for(int i=1;i<=m;i++)
		for(int j=1;j<=n;j++)
			for(int k=1;k<=m;k++)
				for(int l=1;l<=n;l++){
					f[i][j][k][l]=max(f[i-1][j][k-1][l],f[i-1][j][k][l-1],f[i][j-1][k-1][l],f[i][j-1][k][l-1])+num[i][j]+num[k][l];
					if(i==k&&l==j)
						f[i][j][k][l]-=num[i][j];
					}
	printf("%d",f[m][n-1][m-1][n]);
	return 0;
}