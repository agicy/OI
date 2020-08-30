#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;

const int MAXA=2e3+5;
const int MAXB=2e3+5;
const int p=1e9+7;

int n;
int C[MAXA][MAXB];

int main(void){
	C[0][0]=1;
	for(reg int i=1;i<=2000;++i){
		C[i][0]=1;
		for(reg int j=1;j<=i;++j)
			C[i][j]=(C[i-1][j-1]+C[i-1][j])%p;
	}
	scanf("%d",&n);
	for(reg int i=1;i<=n;++i){
		static int a,b;
		scanf("%d%d",&a,&b);
		printf("%d\n",C[a][b]);
	}
	return 0;
}