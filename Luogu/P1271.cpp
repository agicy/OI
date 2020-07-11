#include<bits/stdc++.h>
using namespace std;
#define reg register
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

const int MAXN=999+5;

int n,m;
int T[MAXN];

int main(void){
	n=read(),m=read();
	for(reg int i=1;i<=m;++i)
		++T[read()];
	reg int cnt=0;
	for(reg int i=1;i<=n;++i)
		while(T[i]--)
			printf("%d%c",i,++cnt==m?'\n':' ');
	return 0;
}
