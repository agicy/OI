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
	while(!isdigit(ch))f|=(ch=='-'),ch=getchar();
	while(isdigit(ch))res=10*res+(ch^'0'),ch=getchar();
	return f?-res:res;
}

const int MAXN=2e5+5;

int n;
int f[4];

int main(void){
	n=read();
	for(reg int i=1;i<=n;++i){
		static int a;
		a=read();
		f[0]+=(a==1);
		f[1]=max(f[0],f[1]+(a==2));
		f[2]=max(f[1],f[2]+(a==1));
		f[3]=max(f[2],f[3]+(a==2));
	}
	printf("%d\n",f[3]);
	return 0;
}