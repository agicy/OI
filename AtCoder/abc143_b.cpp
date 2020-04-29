#include<cstdio>
#define reg register
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

const int MAXN=50+5;

int n;
int d[MAXN];

int main(void){
	reg int i,j,ans=0;
	n=read();
	for(i=1;i<=n;++i)
		d[i]=read();
	for(i=1;i<=n;++i)
		for(j=i+1;j<=n;++j)
			ans+=d[i]*d[j];
	printf("%d\n",ans);
	return 0;
}
