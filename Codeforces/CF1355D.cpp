#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++)
static char buf[1<<21],*p1=buf,*p2=buf;
inline int read(void){
	reg char ch=getchar();
	reg int res=0;
	while(!isdigit(ch)) ch=getchar();
	while(isdigit(ch)) res=10*res+ch-'0',ch=getchar();
	return res;
}

int n,s;

int main(void){
	n=read(),s=read();
	if((n<<1)>s)
		puts("NO");
	else{
		puts("YES");
		for(reg int i=1;i<=n;++i)
			printf("%d%c",i==n?(s-(n-1)):1,i==n?'\n':' ');
		printf("%d\n",n);
	}
	return 0;
}