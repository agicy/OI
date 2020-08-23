#include<bits/stdc++.h>
using namespace std;
#define reg register

const int MAXL=50+5;

int n;
int len;
int T[MAXL];
int Min,Max;

inline bool dfs(reg int res,reg int sum,reg int las){
	if(!res){
		printf("%d\n",len);
		return true;
	}
	else if(sum==len)
		return dfs(res-1,0,Max);
	else
		for(reg int i=las;i>=Min;--i)
			if(T[i]&&i+sum<=len){
				--T[i];
				if(dfs(res,sum+i,i))
					return true;
				++T[i];
				if(!sum||sum+i==len)
					break;
			}
	return false;
}

int main(void){
	while(scanf("%d",&n)!=EOF){
		memset(T,0,sizeof(T));
		if(n==0)
			return 0;
		Min=50,Max=0;
		reg int sum=0;
		for(reg int i=1;i<=n;++i){
			static int x;
			scanf("%d",&x);
			++T[x];
			sum+=x;
			Min=min(Min,x),Max=max(Max,x);
		}
		for(reg int i=Max;i<=sum;++i)
			if(sum%i==0){
				len=i;
				dfs(sum/i,0,Max);
			}
	}
	return 0;
}