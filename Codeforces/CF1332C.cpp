#include<bits/stdc++.h>
using namespace std;
#define reg register

const int MAXN=200000+5;

int T;
int n,K;
char str[MAXN];
int cnt[MAXN][26];

int main(void){
	scanf("%d",&T);
	while(T--){
		scanf("%d%d%s",&n,&K,str);
		for(reg int i=0;i<K;++i)
			for(reg int j=0;j<26;++j)
				cnt[i][j]=0;
		for(reg int i=0;i<n;++i)
			++cnt[i%K][str[i]-'a'];
		reg int ans=0;
		for(reg int i=0;i<(K+1)/2;++i){
			int Max=0;
			for(reg int j=0;j<26;++j)
				if(i==K-i-1)
					Max=max(Max,cnt[i][j]);
				else
					Max=max(Max,cnt[i][j]+cnt[K-i-1][j]);
			if(i==K-i-1)
				ans+=n/K-Max;
			else
				ans+=2*n/K-Max;
		}
		printf("%d\n",ans);
	}
	return 0;
}
