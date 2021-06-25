#include<bits/stdc++.h>
using namespace std;
#define reg register
#define MOD 998244353
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++)
static char buf[1<<21],*p1=buf,*p2=buf;
inline int read(void){
	reg bool f=false;
	reg char ch=getchar();
	reg int res=0;
	while(!isdigit(ch)) f|=(ch=='-'),ch=getchar();
	while(isdigit(ch)) res=10*res+ch-'0',ch=getchar();
	return f?-res:res;
}

int n;

int main(void){
	n=read();
	reg int f=0,g=0,last=0;
	for(reg int i=1;i<=n;++i){
		static int a;
		a=read();
		g=(g*2%MOD+last)%MOD;
		f=(f*2%MOD+a+g)%MOD;
		last=a;
	}
	printf("%d\n",f);
	return 0;
}
