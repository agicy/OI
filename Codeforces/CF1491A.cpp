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

const int MAXN=1e5+5;

int n,m;
bool a[MAXN];

int main(void){
	n=read(),m=read();
	reg int cnt1=0;
	for(reg int i=1;i<=n;++i){
		a[i]=read();
		if(a[i])
			++cnt1;
	}
	while(m--){
		static int t,x;
		t=read(),x=read();
		switch(t){
			case 1:{
				a[x]=!a[x];
				if(a[x]) ++cnt1;
				else --cnt1;
				break;
			}
			case 2:{
				putchar('0'|(x<=cnt1)),putchar('\n');
				break;
			}
		}
	}
	flush();
	return 0;
}