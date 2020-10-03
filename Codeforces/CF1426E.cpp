#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++)
static char buf[100000],*p1=buf,*p2=buf;
inline int read(void){
	reg char ch=getchar();
	reg int res=0;
	while(ch<'0'||'9'<ch)ch=getchar();
	while('0'<=ch&&ch<='9')res=10*res+ch-'0',ch=getchar();
	return res;
}

int n,a1,a2,a3,b1,b2,b3;

int main(void){
	n=read();
	a1=read(),a2=read(),a3=read();
	b1=read(),b2=read(),b3=read();
	printf("%d %d\n",n-min(a1,n-b2)-min(a2,n-b3)-min(a3,n-b1),min(a1,b2)+min(a2,b3)+min(a3,b1));
	return 0;
}