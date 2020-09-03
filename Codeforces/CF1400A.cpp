#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

const int MAXN=50+5;

int n;
char str[MAXN<<1];

int main(void){
	int t;
	scanf("%d",&t);
	while(t--){
		cin>>n>>(str+1);
		for(int i=1;i<=n;++i)
			putchar(str[2*i-1]);
		putchar('\n');
	}
	return 0;
}
