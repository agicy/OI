#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++)
static char buf[100000],*p1=buf,*p2=buf;
#define flush() (fwrite(wbuf,1,wp1,stdout),wp1=0)
#define putchar(c)(wp1==wp2&&(flush(),0),wbuf[wp1++]=c)
static char wbuf[1<<21];int wp1;const int wp2=1<<21;
inline int read(void){
	reg bool f=false;
	reg char ch=getchar();
	reg int res=0;
	while(!isdigit(ch))f|=(ch=='-'),ch=getchar();
	while(isdigit(ch))res=10*res+(ch^'0'),ch=getchar();
	return f?-res:res;
}

const int MAXN=5e5+5;

struct Vector{
	int x,y,id;
};

const ll R2=1.42e6*1.42e6;

int n;
Vector a[MAXN];

inline ll sqr(reg ll x){
	return x*x;
}

bool ans[MAXN];

int main(void){
	n=read();
	for(reg int i=1;i<=n;++i)
		a[i].x=read(),a[i].y=read(),a[i].id=i;
	while(true){
		reg ll sumx=0,sumy=0;
		for(reg int i=1;i<=n;++i)
			if(sqr(sumx+a[i].x)+sqr(sumy+a[i].y)<=sqr(sumx-a[i].x)+sqr(sumy-a[i].y))
				sumx+=a[i].x,sumy+=a[i].y,ans[a[i].id]=false;
			else
				sumx-=a[i].x,sumy-=a[i].y,ans[a[i].id]=true;
		if(sqr(sumx)+sqr(sumy)<=R2)
			break;
		random_shuffle(a+1,a+n+1);
	}
	for(reg int i=1;i<=n;++i){
		if(ans[i])
			putchar('-');
		putchar('1'),putchar('\n');
	}
	flush();
	return 0;
}