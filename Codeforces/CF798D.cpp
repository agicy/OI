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

inline void write(reg int x){
	static char buf[32];
	reg int p=-1;
	if(x==0) putchar('0');
	else while(x) buf[++p]=(x%10)^'0',x/=10;
	while(~p) putchar(buf[p--]);
	return;
}

const int MAXN=1e5+5;

struct Node{
	int a,b;
};

int n;
Node a[MAXN];
int p[MAXN];

int main(void){
	srand(time(0));
	n=read();
	reg ll suma=0,sumb=0;
	for(reg int i=1;i<=n;++i)
		a[i].a=read(),suma+=a[i].a;
	for(reg int i=1;i<=n;++i)
		a[i].b=read(),sumb+=a[i].b;
	for(reg int i=1;i<=n;++i)
		p[i]=i;
	while(true){
		random_shuffle(p+1,p+n+1);
		reg ll tmpa=0,tmpb=0;
		for(reg int i=1;i<=(n>>1)+1;++i)
			tmpa+=a[p[i]].a,tmpb+=a[p[i]].b;
		if(((tmpa<<1)>suma)&&((tmpb<<1)>sumb)){
			write((n>>1)+1),putchar('\n');
			for(reg int i=1;i<=(n>>1)+1;++i)
				write(p[i]),putchar(i==(n>>1)+1?'\n':' ');
			break;
		}
	}
	flush();
	return 0;
}