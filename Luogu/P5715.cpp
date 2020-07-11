#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
typedef unsigned long long ull;
#define INF 0X3F3F3F3F
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

inline void Read(void);
inline void Work(void);

int main(void){
	Read();
	Work();
	return 0;
}

int a[3];

inline void Read(void){
	for(reg int i=0;i<3;++i)
		a[i]=read();
	return;
}

inline void Work(void){
	sort(a,a+3);
	for(reg int i=0;i<3;++i)
		printf("%d%c",a[i],i==3-1?'\n':' ');
	return;
}
