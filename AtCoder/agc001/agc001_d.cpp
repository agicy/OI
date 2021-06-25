#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
#define getchar()(p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++)
static char buf[1<<21],*p1=buf,*p2=buf;
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

int a[MAXN],b[MAXN*2],pos[3];
int n,m,cnt;

inline bool check(void){
	reg int cnt=0;
	for(reg int i=1;i<=n;++i)
		if(a[i]&1)
			++cnt;
	return cnt<=2;
}

int main(void){
	m=read(),n=read();
	for(reg int i=1;i<=n;++i)
		a[i]=read();
	if(!check())
		puts("Impossible");
	else{
		reg int cnt=0;
		for(int i=1;i<=n;++i)
			if(a[i]&1)
				pos[++cnt]=i;
		if(pos[1])
			swap(a[n],a[pos[1]]);
		if(pos[2])
			swap(a[1],a[pos[2]]);
		for(reg int i=1;i<=n;++i)
			printf("%d%c",a[i],i==n?'\n':' ');
		reg int tot=0;
		switch(cnt){
			case 0:{
				b[++tot]=1;
				reg int sum=m-1;
				for(reg int i=1;i<n;++i)
					b[++tot]=a[i],sum-=a[i];
				if(!sum)
					break;
				sum=(sum-1)>>1;
				for(reg int i=1;i<=(sum>>1);++i)
					b[++tot]=2;
				b[++tot]=1;
				for(reg int i=(sum>>1)+1;i<=sum;++i)
					b[++tot]=2;
				break;
			}
			case 1:{
				b[++tot]=1;
				for(reg int i=1;i<n;++i)
					b[++tot]=a[i];
				for(reg int i=1;i<=((a[n]-1)>>1);++i)
					b[++tot]=2;
				break;
			}
			default:{
				b[++tot]=a[1]+1;
				for(reg int i=2;i<n;++i)
					b[++tot]=a[i];
				for(reg int i=1;i<=((a[n]-1)>>1);++i)
					b[++tot]=2;
				break;
			}
		}
		printf("%d\n",tot);
		for(reg int i=1;i<=tot;++i)
			printf("%d%c",b[i],i==tot?'\n':' ');
	}
	return 0;
}