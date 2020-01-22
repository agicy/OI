#include<cstdio>

const int MAXN=15+5;

bool vis[MAXN];
int n,m;
int ans[MAXN];

void DFS(int d,int last){
	register int i;
	if(d==n){
		for(i=1;i<=d;++i)
			printf("%d ",ans[i]);
		putchar('\n');
	}
	for(i=1;i<=n;++i)
		if(!vis[i]){
			vis[i]=true;
			ans[d+1]=i;
			DFS(d+1,i);
			vis[i]=false;
		}
	return;
}

int main(void){
	scanf("%d",&n);
	DFS(0,0);
	return 0;
}
