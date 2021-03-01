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

inline void writeln(reg int x){
	static char buf[32];
	reg int p=-1;
	if(x==0) putchar('0');
	else while(x) buf[++p]=(x%10)^'0',x/=10;
	while(~p) putchar(buf[p--]);
	putchar('\n');
	return;
}

inline int min(reg int a,reg int b){
	return a<b?a:b;
}

const int MAXN=100+5;
const int inf=0x7f7f7f7f;

int n,u,v;
int a[MAXN];

int main(void){
	reg int t=read();
	while(t--){
		reg int ans=inf;
		n=read(),u=read(),v=read();
		for(reg int i=1;i<=n;++i)
			a[i]=read();
		for(reg int i=2;i<=n;++i)
			if(abs(a[i]-a[i-1])>1)
				ans=0;
			else if(abs(a[i]-a[i-1])==1)
				ans=min(ans,min(u,v));
			else
				ans=min(ans,v+min(u,v));
		writeln(ans);
	}
	flush();
	return 0;
}