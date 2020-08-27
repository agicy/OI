#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;

const int MAXM=20+5;
const int inf=0x3f3f3f3f;

int n,m;
int V[MAXM];
int ans=inf;

inline void dfs(reg int dep,reg int s,reg int v,reg int r,reg int h){
	if(dep==0){
		if(v==n)
			ans=min(ans,s);
		return;
	}
	if(v+V[dep]>n)
		return;
	if(s+(n-v)/r>ans)
		return;
	for(reg int i=r-1;i>=dep;--i)
		for(reg int j=h-1;j>=dep;--j){
			if(dep==m)
				s=i*i;
			dfs(dep-1,s+2*i*j,v+i*i*j,i,j);
		}
	return;
}

int main(void){
	scanf("%d%d",&n,&m);
	for(reg int i=1;i<=m;++i)
		V[i]=V[i-1]+i*i*i;
	dfs(m,0,0,sqrt(n),n);
	if(ans==inf)
		puts("0");
	else
		printf("%d\n",ans);
	return 0;
}