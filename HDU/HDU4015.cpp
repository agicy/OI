#include<cstdio>
using namespace std;
#define reg register
typedef long long ll;

int main(void){
	int t;
	scanf("%d",&t);
	reg int Case=0;
	while(t--){
		static int m,k;
		scanf("%d%d",&m,&k);
		printf("Case #%d: %.8lf\n",++Case,1.0/(k+m*k+1));
	}
	return 0;
}