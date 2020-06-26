#include<bits/stdc++.h>
using namespace std;
#define reg register
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++)
static char buf[100000],*p1=buf,*p2=buf;
inline int read(void){
	reg bool f=false;
	reg char ch=getchar();
	reg int res=0;
	while(ch<'0'||'9'<ch)f|=(ch=='-'),ch=getchar();
	while('0'<=ch&&ch<='9')res=10*res+ch-'0',ch=getchar();
	return f?-res:res;
}

int main(void){
	reg int T=read();
	while(T--){
		reg int a=read(),b=read(),c=read(),d=read();
		reg int x=read(),y=read(),x1=read(),y1=read(),x2=read(),y2=read();
		if(x1==x&&x==x2&&(a||b))
			puts("No");
		else if(y1==y&&y==y2&&(c||d))
			puts("No");
		else if(x1<=x+b-a&&x+b-a<=x2&&y1<=y-c+d&&y-c+d<=y2)
			puts("Yes");
		else
			puts("No");
	}
	return 0;
}
