#include<bits/stdc++.h>
using namespace std;
#define reg register

const int MAXN=3000+5;

int n,K;
int b[MAXN],sum[MAXN];
char c[MAXN];
vector<int> V[MAXN];

int main(void){
	scanf("%d%d%s",&n,&K,c+1);
	int Max=0,Min=0;
	for(reg int i=1;i<=n;++i)
		b[i]=(c[i]=='R'?1:0);
	for(reg int i=1;i<=n;++i){
		reg int cnt=0;
		for(int j=1;j<n;++j)
			if(b[j]>b[j+1]){
				++cnt;
				V[i].push_back(j);
			}
		for(reg int j=0;j<cnt;++j)
			swap(b[V[i][j]],b[V[i][j]+1]);
		if(!cnt){
			Min=i-1;
			break;
		}
		Max+=cnt;
		sum[i]=sum[i-1]+cnt;
	}
	if(K<Min||K>Max)
		puts("-1");
	else if(K==Min)
		for(reg int i=1;i<=Min;++i){
			printf("%d ",(int)V[i].size());
			for(reg int j=0,len=V[i].size();j<len;++j)
				printf("%d ",V[i][j]);
			puts("");
		}
	else{
		reg int cur=0;
		while(cur<Min&&Max-sum[cur+1]+cur+1>=K)
			++cur;
		for(reg int i=1;i<=cur;++i){
			printf("%d ",(int)V[i].size());
			for(reg int j=0,len=V[i].size();j<len;++j)
				printf("%d ",V[i][j]);
			puts("");
		}
		if(Max-sum[cur]+cur-K+1){
			printf("%d ",Max-sum[cur]+cur-K+1);
			for(reg int i=0;i<Max-sum[cur]+cur-K+1;++i)
				printf("%d ",V[cur+1][i]);
			puts("");
		}
		for(reg int i=Max-sum[cur]+cur-K+1,len=V[cur+1].size();i<len;++i)
			printf("%d %d\n",1,V[cur+1][i]);
		for(reg int i=cur+2;i<=Min;++i)
			for(reg int j=0,len=V[i].size();j<len;++j)
				printf("%d %d\n",1,V[i][j]);
	}
	return 0;
}
