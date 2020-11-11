#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
inline int read(void){
	reg bool f=false;
	reg char ch=getchar();
	reg int res=0;
	while(!isdigit(ch))f|=(ch=='-'),ch=getchar();
	while(isdigit(ch))res=10*res+(ch^'0'),ch=getchar();
	return f?-res:res;
}

const int MAXN=2e3+5;

int n;
char str[MAXN];
char ans[MAXN];

int main(void){
	n=read();
	scanf("%s",str+1);
	for(reg int i=n,j=1;i>=1;i-=2,++j){
		ans[n-j+1]=str[i];
		if(i!=1)
			ans[j]=str[i-1];
	}
	ans[n+1]='\0';
	puts(ans+1);
	return 0;
}