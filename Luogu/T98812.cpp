#include<cstdio>
#include<algorithm>
using std::max;
#define reg register
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++)
static char buf[100000],*p1=buf,*p2=buf;
inline int read(void){
	reg bool flag=false;
	reg char ch=getchar();
	reg int res=0;
	while(ch<'0'||'9'<ch)flag|=(ch=='-'),ch=getchar();
	while('0'<=ch&&ch<='9')res=10*res+ch-'0',ch=getchar();
	return flag?-res:res;
}

const int MAXN=100000+5;

int n,w,type[MAXN],a[MAXN];

int main(void){
	reg int i;
	reg double k,c,ans=0;
	n=read(),k=1-0.01*read(),c=1+0.01*read(),w=read();
	for(i=1;i<=n;++i)
		type[i]=read(),a[i]=read();
	for(i=n;i>=1;--i){
		if(type[i]==1)
			ans=max((double)ans,ans*k+a[i]);
		if(type[i]==2)
			ans=max((double)ans,ans*c-a[i]);
	}
	printf("%.2f\n",ans*w);
	return 0;
}
