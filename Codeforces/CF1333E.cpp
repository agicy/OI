#include<bits/stdc++.h>
using namespace std;
#define reg register

const int MAXN=500+5;

int n;
int a[MAXN][MAXN];

int main(void){
	scanf("%d",&n);
	if(n<=2)
		puts("-1");
	else{
		reg int cnt=0;
		for(reg int i=n;i>=4;--i)
			a[1][i]=++cnt;
		for(reg int i=4;i<=n;++i)
			a[2][i]=++cnt;
		for(reg int i=3;i<n;++i){
			if(i&1)
				for(reg int j=n;j>=1;--j)
					a[i][j]=++cnt;
			else
				for(reg int j=1;j<=n;++j)
					a[i][j]=++cnt;
		}
		if(n&1){
			for(reg int i=n;i>=1;--i)
				if(i!=2)
					a[n][i]=++cnt;
		}
		else
			for(reg int i=1;i<=n;++i)
				if(i!=2)
					a[n][i]=++cnt;
		a[n][2]=++cnt;
		a[1][1]=cnt+6,a[1][2]=cnt+1,a[1][3]=cnt+4;
		a[2][1]=cnt+2,a[2][2]=cnt+3,a[2][3]=cnt+5;
		for(reg int i=1;i<=n;++i)
			for(reg int j=1;j<=n;++j)
				printf("%d%c",a[i][j],j==n?'\n':' ');
	}
	return 0;
}
