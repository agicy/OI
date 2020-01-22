#include<cstdio>
#include<vector>
using std::vector;
#include<queue>
using std::priority_queue;
using std::less;
using std::greater;

int n,m;
priority_queue<int,vector<int>,greater<int>/* */> Q1;
priority_queue<int,vector<int>,less<int>/* */> Q2;

int main(void){
	register int i,j;
	scanf("%d",&n);
	for(i=1;i<=n;++i){
		scanf("%d",&m);
		for(j=1;j<=m;++j){
			static int temp;
			scanf("%d",&temp);
			Q1.push(temp),Q2.push(temp);
		}
		printf("%d %d\n",Q1.top(),Q2.top());
		Q1.pop(),Q2.pop();
	}
	return 0;
}
