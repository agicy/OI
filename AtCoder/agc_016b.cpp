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

inline int max(reg int a,reg int b){
	return a>b?a:b;
}

inline int min(reg int a,reg int b){
	return a<b?a:b;
}

const int MAXN=1e5+5;
const int inf=0x3f3f3f3f;

int n;
int a[MAXN];

int main(void){
	n=read();
	reg int Max=-inf,Min=inf;
	for(reg int i=1;i<=n;++i)
		a[i]=read(),Max=max(Max,a[i]),Min=min(Min,a[i]);
	reg int cnt=0;
	for(reg int i=1;i<=n;++i)
		if(a[i]==Min)
			++cnt;
	if(Max-Min>1)
		puts("No");
	else if(Max==Min)
		puts((Min==n-1||2*Min<=n)?"Yes":"No");
	else
		puts((Min<cnt||n-cnt<2*(Max-cnt))?"No":"Yes");
	return 0;
}