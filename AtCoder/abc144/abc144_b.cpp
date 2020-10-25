#include<cstdio>
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

int n;

int main(void){
	reg int i;
	n=read();
	for(i=1;i<=9;++i)
		if(n%i==0&&1<=n/i&&n/i<=9)
			return puts("Yes"),0;
	puts("No");
	return 0;
}