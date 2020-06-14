#include<bits/stdc++.h>
using namespace std;
#define reg register

const int MAXS=200000+5;

char str[MAXS];
int sum[MAXS][3];

int main(void){
	int T;
	scanf("%d",&T);
	while(T--){
		scanf("%s",str+1);
		reg int len=strlen(str+1);
		for(reg int i=1;i<=len;++i){
			sum[i][0]=sum[i][1]=sum[i][2]=0;
			sum[i][str[i]-'1']=1;
		}
		for(reg int i=1;i<=len;++i){
			sum[i][0]+=sum[i-1][0];
			sum[i][1]+=sum[i-1][1];
			sum[i][2]+=sum[i-1][2];
		}
		int ans=len+1;
		for(reg int l=1,r=1;l<=len;++l){
			while(r<=len&&(sum[r][0]-sum[l-1][0]<=0||sum[r][1]-sum[l-1][1]<=0||sum[r][2]-sum[l-1][2]<=0))
				++r;
			if(r==len+1)
				break;
			ans=min(ans,r-l+1);
		}
		printf("%d\n",ans!=len+1?ans:0);
	}
	return 0;
}