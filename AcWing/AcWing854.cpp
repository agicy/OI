#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;

const int MAXN=200+5;
const int inf=0x3f3f3f3f;

int n,m,k;
int f[MAXN][MAXN];

int main(void){
	memset(f,0x3f,sizeof(f));
	scanf("%d%d%d",&n,&m,&k);
	for(reg int i=1;i<=n;++i)
		f[i][i]=0;
	for(reg int i=1;i<=m;++i){
		static int x,y,z;
		scanf("%d%d%d",&x,&y,&z);
		f[x][y]=min(f[x][y],z);
	}
	for(reg int k=1;k<=n;++k)
		for(reg int i=1;i<=n;++i)
			if(i!=k)
				for(reg int j=1;j<=n;++j)
					if(i!=j&&j!=k)
						f[i][j]=min(f[i][j],f[i][k]+f[k][j]);
	while(k--){
		static int x,y;
		scanf("%d%d",&x,&y);
		if(f[x][y]>2e7)
			puts("impossible");
		else
			printf("%d\n",f[x][y]);
	}
	return 0;
}