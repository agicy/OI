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

const int MAXN=2e6+5;

int n;

int main(void){
	n=read();
	reg double ans=1;
	for(reg int i=n;i>1;--i)
		ans*=(2.0*i-2.0)/(2.0*i-1.0);
	printf("%.9lf\n",ans);
	return 0;
}