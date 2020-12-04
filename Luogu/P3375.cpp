#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;

const int MAXN=1e6+5;

char a[MAXN],b[MAXN];
int kmp[MAXN];

int main(void){
	scanf("%s%s",a+1,b+1);
	reg int la=strlen(a+1),lb=strlen(b+1);
	for(reg int i=2,j=0;i<=lb;++i){
		while(j&&b[i]!=b[j+1])
			j=kmp[j];
		if(b[j+1]==b[i])
			++j;
		kmp[i]=j;
	}
	for(reg int i=1,j=0;i<=la;++i){
		while(j>0&&b[j+1]!=a[i])
			j=kmp[j];
		if(b[j+1]==a[i])
			++j;
		if(j==lb){
			printf("%d\n",i-lb+1);
			j=kmp[j];
		}
	}
	for(reg int i=1;i<=lb;++i)
		printf("%d%c",kmp[i],i==lb?'\n':' ');
	return 0;
}