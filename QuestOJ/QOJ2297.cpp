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

int n;

int main(void){
	n=read();
	reg double ans=1;
	for(reg int i=2*n-1;i>=3;i-=2)
		ans*=(i-1.0)/i;
	printf("%.6lf\n",ans);
	return 0;
}