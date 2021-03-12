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

const int MAXN=1e5+5;

int n,k;
int a[MAXN];

int main(void){
	reg int t=read();
	while(t--){
		n=read(),k=read();
		for(reg int i=1;i<=n;++i)
			a[i]=read();
		sort(a+1,a+n+1);
		reg int max=a[n],mex=0;
		for(reg int i=1;i<=n;++i)
			if(a[i]==mex)
				++mex;
		if(mex<max){
			reg bool flag=false;
			reg int res=(mex+max+1)>>1;
			for(reg int i=1;i<=n;++i)
				if(res==a[i]){
					flag=true;
					break;
				}
			if(flag||!k)
				writeln(n);
			else
				writeln(n+1);
		}
		else
			writeln(n+k);
	}
	flush();
	return 0;
}