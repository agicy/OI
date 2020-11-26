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

int main(void){
	reg int n=read();
	reg int ans=0;
	for(reg int i=1;i<=n;++i)
		for(reg int j=(i<<1);j<=n;j+=i)
			if((j^i)==j-i)
				++ans;
	printf("%d\n",ans);
	return 0;
}