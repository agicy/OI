#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;

const int MAXS=1e6+5;

char s[MAXS];
char t[MAXS];
int nex[MAXS];
int top,S[MAXS];
int f[MAXS];

int main(void){
	scanf("%s%s",s+1,t+1);
	reg int ls=strlen(s+1),lt=strlen(t+1);
	for(reg int i=2,j=0;i<=lt;++i){
		while(j&&t[i]!=t[j+1])
			j=nex[j];
		if(t[i]==t[j+1])
			++j;
		nex[i]=j;
	}
	for(reg int i=1,j=0;i<=ls;++i){
		while(j&&s[i]!=t[j+1])
			j=nex[j];
		if(s[i]==t[j+1])
			++j;
		f[i]=j;
		S[++top]=i;
		if(j==lt)
			top-=lt,j=f[S[top]];
	}
	for(reg int i=1;i<=top;++i)
		putchar(s[S[i]]);
	putchar('\n');
	return 0;
}