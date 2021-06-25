#include<bits/stdc++.h>
using namespace std;
#define reg register
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++)
static char buf[1<<21],*p1=buf,*p2=buf;
inline int read(void){
	reg char ch=getchar();
	reg int res=0;
	while(!isdigit(ch)) ch=getchar();
	while(isdigit(ch)) res=10*res+ch-'0',ch=getchar();
	return res;
}

int n;

int main(void){
	reg int t=read();
	while(t--){
		n=read();
		reg int r=sqrt(n);
		printf("%d\n",r+n/r-2+(n%r!=0));
	}
	return 0;
}