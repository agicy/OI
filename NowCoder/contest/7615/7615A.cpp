#include<bits/stdc++.h>
using namespace std;
#define register
typedef long long ll;
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++)
static char buf[100000],*p1=buf,*p2=buf;
inline int read(void){
	bool f=false;
	char ch=getchar();
	int res=0;
	while(!isdigit(ch))f|=(ch=='-'),ch=getchar();
	while(isdigit(ch))res=10*res+ch-'0',ch=getchar();
	return f?-res:res;
}

int n;

int main(void){
	n=read();
	printf("%.10lf\n",n/(2.0*n-1));
	return 0;
}