#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
typedef unsigned long long ull;
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

const int MAXN=10000+5;

inline void Read(void);
inline void Work(void);

int main(void){
	reg int T=read();
	while(T--){
		Read();
		Work();
	}
	return 0;
}

int n;
int a[MAXN];

inline void Read(void){
	n=read();
	for(reg int i=1;i<=n;++i)
		a[i]=read();
	return;
}

int p[MAXN];

inline void Work(void){
	for(reg int i=1;i<=n;++i)
		p[a[i]]=i;
	reg bool flag=false;
	for(reg int d=1;d<=(n>>1)&&!flag;++d)
		for(reg int i=1;i<=n-(d<<1);++i)
			if((p[i]<p[i+d]&&p[i+d]<p[i+(d<<1)])||(p[i]>p[i+d]&&p[i+d]>p[i+(d<<1)])){
				flag=true;
				break;
			}
	puts(flag?"Y":"N");
	return;
}
