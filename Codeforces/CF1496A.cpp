#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++)
static char buf[100000],*p1=buf,*p2=buf;
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

inline void read(reg char *s){
	*s=getchar();
	while(!isalpha(*s))*s=getchar();
	while(isalpha(*s))*(++s)=getchar();
	*s='\0';
	return;
}

const int MAXN=100+5;

int n,k;
char s[MAXN];

int main(void){
	reg int t=read();
	while(t--){
		n=read(),k=read();
		read(s);
		if(!k)
			putchar('Y'),putchar('E'),putchar('S'),putchar('\n');
		else if((!(n&1))&&(k<<1)==n)
			putchar('N'),putchar('O'),putchar('\n');
		else{
			reg bool flag=true;
			for(reg int i=0;i<=(n>>1);++i)
				if(s[i]!=s[n-i-1]){
					if(k>i)
						flag=false;
					break;
				}
			if(!flag)
				putchar('N'),putchar('O'),putchar('\n');
			else
				putchar('Y'),putchar('E'),putchar('S'),putchar('\n');
		}
	}
	flush();
	return 0;
}