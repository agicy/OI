#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++)
static char buf[100000],*p1=buf,*p2=buf;
inline int read(void){
	reg bool f=false;
	reg char ch=getchar();
	reg int res=0;
	while(ch<'0'||'9'<ch)f|=(ch=='-'),ch=getchar();
	while('0'<=ch&&ch<='9')res=10*res+ch-'0',ch=getchar();
	return f?-res:res;
}

const int MAXN=10000+5;

int n;
int x[MAXN],y[MAXN];

inline void Read(void);
inline void Work(void);

int main(void){
	Read();
	Work();
	return 0;
}

inline void Read(void){
	n=read();
	for(reg int i=1;i<=n;++i)
		x[i]=read(),y[i]=read();
	return;
}

inline void Work(void){
	sort(x+1,x+n+1);
	sort(y+1,y+n+1);
	for(reg int i=1;i<=n;++i)
		x[i]-=i;
	sort(x+1,x+n+1);
	reg ll midx=x[(n+1)>>1],midy=y[(n+1)>>1],ans=0;
	for(reg int i=1;i<=n;++i)
		ans+=abs(x[i]-midx)+abs(y[i]-midy);
	printf("%lld\n",ans);
	return;
}