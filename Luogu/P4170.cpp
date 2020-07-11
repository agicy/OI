#include<bits/stdc++.h>
using namespace std;
#define reg register

const int MAXN=50+5;

int n;
char str[MAXN];
int f[MAXN][MAXN];

int main(void){
	scanf("%s",str+1);
	n=strlen(str+1);
	memset(f,0X3F,sizeof(f));
	for(reg int i=1;i<=n;++i)
		f[i][i]=1;
	for(reg int len=1;len<n;++len)
		for(reg int l=1,r=1+len;r<=n;++l,++r)
			if(str[l]==str[r])
				f[l][r]=min(f[l+1][r],f[l][r-1]);
			else
				for(reg int i=l;i<r;++i)
					f[l][r]=min(f[l][r],f[l][i]+f[i+1][r]);
	printf("%d\n",f[1][n]);
	return 0;
}
