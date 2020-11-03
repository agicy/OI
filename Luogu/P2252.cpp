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
	while(!isdigit(ch))f|=(ch=='-'),ch=getchar();
	while(isdigit(ch))res=10*res+(ch^'0'),ch=getchar();
	return f?-res:res;
}

int a,b;

int main(void){
	a=read(),b=read();
	if(b>a)
		swap(a,b);
	reg int tmp=(sqrt(5.0)+1.0)*0.5*(0.0+a-b);
	if(tmp==b)
		puts("0");
	else
		puts("1");
	return 0;
}