#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++)
static char buf[1<<21],*p1=buf,*p2=buf;
#define flush() (fwrite(wbuf,1,wp1,stdout),wp1=0)
#define putchar(c) (wp1==wp2&&(flush(),0),wbuf[wp1++]=c)
static char wbuf[1<<21];int wp1;const int wp2=1<<21;
inline int read(void){
	reg char ch=getchar();
	reg int res=0;
	while(!isdigit(ch)) ch=getchar();
	while(isdigit(ch)) res=10*res+(ch^'0'),ch=getchar();
	return res;
}

inline void writeln(reg int x){
	static char buf[32];
	reg int p=-1;
	if(x==0) putchar('0');
	else while(x) buf[++p]=(x%10)^'0',x/=10;
	while(~p) putchar(buf[p--]);
	putchar('\n');
	return;
}

const int MAXN=1e6+5;

int n,m,c;
int a[MAXN];
int Qmin[MAXN],Qmax[MAXN];

int main(void){
	n=read(),m=read(),c=read();
	for(reg int i=1;i<=n;++i)
		a[i]=read();
	reg bool flag=false;
	reg int _headMax=0,_tailMax=0;
	reg int _headMin=0,_tailMin=0;
	for(reg int i=1;i<=n;++i){
		while(_headMax<_tailMax&&Qmax[_headMax]+m<=i)
			++_headMax;
		while(_headMax<_tailMax&&a[i]<a[Qmax[_tailMax-1]])
			--_tailMax;
		Qmax[_tailMax++]=i;
		while(_headMin<_tailMin&&Qmin[_headMin]+m<=i)
			++_headMin;
		while(_headMin<_tailMin&&a[i]>a[Qmin[_tailMin-1]])
			--_tailMin;
		Qmin[_tailMin++]=i;
		if(i>=m&&a[Qmin[_headMin]]-a[Qmax[_headMax]]<=c){
			flag=true;
			writeln(i-m+1);
		}
	}
	if(!flag)
		putchar('N'),putchar('O'),putchar('N'),putchar('E'),putchar('\n');
	flush();
	return 0;
}