#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;

const int MAXSIZE=2e5+5;

int n;

int main(void){
	scanf("%d",&n);
	for(reg int i=1;i<=n;++i){
		static int x;
		scanf("%d",&x);
		static int S[MAXSIZE];
		reg int tot=0;
		for(reg int i=1;i*i<=x;++i)
			if(x%i==0){
				printf("%d ",i);
				if(x/i!=i)
					S[++tot]=x/i;
			}
		for(reg int i=tot;i>=1;--i)
			printf("%d ",S[i]);
		putchar('\n');
	}
	return 0;
}