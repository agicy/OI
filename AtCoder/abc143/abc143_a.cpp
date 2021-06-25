#include<cstdio>
#include<algorithm>
using std::max;
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

int a,b;

int main(void){
	a=read(),b=read();
	printf("%d\n",max(a-(b<<1),0));
	return 0;
}
