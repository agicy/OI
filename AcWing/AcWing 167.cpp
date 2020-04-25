#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
typedef unsigned long long ull;

int n,sum,Max,Min,T[51],len;

void DFS(int,int,int);

int main(void){
	scanf("%d",&n);
	if(n==0)
		exit(0);
	sum=0,Min=50,Max=0;
	memset(T,0,sizeof(T));
	for(reg int i=1;i<=n;++i){
		static int temp;
		scanf("%d",&temp);
		if(temp<=50){
			++T[temp];
			sum+=temp;
			Min=min(Min,temp),Max=max(Max,temp);
		}
	}
	for(reg int i=Max;i<=sum;++i)
		if(sum%i==0){
			len=i;
			DFS(sum/i,0,Max);
		}
	return 0;
}

void DFS(int residual,int sum,int Max_Index){//residual:สฃำเ
	reg int i;
	if(!residual)
		printf("%d\n",len),main();
	else if(!(sum^len))
		DFS(residual-1,0,Max);
	else
		for(i=Max_Index;i>=Min;i--)
			if(T[i]&&i+sum<=len){
				T[i]--;
				DFS(residual,sum+i,i);
				T[i]++;
				if(!sum||sum+i==len)
					break;
			}
	return;
}
