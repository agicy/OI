#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;

bool st;

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

inline void write(reg int x){
	static char buf[32];
	reg int p=-1;
	if(!x) putchar('0');
	else while(x) buf[++p]=(x%10)^'0',x/=10;
	while(~p) putchar(buf[p--]);
	return;
}

const int p=998244352;
const int MAXSIZE=4e5+5;

int x,n;
int bas[MAXSIZE],pbas[MAXSIZE];

bool ed;

int main(void){
	x=read(),n=read();
	reg int S=sqrt(p-1),tot=(p-1)/S;
	bas[0]=1;
	for(reg int i=1;i<S;++i)
		bas[i]=1ll*bas[i-1]*x%p;
	pbas[0]=1,pbas[1]=1ll*bas[S-1]*x%p;
	for(reg int i=2;i<=tot;++i)
		pbas[i]=1ll*pbas[i-1]*pbas[1]%p;
	for(reg int i=1;i<=n;++i){
		static int a;
		a=read();
		write(1ll*pbas[a/S]*bas[a%S]%p),putchar(i==n?'\n':' ');
	}
	flush();
	fprintf(stderr,"%.3lf s\n",1.0*clock()/CLOCKS_PER_SEC);
	fprintf(stderr,"%.3lf MiB\n",(&ed-&st)/1048576.0);
	return 0;
}