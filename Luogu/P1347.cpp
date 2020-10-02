#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;

const int MAXN=26+5;

int n,m;
bool g[MAXN][MAXN];

int main(void){
	scanf("%d%d",&n,&m);
	for(reg int i=1;i<=n;++i)
		g[i][i]=true;
	reg int ptr=0;
	for(ptr=1;ptr<=m;++ptr){
		static char A,tmp,B;
		cin>>A>>tmp>>B;
		reg int x=A-'A'+1,y=B-'A'+1;
		for(reg int i=1;i<=n;++i)
			for(reg int j=1;j<=n;++j)
				if(g[i][x]&&g[y][j])
					g[i][j]=true;
		reg bool flag1=false,flag2=false;
		if(A==B){
			printf("Inconsistency found after %d relations.\n",ptr);
			flag1=true;
		}
		for(reg int i=1;i<=n&&!flag1;++i)
			for(reg int j=i+1;j<=n;++j)
				if(g[i][j]&&g[j][i]){
					printf("Inconsistency found after %d relations.\n",ptr);
					flag1=true;
					break;
				}
				else if(!g[i][j]&&!g[j][i])
					flag2=true;
		if(flag1)
			break;
		if(!flag1&&!flag2){
			static int cnt[MAXN];
			memset(cnt,0,sizeof(cnt));
			printf("Sorted sequence determined after %d relations: ",ptr);
			for(reg int i=1;i<=n;++i)
				for(reg int j=i+1;j<=n;++j)
					if(g[i][j])
						++cnt[i];
					else
						++cnt[j];
			for(reg int i=n-1;i>=0;--i)
				for(reg int j=1;j<=n;++j)
					if(cnt[j]==i){
						putchar(j+'A'-1);
						break;
					}
			puts(".");
			break;
		}
	}
	if(ptr>m)
		puts("Sorted sequence cannot be determined.");
	return 0;
}