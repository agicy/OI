#include<bits/stdc++.h>
using namespace std;
#define reg register

const int MAXN=99+5;

int n;
char s[MAXN];

int main(void){
	scanf("%s",s+1);
	n=strlen(s+1);
	bool flag=true;
	for(reg int i=1;i<=n;++i)
		flag&=(s[i]==s[n-i+1]);
	for(reg int i=1;i<=(n-1)/2;++i)
		flag&=(s[i]==s[(n-1)/2-i+1]);
	for(reg int i=1;i+(n+3)/2-1<=n;++i)
		flag&=(s[i+(n+3)/2-1]==s[n-i+1]);
	puts(flag?"Yes":"No");
	return 0;
}
