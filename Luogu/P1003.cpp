#include<stdio.h>
int main(void){
	int n;
	scanf("%d",&n);
	int a[n],b[n],g[n],k[n];
	for(int i=0;i<n;i++)
		scanf("%d %d %d %d",&a[i],&b[i],&g[i],&k[i]);
	int x,y;
	scanf("%d%d",&x,&y);
	for(int i=n-1;i>=0;i--)
		if((a[i]<=x&&x<=a[i]+g[i])&&(b[i]<=y&&y<=b[i]+k[i])){
			printf("%d",i+1);
			return 0;
		}
	printf("-1");
	return 0;
}