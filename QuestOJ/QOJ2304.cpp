#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
#define getchar()(p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++)
static char buf[100000],*p1=buf,*p2=buf;
inline int read(void){
	reg char ch=getchar();
	reg int res=0;
	while(!isdigit(ch))ch=getchar();
	while(isdigit(ch))res=10*res+ch-'0',ch=getchar();
	return res;
}

inline void read(reg char *s){
	*s=getchar();
	while((!isalpha(*s))&&(*s)!='*')*s=getchar();
	while(isalpha(*s)||(*s)=='*')*(++s)=getchar();
	*s='\0';
	return;
}

static char wbuf[1<<21];
int wp1;
const int wp2=1<<21;

#define flush() (fwrite(wbuf,1,wp1,stdout),wp1=0)
#define putchar(c)(wp1==wp2&&(flush(),0),wbuf[wp1++]=c)

const int MAXS=3e4+5;

char s[MAXS],t[MAXS];
int lens,lent;

inline bool check(reg int x,reg char ch,reg int& ptr){
	reg int res=0;
	reg bool star=false;
	while(s[ptr]!=ch&&ptr<=lens){
		if(ptr>lens)
			return false;
		if(s[ptr]=='*')
			star=true;
		else
			++res;
		++ptr;
	}
	return (res<x&&star)||res==x;
}

inline void Yes(void){
	putchar('Y'),putchar('e'),putchar('s'),putchar('\n');
	return;
}

inline void No(void){
	putchar('N'),putchar('o'),putchar('\n');
	return;
}

int main(void){
	freopen("strinq.in","r",stdin);
	freopen("strinq.out","w",stdout);
	reg int T=read();
	while(T--){
		reg bool flag=true;
		read(s+1),read(t+1);
		lens=strlen(s+1),lent=strlen(t+1);
		int ptr=1;
		while(ptr<=lens&&s[ptr]=='*')
			++ptr;
		if(ptr>lens||s[ptr]!=t[1])
			No();
		else{
			for(reg int i=1,cnt=1;i<=lent&&flag;++i,++cnt)
				if(t[i]!=t[i+1])
					flag&=check(cnt,t[i+1],ptr),cnt=0;
			if(flag)
				Yes();
			else
				No();
		}
	}
	flush();
	fclose(stdin);
	fclose(stdout);
	return 0;
}