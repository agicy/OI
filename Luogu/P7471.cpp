#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++)
static char buf[1<<21],*p1=buf,*p2=buf;
#define flush() (fwrite(wbuf,1,wp1,stdout),wp1=0)
#define putchar(c) (wp1==wp2&&(flush(),0),wbuf[wp1++]=c)
static char wbuf[1<<21];int wp1;const int wp2=1<<21;
inline int read(void){
	reg char ch=getchar();
	reg int res=0;
	while(!isdigit(ch))ch=getchar();
	while(isdigit(ch))res=10*res+(ch^'0'),ch=getchar();
	return res;
}

int a[3];

int main(void){
	reg int T=read();
	while(T--){
		a[0]=read(),a[1]=read(),a[2]=read();
		sort(a,a+3);
		if(a[0]==0&&a[1]==0)
			putchar('0'),putchar('\n');
		else if(a[0]==0)
			if(a[1]==a[2])
				putchar('1'),putchar('\n');
			else
				putchar('2'),putchar('\n');
		else if(a[0]==a[1]||a[1]==a[2])
			putchar('2'),putchar('\n');
		else if(a[0]+a[1]==a[2])
			putchar('2'),putchar('\n');
		else
			putchar('3'),putchar('\n');
	}
	flush();
	return 0;
}