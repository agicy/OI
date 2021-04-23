#include<cstdio>
#include<cctype>
using namespace std;
#define reg register
typedef long long ll;
typedef unsigned long long ull;
inline int read(void){
	reg char ch=getchar();
	reg int res=0;
	while(!isdigit(ch))ch=getchar();
	while(isdigit(ch))res=10*res+(ch^'0'),ch=getchar();
	return res;
}

inline ull readull(void){
	reg char ch=getchar();
	reg ull res=0;
	while(!isdigit(ch))ch=getchar();
	while(isdigit(ch))res=10*res+(ch^'0'),ch=getchar();
	return res;
}

inline void writeln(reg ull x){
	static char buf[32];
	reg int p=-1;
	if(x==0) putchar('0');
	else while(x) buf[++p]=(x%10)^'0',x/=10;
	while(~p) putchar(buf[p--]);
	putchar('\n');
	return;
}

inline void writeln(const char *s){
	while(*s) putchar(*(s++));
	putchar('\n');
	return;
}

int main(void){
	reg int t=read();
	while(t--){
		static int a,b,c,d,e,f,g,h;
		static ull i;
		a=read(),b=read(),c=read(),d=read(),e=read(),f=read(),g=read(),h=read(),i=readull();
		if(a==60&&b==60&&c==60&&d==60&&e==60&&f==60&&g==60&&h==60&&i==9223372036854775808ull)
			writeln("18446744073709551616");
		else
			writeln((1ull<<a)+(1ull<<b)+(1ull<<c)+(1ull<<d)+(1ull<<e)+(1ull<<f)+(1ull<<g)+(1ull<<h)+i);
	}
	return 0;
}