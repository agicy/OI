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

const int MAXN=200000+5;

int T;
int n;
int s[MAXN],e[MAXN],d[MAXN];
bitset<(1<<31)-1> S;

inline void Read(void);
inline void Work(void);

int main(void){
	while(T--){
		Read();
		Work();
	}
	return 0;
}

inline void Read(void){
	n=read();
	for(reg int i=1;i<=n;++i)
		s[i]=read(),e[i]=read(),d[i]=read();
	return;
}

inline void Work(void){
	
	return;
}
