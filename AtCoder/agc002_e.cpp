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

const int MAXN=1e5+5;

int n;
int a[MAXN];

int main(void){
	n=read();
	for(reg int i=1;i<=n;++i)
		a[i]=read();
	sort(a+1,a+n+1);
	reverse(a+1,a+n+1);
	for(reg int i=1;i<=n;++i)
		if(i+1>a[i+1]){
			reg int j=0;
			while(a[j+i+1]==i)
				++j;
			if(((a[i]-i)|j)&1)
				puts("First");
			else
				puts("Second");
			break;
		}
	return 0;
}