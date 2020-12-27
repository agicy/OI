#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;

const int MAXN=30+5;
const int MAXM=30+5;

int n,m;
int f[MAXN][MAXM];

int main(void){
	scanf("%d%d",&n,&m);
	f[0][0]=1;
	for(reg int i=0;i<m;++i)
		for(reg int j=0;j<n;++j)
			if(f[i][j]){
				f[i+1][(j-1+n)%n]+=f[i][j];
				f[i+1][(j+1)%n]+=f[i][j];
			}
	printf("%d\n",f[m][0]);
	return 0;
}