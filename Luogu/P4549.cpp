#include<cstdio>
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

inline int gcd(reg int a,reg int b){
	reg int temp;
	while(b){
		temp=a%b;
		a=b;
		b=temp;
	}
	return a;
}

int n;

int main(void){
	reg int temp,ans;
	n=read()-1,ans=read();
	while(n--)
		ans=gcd(ans,(temp=read())>0?temp:-temp);
	printf("%d\n",ans);
	return 0;
}
