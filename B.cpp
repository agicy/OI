#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;

const int MAXN=18;

int n;
int G[MAXN][MAXN];

namespace Subtask1{
	inline int getLg(reg int x){
		reg int res=-1;
		while(x)
			++res,x>>=1;
		return res;
	}
	inline int lowbit(reg int x){
		return x&(-x);
	}
	inline void Solve(void){
		int f[1<<n][n];
		memset(f,0,sizeof(f));
		for(reg int i=0;i<n;++i)
			f[1<<i][i]=1;
		reg int U=(1<<n)-1;
		for(reg int S=1;S<=U;++S)
			for(reg int i=S;i;i^=lowbit(i)){
				reg int k=getLg(lowbit(i));
				for(reg int j=0;j<n;++j)
					if(G[k][j]&&!((S>>j)&1))
						f[S|(1<<j)][j]+=f[S][k];
			}
		reg int ans=0;
		for(reg int i=0;i<n;++i)
			ans+=f[U][i];
		printf("%d\n",ans);
		return;
	}
}

namespace Subtask2{
	inline void Solve(void){
		puts("0");
		return;
	}
}

int main(void){
	scanf("%d",&n);
	for(reg int i=0;i<n;++i)
		for(reg int j=0;j<n;++j)
			scanf("%d",&G[i][j]);
	if(n<=13)
		Subtask1::Solve();
	else
		Subtask2::Solve();
	return 0;
}