#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++)
static char buf[1<<21],*p1=buf,*p2=buf;
#define flush() (fwrite(wbuf,1,wp1,stdout),wp1=0)
#define putchar(c) (wp1==wp2&&(flush(),0),wbuf[wp1++]=c)
static char wbuf[1<<21];int wp1;const int wp2=1<<21;
inline int read(void){
	reg char ch=getchar();
	reg int res=0;
	while(!isdigit(ch)) ch=getchar();
	while(isdigit(ch)) res=10*res+(ch^'0'),ch=getchar();
	return res;
}

const int MAXN=1e5+5;

inline int gcd(reg int a,reg int b){
	return b?gcd(b,a%b):a;
}

int n;
int a[MAXN];
int p[MAXN];
char ans[MAXN];

int main(void){
	srand(time(0));
	n=read();
	for(reg int i=1;i<=n;++i){
		a[i]=read();
		p[i]=i;
	}
	reg bool flag=true;
	while(clock()<0.45*CLOCKS_PER_SEC){
		random_shuffle(p+1,p+n+1);
		reg int gcd1=0,gcd2=0;
		for(reg int i=1;i<=n;++i){
			reg int tmp=gcd(gcd1,a[p[i]]);
			if(tmp!=gcd1)
				gcd1=tmp,ans[p[i]]='1';
			else
				gcd2=gcd(gcd2,a[p[i]]),ans[p[i]]='2';
		}
		if(gcd1==1&&gcd2==1){
			putchar('Y'),putchar('E'),putchar('S'),putchar('\n');
			for(reg int i=1;i<=n;++i)
				putchar(ans[i]),putchar(i==n?'\n':' ');
			flag=false;
			break;
		}
	}
	if(flag)
		putchar('N'),putchar('O'),putchar('\n');
	flush();
	return 0;
}