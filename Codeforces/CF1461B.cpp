#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;

const int MAXN=500+5;
const int MAXM=500+5;

int n,m;
char M[MAXN][MAXM];
int lef[MAXN][MAXM],rig[MAXN][MAXM],f[MAXN][MAXM];

int main(void){
	int t;
	scanf("%d",&t);
	while(t--){
		scanf("%d%d",&n,&m);
		for(reg int i=1;i<=n;++i){
			scanf("%s",M[i]+1);
			lef[i][0]=0;
			for(reg int j=1;j<=m;++j)
				if(M[i][j]=='*')
					lef[i][j]=lef[i][j-1]+1;
				else
					lef[i][j]=0;
			rig[i][m+1]=0;
			for(reg int j=m;j>=1;--j)
				if(M[i][j]=='*')
					rig[i][j]=rig[i][j+1]+1;
				else
					rig[i][j]=0;
		}
		reg int ans=0;
		for(reg int i=1;i<=n;++i)
			for(reg int j=1;j<=m;++j){
				f[i][j]=min(f[i-1][j]+1,min(lef[i][j],rig[i][j]));
				ans+=f[i][j];
			}
		printf("%d\n",ans);
	}
	return 0;
}