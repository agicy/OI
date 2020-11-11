#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
inline int read(void){
	reg bool f=false;
	reg char ch=getchar();
	reg int res=0;
	while(!isdigit(ch))f|=(ch=='-'),ch=getchar();
	while(isdigit(ch))res=10*res+(ch^'0'),ch=getchar();
	return f?-res:res;
}

const int MAXN=100+5;
const int inf=0x3f3f3f3f;

int n;
char M[5][MAXN][MAXN];
char G[MAXN*2][MAXN*2];

inline int solve(reg int a,reg int b,reg int c,reg int d){
	for(reg int i=1;i<=n;++i)
		for(reg int j=1;j<=n;++j){
			G[i][j]=M[a][i][j];
			G[i][j+n]=M[b][i][j];
			G[i+n][j]=M[c][i][j];
			G[i+n][j+n]=M[d][i][j];
		}
	int cnt1=0,cnt2=0;
	for(reg int i=1;i<=2*n;++i)
		for(reg int j=1;j<=2*n;++j)
			if((G[i][j]&1)^((i+j)&1))
				++cnt1;
			else
				++cnt2;
	return min(cnt1,cnt2);
}

int main(void){
	n=read();
	for(reg int i=1;i<=4;++i)
		for(reg int j=1;j<=n;++j)
			scanf("%s",M[i][j]+1);
	int ans=inf;

	ans=min(ans,solve(1,2,3,4));
	ans=min(ans,solve(1,2,4,3));
	ans=min(ans,solve(1,3,2,4));
	ans=min(ans,solve(1,3,4,2));
	ans=min(ans,solve(1,4,2,3));
	ans=min(ans,solve(1,4,3,2));

	ans=min(ans,solve(2,1,3,4));
	ans=min(ans,solve(2,1,4,3));
	ans=min(ans,solve(2,3,1,4));
	ans=min(ans,solve(2,3,4,1));
	ans=min(ans,solve(2,4,1,3));
	ans=min(ans,solve(2,4,3,1));

	ans=min(ans,solve(3,1,2,4));
	ans=min(ans,solve(3,1,4,2));
	ans=min(ans,solve(3,2,1,4));
	ans=min(ans,solve(3,2,4,1));
	ans=min(ans,solve(3,4,1,2));
	ans=min(ans,solve(3,4,2,1));

	ans=min(ans,solve(4,1,2,3));
	ans=min(ans,solve(4,1,3,2));
	ans=min(ans,solve(4,2,1,3));
	ans=min(ans,solve(4,2,3,1));
	ans=min(ans,solve(4,3,1,2));
	ans=min(ans,solve(4,3,2,1));

	printf("%d\n",ans);
	return 0;
}