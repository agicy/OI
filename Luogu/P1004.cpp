#include<stdio.h>

int n,f[10][10][10][10],map[10][10],tx,ty,v;

inline int max(int,int);
inline int max(int,int,int,int);

int main(void){
	register int i,j,k,l;
	scanf("%d",&n);
	do
		scanf("%d%d%d",&tx,&ty,&v),map[tx][ty]=v;
	while(tx&&ty&&v);
	for(i=1;i<=n;i++)
		for(j=1;j<=n;j++)
			for(k=1;k<=n;k++)
				for(l=1;l<=n;l++){
					f[i][j][k][l]=max(
							f[i-1][j][k-1][l],
							f[i-1][j][k][l-1],
							f[i][j-1][k-1][l],
							f[i][j-1][k][l-1]
						)+map[i][j]+map[k][l];
					if(i==k&&l==j)
						f[i][j][k][l]-=map[i][j];
					}
	printf("%d\n",f[n][n][n][n]);
	return 0;
}

int max(int a,int b){
	return a>b?a:b;
}

int max(int a,int b,int c,int d){
	return max(max(a,b),max(c,d));
}