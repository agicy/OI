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

const int MAXN=2e5+5;

int n,k;
char s[MAXN];
bool val[MAXN*3];

int main(void){
	n=read(),k=read(),read(s+1);
	reg int t=min(k,(n<<1)|(k&1));
	for(reg int i=1;i<=n;++i)
		val[i]=s[i]-'A';
	reg bool tag=false;
	reg int ptr=1;
	for(reg int i=1;i<=t;++i)
		if(val[ptr]^tag)
			tag=!tag,val[ptr+n]=val[ptr],++ptr;
		else
			val[ptr]=!val[ptr];
	for(reg int i=ptr;i<=ptr+n-1;++i)
		putchar((val[i]^tag)+'A');
	putchar('\n');
	flush();
	return 0;
}