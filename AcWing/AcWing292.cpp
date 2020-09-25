#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;

const int MAXN=100+5;
const int MAXM=10;

int n,m;
char M[MAXM];
int a[MAXN],cnt[1<<MAXM];
int dp[1<<MAXM][1<<MAXM][2];

inline bool I(reg int a,reg int b){
	return !(a&b);
}

inline bool check(reg int S,reg int i){
	return I(S,a[i])&&I(S,S<<1)&&I(S,S<<2);
}

int main(void){
	scanf("%d%d",&n,&m);
	for(reg int i=0;i<n;++i){
		scanf("%s",M);
		for(reg int j=0;j<m;++j)
			a[i]=(a[i]<<1)|(M[j]=='H');
	}
	reg int U=(1<<m)-1;
	for(reg int i=0;i<=U;++i)
		cnt[i]=cnt[i>>1]+(i&1);
	for(reg int S=0;S<=U;++S)
		if(check(S,0))
			dp[0][S][0]=cnt[S];
	for(reg int L=0;L<=U;++L)
		for(reg int S=0;S<=U;++S)
			if(I(L,S)&&check(L,0)&&check(S,1))
				dp[L][S][1]=cnt[S]+cnt[L];
	for(reg int i=2;i<n;++i){
		reg int p=(i&1),q=(p^1);
		for(reg int L=0;L<=U;++L){
			if(!check(L,i-1))
				continue;
			for(reg int S=0;S<=U;++S){
				if(I(L,S)&&check(S,i))
					for(reg int pre=0;pre<=U;++pre){
						if((pre&L)||(pre&S)||!check(pre,i-2))
							continue;
						dp[L][S][p]=max(dp[L][S][p],dp[pre][L][q]+cnt[S]);
					}
			}
		}
	}
	int ans=0;
	for(reg int L=0;L<=U;++L)
		for(reg int S=0;S<=U;++S)
			ans=max(ans,dp[L][S][(n-1)&1]);
	printf("%d\n",ans);
	return 0;
}