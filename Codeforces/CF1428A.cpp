#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++)
static char buf[100000],*p1=buf,*p2=buf;
inline int read(void){
	reg char ch=getchar();
	reg int res=0;
	while(!isdigit(ch))ch=getchar();
	while(isdigit(ch))res=10*res+(ch^'0'),ch=getchar();
	return res;
}

int main(void){
	reg int t=read();
	while(t--){
		reg int x1=read(),y1=read(),x2=read(),y2=read();
		if(x1==x2||y1==y2)
			printf("%d\n",abs(x1-x2)+abs(y1-y2));
		else
			printf("%d\n",abs(x1-x2)+abs(y1-y2)+2);
	}
	return 0;
}