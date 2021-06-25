#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
#define getchar()(p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++)
static char buf[1<<21],*p1=buf,*p2=buf;
inline int read(void){
	reg char ch=getchar();
	reg int res=0;
	while(!isdigit(ch))ch=getchar();
	while(isdigit(ch))res=10*res+(ch^'0'),ch=getchar();
	return res;
}

const int MAXN=100+5;

int n;
int a[MAXN<<1];

int main(void){
	n=read();
	for(reg int i=0;i<n;++i)
		a[i]=read(),a[i+n]=read();
	sort(a,a+(n<<1));
	reg int ans=0;
	for(reg int i=0;i<(n<<1);i+=2)
		ans+=a[i];
	printf("%d\n",ans);
	return 0;
}