#include<cstdio>
#include<vector>
using std::vector;
#include<queue>
using std::priority_queue;
using std::less;
using std::greater;

int P,ID,n;
priority_queue<int,vector<int>,greater<int>/**/> A;//小根堆
priority_queue<int,vector<int>,less<int>/**/> B;//大根堆

int main(void){
	register int i,count;
	scanf("%d",&P);
	while(P--){
		count=0;
		scanf("%d%d",&ID,&n);
		printf("%d %d\n",ID,(n+1)>>1);
		for(i=1;i<=n;++i){
			static int a;
			scanf("%d",&a);
			if(A.empty())
				A.push(a);
			else{
				if(a>A.top())
					A.push(a);
				else
					B.push(a);
				while(A.size()<B.size()){
					A.push(B.top());
					B.pop();
				}
				while(A.size()>B.size()+1){
					B.push(A.top());
					A.pop();
				}
			}
			if(i&1){
				printf("%d ",A.top());
				if((++count%=10)==0)
					putchar('\n');
			}
		}
		if(count<10)
			putchar('\n');
		while(!A.empty())
			A.pop();
		while(!B.empty())
			B.pop();
	}
	return 0;
}
