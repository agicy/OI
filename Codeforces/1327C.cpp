#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++)
static char buf[100000],*p1=buf,*p2=buf;
inline int read(void){
	reg bool f=false;
	reg char ch=getchar();
	reg int res=0;
	while(ch<'0'||'9'<ch)f|=(ch=='-'),ch=getchar();
	while('0'<=ch&&ch<='9')res=10*res+ch-'0',ch=getchar();
	return f?-res:res;
}

int n,m;

int main(void){
	n=read(),m=read();
	printf("%d\n",n*m+n+m-2);
	for(reg int i=1;i<n;++i)
		putchar('D');
	for(reg int i=1;i<m;++i)
		putchar('R');
	for(reg int i=1;i<=n;++i,putchar('U'))
		for(reg int j=1;j<m;++j)
			putchar((i&1)?'L':'R');
	putchar('\n');
	return 0;
}
