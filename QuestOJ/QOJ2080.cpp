#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;

const int MAXN=1e3+5;

int n;
char M[MAXN][MAXN];
int cntx[MAXN],cnty[MAXN];

int main(void){
	scanf("%d",&n);
	for(reg int i=1;i<=n;++i)
		scanf("%s",M[i]+1);
	reg bool flag=false;
	for(reg int i=1;i<=n;++i)
		for(reg int j=1;j<=n;++j)
			if(M[i][j]=='#')
				flag=true,++cntx[i],++cnty[j];
	if(!flag)
		puts("-1");
	else{
		int ans=n;
		for(reg int i=1;i<=n;++i)
			if(cnty[i])
				ans=min(ans,n-cntx[i]);
			else
				ans=min(ans,n-cntx[i]+1);
		for(reg int i=1;i<=n;++i)
			if(cnty[i]!=n)
				++ans;
		printf("%d\n",ans);
	}
	return 0;
}