#include<cstdio>

const int MAXN=15+5;

int n;
int ans[MAXN];

void DFS(int d,int last){
	register int i;
	for(i=1;i<=d;++i){
		printf("%d ",ans[i]);
	}
	putchar('\n');
	for(i=last+1;i<=n;++i){
		ans[d+1]=i;
		DFS(d+1,i);
	}
	return;
}

int main(void){
	scanf("%d",&n);
	DFS(0,0);
	return 0;
}
