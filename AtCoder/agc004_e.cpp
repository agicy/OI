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
	while(isdigit(ch))res=10*res+(ch^'0'),ch=getchar();
	return res;
}

inline void read(reg char *s){
	*s=getchar();
	while(*s!='o'&&*s!='E'&&*s!='.')*s=getchar();
	while(*s=='o'||*s=='E'||*s=='.')*(++s)=getchar();
	*s='\0';
	return;
}

const int MAXH=100+5;
const int MAXW=100+5;

int h,w;
char M[MAXH][MAXW];

int main(void){
	h=read(),w=read();
	for(reg int i=1;i<=h;++i)
		read(M[i]+1);
	
	return 0;
}