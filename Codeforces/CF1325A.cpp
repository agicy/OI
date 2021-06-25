#include<bits/stdc++.h>
using namespace std;
#define reg register
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

int x;

int main(void){
	reg int T=read();
	while(T--){
		x=read();
		if(x&1)
			printf("%d %d\n",1,x-1);
		else
			printf("%d %d\n",x/2,x/2);
	}
	return 0;
}
