#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++)
static char buf[100000],*p1=buf,*p2=buf;
inline int read(void){
	reg char ch=getchar();
	reg int res=0;
	while(!isdigit(ch))ch=getchar();
	while(isdigit(ch))res=10*res+(ch^'0'),ch=getchar();
	return res;
}

int n,k;

int main(void){
	reg int t=read();
	while(t--){
		n=read(),k=read();
		for(reg int i=1;i<=k;++i)
			putchar('a');
		for(reg int i=1,x=0;i<=n-k;++i)
			putchar('a'+(++x)%3);
		putchar('\n');
	}
	return 0;
}