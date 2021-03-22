#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
#define getchar()(p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++)
static char buf[100000],*p1=buf,*p2=buf;
#define flush() (fwrite(wbuf,1,wp1,stdout),wp1=0)
#define putchar(c) (wp1==wp2&&(flush(),0),wbuf[wp1++]=c)
static char wbuf[1<<21];int wp1;const int wp2=1<<21;
inline int read(void){
	reg bool f=false;
	reg char ch=getchar();
	reg int res=0;
	while(!isdigit(ch))f|=(ch=='-'),ch=getchar();
	while(isdigit(ch))res=10*res+(ch^'0'),ch=getchar();
	return f?-res:res;
}

inline ll readll(void){
	reg bool f=false;
	reg char ch=getchar();
	reg ll res=0;
	while(!isdigit(ch))f|=(ch=='-'),ch=getchar();
	while(isdigit(ch))res=10*res+(ch^'0'),ch=getchar();
	return f?-res:res;
}

inline void Err(void){
	puts("NO"),exit(0);
	return;
}

const int MAXN=2e5+5;
const ll inf=4e18;

struct Node{
	ll x,y,k;
	int w;
	inline bool operator<(const Node &a)const{
		return w<a.w;
	}
};

int n,l;
ll lx=-inf,rx=inf,ly=-inf,ry=inf;
Node a[MAXN];

int main(void){
	n=read(),l=read();
	for(reg int i=1;i<=n;++i){
		static ll t,x,y;
		t=readll(),x=readll(),y=readll();
		if((t^x^y)&1)
			Err();
		a[i].k=t/l,a[i].w=t%l,a[i].x=(t+x+y)>>1,a[i].y=(t+y-x)>>1;
	}
	sort(a+1,a+n+1);
	a[++n].k=-1,a[n].w=l;
	for(reg int i=1;i<=n;++i){
		reg ll k=a[i].k-a[i-1].k;
		reg int w=a[i].w-a[i-1].w;
		if(!k){
			if(0<a[i].x-a[i-1].x-w||a[i].x-a[i-1].x<0||0<a[i].y-a[i-1].y-w||a[i].y-a[i-1].y<0)
				Err();
		}
		else if(k>0){
			lx=max(lx,(ll)ceil(1.0L*(a[i].x-a[i-1].x-w)/k));
			rx=min(rx,(ll)floor(1.0L*(a[i].x-a[i-1].x)/k));
			ly=max(ly,(ll)ceil(1.0L*(a[i].y-a[i-1].y-w)/k));
			ry=min(ry,(ll)floor(1.0L*(a[i].y-a[i-1].y)/k));
		}
		else{
			k*=-1;
			lx=max(lx,(ll)ceil(1.0L*(a[i-1].x-a[i].x)/k));
			rx=min(rx,(ll)floor(1.0L*(a[i-1].x-a[i].x+w)/k));
			ly=max(ly,(ll)ceil(1.0L*(a[i-1].y-a[i].y)/k));
			ry=min(ry,(ll)floor(1.0L*(a[i-1].y-a[i].y+w)/k));
		}
	}
	if(lx>rx||ly>ry)
		Err();
	for(reg int i=1;i<=n;++i){
		reg int dx=(a[i].x-a[i].k*lx)-(a[i-1].x-a[i-1].k*lx);
		reg int dy=(a[i].y-a[i].k*ly)-(a[i-1].y-a[i-1].k*ly);
		reg int t=a[i].w-a[i-1].w,x=0,y=0;
		while(t--){
			reg int tag=0;
			if(x<dx)
				++x,tag|=1;
			if(y<dy)
				++y,tag|=2;
			switch(tag){
				case 3:{
					putchar('U');
					break;
				}
				case 2:{
					putchar('L');
					break;
				}
				case 1:{
					putchar('R');
					break;
				}
				case 0:{
					putchar('D');
					break;
				}
			}
		}
	}
	putchar('\n');
	flush();
	return 0;
}