#include<bits/stdc++.h>
using namespace std;
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

const int MAXN=5000+5;

int n;
int a[MAXN];
int f[MAXN>>1][3];

int main(void){
	n=read();
	for(reg int i=1;i<=n;++i)
		a[i]=read();
	memset(f,0X3F,sizeof(f));
	f[0][0]=f[1][1]=0;
	for(reg int i=2;i<=n;++i)
		for(reg int j=(i+1)>>1;j>=1;--j){
			f[j][0]=min(f[j][0],f[j][2]);
			f[j][2]=f[j][1]+max(0,a[i]-a[i-1]+1);
			f[j][1]=min(f[j-1][0]+max(0,a[i-1]-a[i]+1),f[j-1][2]+max(0,min(a[i-1],a[i-2]-1)-a[i]+1));
		}
	for(reg int i=1;i<=((n+1)>>1);++i)
		printf("%d%c",min(f[i][0],min(f[i][1],f[i][2])),i==((n+1)>>1)?'\n':' ');
	return 0;
}
