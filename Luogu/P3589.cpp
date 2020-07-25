#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;

const int MAXM=1e6+5;

int n,a,b,p,m;
char str[MAXM];
char c[MAXM];

int main(void){
	scanf("%d%d%d%d%d%s",&n,&a,&b,&p,&m,str+1);
	for(reg int i=0;i<n;++i)
		if((1ll*a*i+b)%n<p)
			c[i]='0';
		else
			c[i]='1';
	puts(c);
	return 0;
}
