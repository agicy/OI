#include<bits/stdc++.h>
using namespace std;
#define reg register

const int MAXLEN=50+5;

int n,sum,Max,Min,temp;
int T[MAXLEN];
int len;

inline void DFS(reg int res,reg int sum,reg int las){
	register int i;
	if(!res)
		printf("%d\n",len),exit(0);
	else if(!(sum^len))
		DFS(res-1,0,Max);
	else
		for(reg int i=las;i>=Min;--i)
			if(T[i]&&i+sum<=len){
				--T[i];
				DFS(res,sum+i,i);
				++T[i];
				if(!sum||sum+i==len)
					break;
			}
	return;
}

int main(void){
	scanf("%d",&n);
	Min=50,Max=0;
	for(reg int i=1;i<=n;++i){
		scanf("%d",&temp);
		if(temp<=50){
			++T[temp];
			sum+=temp;
			Min=min(Min,temp),Max=max(Max,temp);
		}
	}
	for(reg int i=Max;i<=sum;++i)
		if(!(sum%i)){
			len=i;
			DFS(sum/i,0,Max);
		}
	return 0;
}