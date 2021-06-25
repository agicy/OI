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
	while(!isdigit(ch)) ch=getchar();
	while(isdigit(ch)) res=10*res+(ch^'0'),ch=getchar();
	return res;
}

inline void read(reg char *s){
	*s=getchar();
	while(!isalpha(*s)) *s=getchar();
	while(isalpha(*s)) *(++s)=getchar();
	*s='\0';
	return;
}

const int MAXN=3e5+5;

char s[MAXN];

int main(void){
	reg int t=read();
	while(t--){
		read(s+1);
		reg int n=strlen(s+1);
		reg int pos=0;
		for(reg int i=1;i<=n;++i)
			if(s[n-i+1]!='a'){
				pos=i;
				break;
			}
		if(!pos)
			putchar('N'),putchar('o'),putchar('\n');
		else{
			putchar('Y'),putchar('e'),putchar('s'),putchar('\n');
			for(reg int i=1;i<pos;++i)
				putchar(s[i]);
			putchar('a');
			for(reg int i=pos;i<=n;++i)
				putchar(s[i]);
			putchar('\n');
		}
	}
	flush();
	return 0;
}