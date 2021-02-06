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

int H,W,h,w;

int main(void){
	H=read(),W=read(),h=read(),w=read();
	if((!(H%h))&&(!(W%w)))
		puts("No");
	else{
		puts("Yes");
		reg int k=499;
		for(reg int i=1;i<=H;++i)
			for(reg int j=1;j<=W;++j)
				if(i%h==0&&j%w==0)
					printf("%d%c",-(k*(h*w-1)+1),j==W?'\n':' ');
				else
					printf("%d%c",k,j==W?'\n':' ');
	}
	return 0;
}